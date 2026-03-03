// Created on: 2026-02-27
// Created by: Mladen Banovic
// Copyright (c) German Aerospace Center (DLR e.V.)
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.

#include <gtest/gtest.h>

#include <vector>

#include <Geom_BSplineCurve.hxx>

Handle(Geom_BSplineCurve) bspline_curve(const std::vector<Standard_Real>& design_parameters)
{
  // control points
  gp_Pnt p1(0.0, 0.0, 0.0);
  gp_Pnt p2(design_parameters[0], design_parameters[1], design_parameters[2]);
  gp_Pnt p3(0.0, 2.0, -1.0);
  gp_Pnt p4(0.0, 0.0, 3.0);
  gp_Pnt p5(0.0, 4.0, 0.0);

  TColgp_Array1OfPnt control_points(1, 5);
  control_points.SetValue(1, p1);
  control_points.SetValue(2, p2);
  control_points.SetValue(3, p3);
  control_points.SetValue(4, p4);
  control_points.SetValue(5, p5);

  // degree
  Standard_Integer degree = 2;

  // knots
  TColStd_Array1OfReal knots(1, 4);
  knots.SetValue(1, Standard_Real(0.));
  knots.SetValue(2, Standard_Real(1.));
  knots.SetValue(3, Standard_Real(2.));
  knots.SetValue(4, Standard_Real(3.));

  TColStd_Array1OfInteger mults(1, 4);
  mults.SetValue(1, Standard_Integer(3));
  mults.SetValue(2, Standard_Integer(1));
  mults.SetValue(3, Standard_Integer(1));
  mults.SetValue(4, Standard_Integer(3));

  Handle(Geom_BSplineCurve) curve = new Geom_BSplineCurve(control_points, knots, mults, degree);

  return curve;
}

// The fixture – gives us GetParam() returning an int
class Test_Geom_BSplineCurve_ByParameterId : public ::testing::TestWithParam<int> {};

TEST_P(Test_Geom_BSplineCurve_ByParameterId, sensitivity_wrt_pole_coordinate_xyz)
{
  // independent variable index (x, y or z)
  int independent_idx = GetParam();

  ASSERT_TRUE(independent_idx >= 0 && independent_idx <= 2);

  std::vector<Standard_Real> design_parameters = {0.0, 1.0, 2.0};

  // set AD seed
  design_parameters[independent_idx].setADValue(0, 1.);

  Handle(Geom_BSplineCurve) ad_curve = bspline_curve(design_parameters);

  gp_Pnt pnt_primal;

  ad_curve->D0(Standard_Real(0.5), pnt_primal);

  // reset AD seed
  design_parameters[independent_idx].setADValue(0, 0.);

  // finite differences
  double fd_step = 1e-6;

  double design_parameter_original_value = design_parameters[independent_idx].getValue();

  design_parameters[independent_idx] += fd_step;

  Handle(Geom_BSplineCurve) perturbed_curve = bspline_curve(design_parameters);

  gp_Pnt pnt_perturbed;

  perturbed_curve->D0(Standard_Real(0.5), pnt_perturbed);

  double fd_sensitivity_x = (pnt_perturbed.X().getValue() - pnt_primal.X().getValue()) / fd_step;
  double fd_sensitivity_y = (pnt_perturbed.Y().getValue() - pnt_primal.Y().getValue()) / fd_step;
  double fd_sensitivity_z = (pnt_perturbed.Z().getValue() - pnt_primal.Z().getValue()) / fd_step;

  design_parameters[independent_idx] = design_parameter_original_value;

  /*
  std::cout << "Comparison for the design parameter id: " << independent_idx << std::endl;
  std::cout << " AD (x,y,z): " << std::setprecision(8)
                    << std::setw(18) << std::scientific << pnt_primal.X().getADValue(0)
                    << std::setw(18) << std::scientific << pnt_primal.Y().getADValue(0)
                    << std::setw(18) << std::scientific << pnt_primal.Z().getADValue(0) <<
  std::endl;

  std::cout << " FD (x,y,z): " << std::setprecision(8)
                      << std::setw(18) << std::scientific << fd_sensitivity_x
                      << std::setw(18) << std::scientific << fd_sensitivity_y
                      << std::setw(18) << std::scientific << fd_sensitivity_z << std::endl;
  */

  EXPECT_NEAR(pnt_primal.X().getADValue(0), fd_sensitivity_x, 1e-5);
  EXPECT_NEAR(pnt_primal.Y().getADValue(0), fd_sensitivity_y, 1e-5);
  EXPECT_NEAR(pnt_primal.Z().getADValue(0), fd_sensitivity_z, 1e-5);
}

INSTANTIATE_TEST_SUITE_P(
    Test_Geom_BSplineCurve_ByParameterRange,                     // prefix for names
    Test_Geom_BSplineCurve_ByParameterId,                        // fixture class
    ::testing::Values(0, 1, 2)); // ids to test
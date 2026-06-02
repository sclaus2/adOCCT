# adOCCT: Algorithmic Differentiation of the Open CASCADE Technology modeling kernel

Algorithmic Differentiation (AD) is applied
to [Open CASCADE Technology (OCCT)](https://github.com/Open-Cascade-SAS/OCCT)
in order to enable the computation of the so-called geometric sensitivities (e.g., derivatives of
surface nodes with respect to its design parameters such as control points).
The differentiated OCCT variant, named *adOCCT*, is developed by integrating the AD tool
[ADOL-C](https://github.com/coin-or/adol-c) (*Automatic Differentiation by Overloading in C++*)
into its source-code.

## License

adOCCT is free software; you can redistribute it and/or modify it under the terms of the GNU
Lesser General Public License version 2.1 as published by the Free Software Foundation, with a special exception defined
in the file `OCCT_LGPL_EXCEPTION.txt`. Consult the file `LICENSE_LGPL_21.txt` included in the adOCCT distribution for
the complete text of the license.

**Note:** adOCCT is provided on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND. The entire risk related to any use of
the adOCCT code and materials is on you. See the license text for a formal disclaimer.

## Build from sources

adOCCT is currently being tested only on Linux distributions.
To use it, adOCCT has to be built from sources to ensure compatibility with your platform (OS, compiler).
The process of configuring and building adOCCT using CMake is very similar to the original OCCT workflow.
Please consult the
official [Building OCCT](https://dev.opencascade.org/doc/occt-7.9.0/overview/html/build_upgrade__building_occt.html)
page for instructions.
Additional steps and requirements are described in the following.

The first step is to build and install ADOL-C release 2.7.2.
When configuring it, one has to activate the flag `--enable-atrig-erf`.
For example, ADOL-C installation process can be executed as follows:

```
./configure --prefix=ADOLC_PREFIX --enable-atrig-erf
make && make install
```

where `ADOLC_PREFIX` is the destination where header and library files are going to be installed.

Next, one can proceed with building adOCCT as follows:

1. Checkout `ad/master` branch (should be done by default).
2. Configure adOCCT using CMake by setting the following variable: `USE_ADOLC=ON`.
   After that, a PkgConfig module for CMake is loaded to search for the existing ADOL-C installation.
   If it fails to find it, which can be the case with a local ADOL-C installation that is not added
   to common search paths, one has to manually set a variable `3RDPARTY_ADOLC_DIR` to the path where
   ADOL-C installation resides (i.e., `ADOLC_PREFIX` described previously).
   From that, the variables for the ADOL-C include and library directory are automatically derived.
3. To activate the reverse mode of AD, set `ADOLC_REVERSE_MODE=ON`. This will build adOCCT using the
   *trace-based* headers of ADOL-C, otherwise the *traceless* header of ADOL-C is employed which allows only
   the forward mode of AD.
4. Optionally, if ADOL-C has been built with Boost, one can provide the used Boost installation directory
   using the variable `3RDPARTY_BOOST_DIR`. This option makes the *traceless* feature of ADOL-C more performant
   as Boost is used to handle the memory management of *adouble* objects.
5. Optionally, one can build AD-tests by setting `BUILD_AD_TESTS=ON`.
6. Optionally, add `-Wno-ignored-qualifiers -Wno-deprecated-copy` to `CMAKE_CXX_FLAGS` in order to
   suppress warnings related to the ADOL-C *traceless* option.
7. Once the configuring is done, proceed with `make && make install`.

## Version

The current version of adOCCT can be found in the file [`adm/cmake/version.cmake`](adm/cmake/version.cmake).

## Cite as

Banović, M., Mykhaskiv, O., Auriemma, S., Walther, A., Legrand, H., & Müller, J. D. (2018). Algorithmic differentiation
of the Open CASCADE Technology CAD kernel and its coupling with an adjoint CFD solver. Optimization Methods and
Software, 33(4–6), 813–828. https://doi.org/10.1080/10556788.2018.1431235
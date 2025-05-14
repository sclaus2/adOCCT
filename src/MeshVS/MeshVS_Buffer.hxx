// Created on: 2007-03-07
// Created by: msv@EUCLIDEX
// Copyright (c) 2007-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef MeshVS_Buffer_HeaderFile
#define MeshVS_Buffer_HeaderFile

#include <Standard.hxx>
#include <gp_Pnt.hxx>

/**
 * General purpose buffer that is allocated on the stack with a
 * constant size MeshVS_BufSize, or is allocated dynamically if the requested
 * size exceeds the standard one.
 * It is useful when an allocation of an array of unknown size is needed,
 * and most often the array is small enough to allocate as automatic C array.
 */

//! define the constant to the size of 10 points
#define MeshVS_BufSize 10 * 3

template<class T>
class MeshVS_Buffer
{
public:
  //! Constructor of the buffer of the requested size
  MeshVS_Buffer(const Standard_Size theLength)
      : myDynData(nullptr)
  {
    if (theLength > MeshVS_BufSize)
      myDynData = new T[theLength]; // Standard::Allocate(theSize);
  }

  //! Destructor
  ~MeshVS_Buffer()
  {
    if (myDynData)
    {
      // Standard::Free(myDynData);
      // myDynData = 0;
      delete[] myDynData;
    }
  }

  //! Cast the buffer to the void pointer. Commented in the AD version of OCCT, also not used
  // operator void*() { return myDynData ? myDynData : (void*)myAutoData; }

  //! Interpret the buffer as a reference to double
  operator T&()
  {
    // return *(myDynData ? (Standard_Real*)myDynData : (Standard_Real*)myAutoData);
    return *(myDynData ? myDynData : myAutoData);
  }

  //! Interpret the buffer as a reference to int. Commented in the AD version of OCCT, accessing adouble array with an int pointer does not make sense
  /*
  operator Standard_Integer&()
  {
    return *(myDynData ? (Standard_Integer*)myDynData : (Standard_Integer*)myAutoData);
  }
  */

  //! Interpret the buffer as a reference to gp_Pnt
  operator gp_Pnt&() { return *(myDynData ? (gp_Pnt*)myDynData : (gp_Pnt*)myAutoData); }

private:
  //! Deprecate copy constructor
  MeshVS_Buffer(const MeshVS_Buffer&) {}

  //! Deprecate copy operation
  MeshVS_Buffer& operator=(const MeshVS_Buffer&) { return *this; }

  T  myAutoData[MeshVS_BufSize];
  T* myDynData;
};

#endif

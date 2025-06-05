#include <math_VectorBase.hxx>

// template specialization for Standard_Real
template <>
math_VectorBase<Standard_Real>& math_VectorBase<Standard_Real>::Initialized(
  const math_VectorBase<Standard_Real>& theOther)
{
  Standard_DimensionError_Raise_if(
    Length() != theOther.Length(),
    "math_VectorBase::Initialized() - input vector has wrong dimensions");
  // memmove(&Array.ChangeFirst(), &theOther.Array.First(), sizeof(TheItemType) * Array.Length());
  /*
  for (int i = 0; i < Array.Length(); ++i)
  {
    Array[i] = theOther.Array[i];
  }
  */
  std::copy(theOther.Array.cbegin(), theOther.Array.cend(), Array.begin());
  return *this;
}

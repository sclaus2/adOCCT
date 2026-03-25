#ifndef _Standard_Adouble_HeaderFile
#define _Standard_Adouble_HeaderFile

#include <adolc/adtl.h>

/*
 * A child class of adouble implemented only for the purposes of overloading the behavior of
 * ostream and istream operators. That is, only primal values should be considered, such that
 * OCCT input/output system is not corrupted with AD values.
 */

class Standard_Adouble : public adtl::adouble
{
public:
  Standard_Adouble() = default;

  inline Standard_Adouble(const double v)
      : adtl::adouble(v)
  {
  }

  inline Standard_Adouble(const double v, const double* adv)
      : adtl::adouble(v, adv)
  {
  }

  inline Standard_Adouble(const adtl::adouble& a)
      : adtl::adouble(a)
  {
  }

  inline Standard_Adouble(const adtl::adouble&& a)
      : adtl::adouble(a)
  {
  }

  inline Standard_Adouble(const Standard_Adouble& a)
      : adtl::adouble(static_cast<const adtl::adouble&>(a))
  {
  }

  ~Standard_Adouble() = default;

  friend ostream& operator<<(ostream& out, const Standard_Adouble& a)
  {
    out << a.getValue();
    return out;
  }

  friend istream& operator>>(istream& in, Standard_Adouble& a)
  {
    double temp;
    in >> temp;
    a.setValue(temp);
    return in;
  }
};

namespace std
{
// std::hash for Standard_Adouble
template <>
struct hash<Standard_Adouble>
{
  size_t operator()(const Standard_Adouble& a) const noexcept
  {
    return hash<double>()(a.getValue());
  }
};

// std::hash for adtl::adouble
template <>
struct hash<adtl::adouble>
{
  size_t operator()(const adtl::adouble& a) const noexcept { return hash<double>()(a.getValue()); }
};

// std::numeric_limits
template <>
struct numeric_limits<Standard_Adouble>
{
  static Standard_Adouble min() { return Standard_Adouble(std::numeric_limits<double>::min()); };

  static Standard_Adouble max() { return Standard_Adouble(std::numeric_limits<double>::max()); };

  static Standard_Adouble epsilon()
  {
    return Standard_Adouble(std::numeric_limits<double>::epsilon());
  };

  static constexpr bool is_specialized{true};
};
} // namespace std

#endif

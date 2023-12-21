#ifndef _Standard_Adouble_HeaderFile
#define _Standard_Adouble_HeaderFile

#include <adolc/adtl.h>

class myadouble : public adtl::adouble {
public:
    // inline myadouble() : adouble() {}
    //using adouble::adouble;
    myadouble() = default;
    inline myadouble(const double v) : adtl::adouble(v){}
    inline myadouble(const double v, const double* adv) : adtl::adouble(v,adv) {}
    inline myadouble(const adtl::adouble& a) : adtl::adouble(a) {}
    inline myadouble(const adtl::adouble&& a) : adtl::adouble(a) {}
    inline myadouble(const myadouble& a) : adtl::adouble(static_cast<const adtl::adouble&>(a)) {}

    ~myadouble() = default;

    inline explicit operator bool() const { return static_cast<bool>(this->getValue()); }
    inline explicit operator int() const { return static_cast<int>(this->getValue()); }
    inline explicit operator float() const { return static_cast<float>(this->getValue()); }

    friend ostream& operator << ( ostream& out, const myadouble& a);

    friend istream& operator >> ( istream& in, myadouble& a);
};

#endif

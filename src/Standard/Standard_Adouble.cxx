#include <Standard_Adouble.hxx>
#include <iostream>

ostream& operator << ( ostream& out, const myadouble& a) {
    out << a.getValue();
    return out;
}

istream& operator >> ( istream& in, myadouble& a) {
    double temp;
    in >> temp;
    a.setValue(temp);
    return in;
}

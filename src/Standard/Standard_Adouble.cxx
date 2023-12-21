#include <Standard_Adouble.hxx>
#include <iostream>

ostream& operator << ( ostream& out, const Standard_Adouble& a) {
    out << a.getValue();
    return out;
}

istream& operator >> ( istream& in, Standard_Adouble& a) {
    double temp;
    in >> temp;
    a.setValue(temp);
    return in;
}

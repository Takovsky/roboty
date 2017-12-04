#include <ostream> // ostream
#include "wektor.hpp"
#include "figura.hpp"

using namespace std;

ostream &operator<<(ostream &strm, t_figura F)
{
    for (auto pd = F.begin(); pd != F.end(); pd++)
        strm << *pd;
    return strm;
}

t_figura t_figura::operator+(t_wektor W)
{
    for (t_wektor &elem : *this)
        elem = elem + W;
    return *this;
}

t_figura t_figura::operator-(t_wektor W)
{
    for (t_wektor &elem : *this)
        elem = elem - W;
    return *this;
}
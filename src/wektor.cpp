#include <iostream>
#include "wektor.hpp"
#include "macierz.hpp"

using namespace std;

ostream &operator<<(ostream &strm, t_wektor W)
{
    return strm << W[0] << " " << W[1] << " " << W[2] << endl;
}

istream &operator>>(istream &strm, t_wektor &W)
{
    return strm >> W[0] >> W[1] >> W[2];
}

t_wektor t_wektor::operator+(t_wektor W)
{
    W[0] += _wektor[0];
    W[1] += _wektor[1];
    W[2] += _wektor[2];
    return W;
}

t_wektor t_wektor::operator+(float x)
{
    _wektor[0] += x;
    _wektor[1] += x;
    _wektor[2] += x;
    return *this;
}

t_wektor t_wektor::operator-(t_wektor W)
{
    W[0] = _wektor[0] - W[0];
    W[1] = _wektor[1] - W[1];
    W[2] = _wektor[2] - W[2];
    return W;
}

t_wektor t_wektor::operator*(float x)
{
    _wektor[0] *= x;
    _wektor[1] *= x;
    _wektor[2] *= x;
    return *this;
}

t_wektor t_wektor::obroc(t_macierz M)
{
    double x, y, z;
    x = M(0, 0) * _wektor[0] + M(0, 1) * _wektor[1] + M(0, 2) * _wektor[2];
    y = M(1, 0) * _wektor[0] + M(1, 1) * _wektor[1] + M(1, 2) * _wektor[2];
    z = M(2, 0) * _wektor[0] + M(2, 1) * _wektor[1] + M(2, 2) * _wektor[2];
    _wektor[0] = x;
    _wektor[1] = y;
    _wektor[2] = z;
    return *this;
}

t_wektor t_wektor::operator*(t_macierz M)
{
    obroc(M);
    return *this;
}

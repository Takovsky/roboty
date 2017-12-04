#include <cmath>   // sin, cos, PI
#include "macierz.hpp"
#include "nazwaosi.hpp"

using namespace std;

t_macierz t_macierz::operator*(t_macierz M)
{
    double x, y, z;
    x = _macierz[0][0] * M(0, 0) + _macierz[0][1] * M(1, 0) + _macierz[0][2] * M(2, 0);
    y = _macierz[0][0] * M(0, 1) + _macierz[0][1] * M(1, 1) + _macierz[0][2] * M(2, 1);
    z = _macierz[0][0] * M(0, 2) + _macierz[0][1] * M(1, 2) + _macierz[0][2] * M(2, 2);
    _macierz[0][0] = x;
    _macierz[0][1] = y;
    _macierz[0][2] = z;
    x = _macierz[1][0] * M(0, 0) + _macierz[1][1] * M(1, 0) + _macierz[1][2] * M(2, 0);
    y = _macierz[1][0] * M(0, 1) + _macierz[1][1] * M(1, 1) + _macierz[1][2] * M(2, 1);
    z = _macierz[1][0] * M(0, 2) + _macierz[1][1] * M(1, 2) + _macierz[1][2] * M(2, 2);
    _macierz[1][0] = x;
    _macierz[1][1] = y;
    _macierz[1][2] = z;
    x = _macierz[2][0] * M(0, 0) + _macierz[2][1] * M(1, 0) + _macierz[2][2] * M(2, 0);
    y = _macierz[2][0] * M(0, 1) + _macierz[2][1] * M(1, 1) + _macierz[2][2] * M(2, 1);
    z = _macierz[2][0] * M(0, 2) + _macierz[2][1] * M(1, 2) + _macierz[2][2] * M(2, 2);
    _macierz[2][0] = x;
    _macierz[2][1] = y;
    _macierz[2][2] = z;
    return *this;
}

t_macierz t_macierz::Zamien(float kat, nazwaosi os) //inicjalizacja macierzy zadanym katem
{
    switch (os)
    {
    case osx:
        _macierz[0][0] = 1;
        _macierz[0][1] = 0;
        _macierz[0][2] = 0;
        _macierz[1][0] = 0;
        _macierz[1][1] = cos(kat * M_PI / 180);
        _macierz[1][2] = -sin(kat * M_PI / 180);
        _macierz[2][0] = 0;
        _macierz[2][1] = sin(kat * M_PI / 180);
        _macierz[2][2] = cos(kat * M_PI / 180);
        break;
    case osy:
        _macierz[0][0] = cos(kat * M_PI / 180);
        _macierz[0][1] = 0;
        _macierz[0][2] = sin(kat * M_PI / 180);
        _macierz[1][0] = 0;
        _macierz[1][1] = 1;
        _macierz[1][2] = 0;
        _macierz[2][0] = -sin(kat * M_PI / 180);
        _macierz[2][1] = 0;
        _macierz[2][2] = cos(kat * M_PI / 180);
        break;
    case osz:
        _macierz[0][0] = cos(kat * M_PI / 180);
        _macierz[0][1] = -sin(kat * M_PI / 180);
        _macierz[0][2] = 0;
        _macierz[1][0] = sin(kat * M_PI / 180);
        _macierz[1][1] = cos(kat * M_PI / 180);
        _macierz[1][2] = 0;
        _macierz[2][0] = 0;
        _macierz[2][1] = 0;
        _macierz[2][2] = 1;
        break;
    }
    return *this;
}

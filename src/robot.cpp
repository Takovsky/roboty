#include <cstdlib> // rand()
#include <cstring> // c_str()
#include <fstream>
#include "robot.hpp"
#include "figura.hpp"
#include "wektor.hpp"
#include "obiekt.hpp"
#include "macierz.hpp"
#include "nazwaosi.hpp"

using namespace std;

unsigned int t_robot::_ilosc = 0;

t_robot::t_robot() : t_obiekt(string("robot") + char(_ilosc + '1') + string(".dat"))
{
    _ilosc++;
    int x = rand() % 401 - 200;
    int y = rand() % 401 - 200;
    int z = rand() % 401 - 200;
    _punktzaczepienia(x, y, z);
    _skala = 1;
    _predkosc = 1;
    _lokalne.push(_punktzaczepienia);
    _lokalne.push(_punktzaczepienia);
    _lokalne.push(_punktzaczepienia);
    _lokalne.push(_punktzaczepienia);
    _lokalne.push(_punktzaczepienia);
    _lokalne.push(_punktzaczepienia);
    _lokalne.push(_punktzaczepienia);
    _lokalne.push(_punktzaczepienia);
    _lokalne.push(_punktzaczepienia);
    _lokalne.push(_punktzaczepienia);
    resetuj();
    globalne() = _lokalne;
    globalne() = globalne() + _punktzaczepienia;
    save();
}

// t_robot::t_robot(t_wektor W) : t_obiekt(string("robot") + char(_ilosc + '1') + string(".dat"))
// {

//     ++_ilosc;
//     _punktzaczepienia = W;
//     _skala = 1;
//     _predkosc = 1;
//     _lokalne.push(W);
//     _lokalne.push(W);
//     _lokalne.push(W);
//     _lokalne.push(W);
//     _lokalne.push(W);
//     _lokalne.push(W);
//     _lokalne.push(W);
//     _lokalne.push(W);
//     _lokalne.push(W);
//     _lokalne.push(W);
//     resetuj();
//     globalne() = _lokalne;
//     globalne() = globalne() + _punktzaczepienia;
//     save();
// }

void t_robot::przesun(t_wektor translacja)
{
    globalne() = globalne() + translacja;
}

void t_robot::resetuj()
{
    t_macierz M;
    M.Zamien(0, osz);
    _kat = M;
    t_wektor W;
    _dlpromienia = 30 * _skala;
    _lokalne[0] = W;
    _lokalne[1] = W(0, 0, _dlpromienia);
    _lokalne[2] = W.obroc(M.Zamien(60, osy));
    _lokalne[3] = W.obroc(M.Zamien(90, osz));
    _lokalne[4] = W.obroc(M.Zamien(90, osz));
    _lokalne[5] = W.obroc(M.Zamien(90, osz));
    _lokalne[6] = W.obroc(M.Zamien(70, osx));
    _lokalne[7] = W.obroc(M.Zamien(90, osz));
    _lokalne[8] = W.obroc(M.Zamien(90, osz));
    _lokalne[9] = W.obroc(M.Zamien(90, osz));
}

void t_robot::ustaw()
{
    globalne() = _lokalne;
    globalne() = globalne() + _punktzaczepienia;
}

void t_robot::obroc(t_macierz M)
{
    t_wektor tmp = *globalne().begin();
    for (t_wektor &elem : _lokalne)
        elem.obroc(M);
    globalne() = _lokalne;
    globalne() = globalne() + tmp;
    _kat = M * _kat;
}

void t_robot::move()
{
    t_wektor tmp(0, 0, _predkosc);
    tmp.obroc(_kat);
    for (t_wektor &elem : globalne())
        elem = elem + tmp;
}

void t_robot::move(float odl)
{
    t_wektor tmp(0, 0, odl);
    tmp.obroc(_kat);
    for (t_wektor &elem : globalne())
        elem = elem + tmp;
}

void t_robot::skaluj()
{
    t_macierz tmp = _kat;
    t_wektor W = globalne()[0];
    W = W;
    resetuj();
    _kat = tmp;
    for (auto &elem : _lokalne)
    {
        elem.obroc(_kat);
    }
    globalne() = _lokalne;
    globalne() = globalne() + W;
}

void t_robot::save()
{
    fstream plik;
    plik.open(nazwa().c_str(), ios::out);
    plik << globalne()[0]
         << globalne()[1]
         << globalne()[2]
         << globalne()[3]
         << globalne()[2]
         << globalne()[7]
         << globalne()[6]
         << globalne()[7]
         << globalne()[0]
         << globalne()[1]
         << globalne()[3]
         << globalne()[8]
         << globalne()[9]
         << globalne()[8]
         << globalne()[0]
         << globalne()[1]
         << globalne()[5]
         << globalne()[4]
         << globalne()[5]
         << globalne()[6]
         << globalne()[0]
         << globalne()[1]
         << globalne()[4]
         << globalne()[9]
         << globalne()[0];
    plik.close();
}

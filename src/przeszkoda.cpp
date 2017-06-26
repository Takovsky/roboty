#include <cstdlib> // rand()
#include <fstream>
#include "obiekt.hpp"
#include "przeszkoda.hpp"
#include "macierz.hpp"
#include "nazwaosi.hpp"

using namespace std;

unsigned int t_przeszkoda::_ilosc = 0;

t_przeszkoda::t_przeszkoda() : t_obiekt(string("przeszkoda") + char(_ilosc + '1') + string(".dat"))
{
    int x = rand() % 401 - 200;
    int y = rand() % 401 - 200;
    int z = rand() % 401 - 200;
    _size = rand() % 25 + 20;
    t_wektor tmp(x, y, z);
    t_wektor W(0, 0, 0);
    t_macierz M;
    globalne().push(W);
    globalne().push(W + (_size));
    M.Zamien(90, osz);
    globalne().push(W.obroc(M));
    globalne().push(W.obroc(M));
    globalne().push(W.obroc(M));
    M.Zamien(90, osx);
    globalne().push(W.obroc(M));
    M.Zamien(90, osz);
    globalne().push(W.obroc(M));
    globalne().push(W.obroc(M));
    globalne().push(W.obroc(M));
    globalne() = globalne() + tmp;
    save();
    _ilosc++;
}

// t_przeszkoda::t_przeszkoda(t_wektor tmp, float size) : t_obiekt(string("przeszkoda") + char(_ilosc + '1') + string(".dat"))
// {
//     t_wektor W(0, 0, 0);
//     t_macierz M;
//     nazwaosi os = osz;
//     globalne().push(W + (size / 2));
//     M.Zamien(90, os);
//     globalne().push(W.obroc(M));
//     globalne().push(W.obroc(M));
//     globalne().push(W.obroc(M));
//     os = osx;
//     M.Zamien(90, os);
//     globalne().push(W.obroc(M));
//     os = osz;
//     M.Zamien(90, os);
//     globalne().push(W.obroc(M));
//     globalne().push(W.obroc(M));
//     globalne().push(W.obroc(M));
//     globalne() = globalne() + tmp;
//     save();
//     _ilosc++;
// }

// t_przeszkoda t_przeszkoda::operator()(t_wektor tmp, float size)
// {
//     t_wektor W(0, 0, 0);
//     t_macierz M;
//     nazwaosi os = osz;
//     globalne().push(W + (size / 2));
//     M.Zamien(90, os);
//     globalne().push(W.obroc(M));
//     globalne().push(W.obroc(M));
//     globalne().push(W.obroc(M));
//     os = osx;
//     M.Zamien(90, os);
//     globalne().push(W.obroc(M));
//     os = osz;
//     M.Zamien(90, os);
//     globalne().push(W.obroc(M));
//     globalne().push(W.obroc(M));
//     globalne().push(W.obroc(M));
//     globalne() = globalne() + tmp;
//     _ilosc++;
//     save();
//     return *this;
// }

void t_przeszkoda::save()
{
    fstream plik;
    plik.open(nazwa().c_str(), ios::out);
    plik << globalne()[0 + 1]
         << globalne()[1 + 1]
         << globalne()[2 + 1]
         << globalne()[3 + 1]
         << globalne()[0 + 1]
         << globalne()[5 + 1]
         << globalne()[6 + 1]
         << globalne()[7 + 1]
         << globalne()[4 + 1]
         << globalne()[5 + 1]
         << globalne()[4 + 1]
         << globalne()[3 + 1]
         << globalne()[2 + 1]
         << globalne()[7 + 1]
         << globalne()[6 + 1]
         << globalne()[1 + 1];
    plik.close();
}
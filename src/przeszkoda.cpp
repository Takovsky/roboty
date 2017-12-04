#include <cstdlib> // rand()
#include <fstream> // zapis do pliku
#include "nazwaosi.hpp"
#include "macierz.hpp"
#include "obiekt.hpp"
#include "przeszkoda.hpp"


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
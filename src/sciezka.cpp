#include <fstream>
#include <vector>
#include "sciezka.hpp"

using namespace std;

unsigned int t_sciezka::_ilosc = 0;

t_sciezka::t_sciezka() : t_obiekt(string("sciezka") + char(_ilosc + '1') + string(".dat"))
{
    kasuj();
    ++_ilosc;
}

void t_sciezka::save()
{
    fstream plik;
    plik.open(nazwa().c_str(), ios::out);
    plik << "";
    for (auto pd = globalne().begin(); pd != globalne().end(); pd++)
        plik << *pd;
    plik.close();
}

void t_sciezka::kasuj()
{
    for (auto i = globalne().size(); i > 0; i--)
        pop();
    save();
}

float t_sciezka::dlugosc()
{
    float x = 0;
    for (auto pd = globalne().begin(); pd != (globalne().end() - 1); pd++)
    {
        x += *pd & *(pd + 1);
    }
    return x;
}

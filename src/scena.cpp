#include <vector> // vector
#include "wektor.hpp"
#include "figura.hpp"
#include "scena.hpp"

void t_scena::przesun(t_wektor W)
{
    for (auto d : roboty)
    {
        // przesuwamy kazdy obiekt o zadany wektor
        *d.first->get() = *d.first->get() + W;
        *d.second->get() = *d.second->get() + W;
    }
    for (auto d : przeszkody)
    {
        *d->get() = *d->get() + W;
    }
    _wektortranslacji = _wektortranslacji + W;
}

void t_scena::powroc()
{
    przesun(_wektortranslacji * -1);
    _wektortranslacji(0, 0, 0);
}

bool t_scena::kolizja(const unsigned int aktywny)
{
    float odl;
    for (auto pd = roboty.begin(); pd != roboty.end(); pd++)
    {
        odl = sqrt(pow((*(*roboty[aktywny].first).get())[0][0] - (*(*pd->first).get())[0][0], 2) +
                   pow((*(*roboty[aktywny].first).get())[0][1] - (*(*pd->first).get())[0][1], 2) +
                   pow((*(*roboty[aktywny].first).get())[0][2] - (*(*pd->first).get())[0][2], 2));
        if (pd == roboty.begin() + aktywny)
            continue;
        else if (odl <= (*roboty[aktywny].first).promien() + (*pd->first).promien())
            return true;
    }
    for (auto pd = przeszkody.begin(); pd != przeszkody.end(); pd++)
    {
        odl = sqrt(pow((*(*roboty[aktywny].first).get())[0][0] - (*(*pd)->get())[0][0], 2) +
                   pow((*(*roboty[aktywny].first).get())[0][1] - (*(*pd)->get())[0][1], 2) +
                   pow((*(*roboty[aktywny].first).get())[0][2] - (*(*pd)->get())[0][2], 2));
        if (odl <= (*roboty[aktywny].first).promien() + (*pd)->size())
            return true;
    }
    return false;
}

t_scena::~t_scena()
{
    for (; przeszkody.size() > 0;)
        przeszkody.pop_back();
    for (; roboty.size() > 0;)
        roboty.pop_back();
}
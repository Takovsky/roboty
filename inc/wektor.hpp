#ifndef WEKTORH
#define WEKTORH

#include <iostream> // ostream, istream
#include <cmath> // sqrt(),pow()
#include "macierz.hpp"

/*!
 *  \brief deinicja ilosc osi uzywanych w progamie
 */
#define IL_OSI 3

using namespace std;

/*!
 * \file wektor.hpp
 *  
 *  Plik zawiera definicję klasy t_wektor
 */

/*!
 * \brief klasa obsluguje wektor
 * 
 *  Klasa definiuje wektor, skladajacy sie z trzech wspolrzednych X,Y,Z,
 *  oraz metody dotyczace tej klasy
 */
class t_wektor
{
    /*!
 * wektor to tablica skladajaca sie z 3 wspolrzednych
 */
    float _wektor[IL_OSI];

  public:
    /*!
 * \brief konstruktor wetkora
 */
    t_wektor()
    {
        _wektor[0] = 0;
        _wektor[1] = 0;
        _wektor[2] = 0;
    }
    /*!
 * \brief konstruktor wektora wypelniajacy go od razu zadanymi wspolrzednymi
 */
    t_wektor(float x, float y, float z)
    {
        _wektor[0] = x;
        _wektor[1] = y;
        _wektor[2] = z;
    }
    /*!
 * \brief destruktor wektora
 */
    ~t_wektor() {}
    /*!
 * \brief operator indeksujacy
 * zwraca wektor od i
 */
    float operator[](int i) const { return _wektor[i]; }
    /*!
 * \brief operator indeksujacy
 * pozwala na zapis pod wektor od i
 */
    float &operator[](int i) { return _wektor[i]; }
    /*!
 * \brief operator funkcyjny
 * pozwala na nadpisanie wspolrzednych wetkora
 */
    t_wektor &operator()(float x, float y, float z)
    {
        _wektor[0] = x;
        _wektor[1] = y;
        _wektor[2] = z;
        return *this;
    }
    /*!
 * \brief operator &
 * zwraca odleglosc pomiedzy dwoma wektorami
 */
    float operator&(t_wektor W) { return sqrt(pow(_wektor[0] - W[0], 2) + pow(_wektor[1] - W[1], 2) + pow(_wektor[2] - W[2], 2)); }
    /*!
 * \brief operator dodawania wektora z wektorem
 */
    t_wektor operator+(t_wektor);
    /*!
 * \brief operator dodawania wektora z floatem
 */
    t_wektor operator+(float);
    /*!
 * \brief operator odejmowania wektora z wektorem
 */
    t_wektor operator-(t_wektor);
    /*!
 * \brief operator mnozenia wektora z floatem
 */
    t_wektor operator*(float);
    /*!
 * \brief operator dodawania wektora z macierza
 */
    t_wektor operator*(t_macierz);
    /*!
 * \brief metoda obracajaca wektor o zadana macierz
 */
    t_wektor obroc(t_macierz);
};

/*!
 * \brief operator wyswietlania wspolrzednych wektora
 */
ostream &operator<<(ostream &, t_wektor);
/*!
 * \brief operator wczytywania wektora
 */
istream &operator>>(istream &, t_wektor &);

#endif
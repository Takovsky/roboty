#ifndef MACIERZH
#define MACIERZH

#include "nazwaosi.hpp"

/*!
 * \file macierz.hpp
 *  
 *  Plik zawiera definicję klasy t_maicerz
 */

/*!
 * \brief Klasa obslugujaca macierz obrotu
 * 
 *  Klasa definiuje macierz 3x3 skladajaca sie z floatow 
 *  oraz metody dotyczace tej klasy
 */
class t_macierz
{
  /*!
 * \brief macierz to tablica 3x3
 */
  float _macierz[3][3];

public:
  /*!
 * \brief konstruktor macierzy
 */
  t_macierz() {}
  /*!
 * \brief destruktor macierzy
 */
  ~t_macierz() {}
  /*!
 * \brief operator funkcyjny
 * pozwala na podmienienie _macierz[i][j] zadana liczba
 */
  float &operator()(int i, int j) { return _macierz[i][j]; }
    /*!
 * \brief operator funkcyjny
 * zwraca macierz od 'i' i 'j'
 */
  float operator()(int i, int j) const { return _macierz[i][j]; }
    /*!
 * wypelnia macierz zaleznie od zadanego kata i osi
 */
  t_macierz Zamien(float, nazwaosi);
    /*!
 * \brief operator mnozenia macierzy z macierza
 */
  t_macierz operator*(t_macierz);
};

#endif
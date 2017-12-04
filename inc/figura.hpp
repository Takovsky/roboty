#ifndef FIGURAH
#define FIGURAH

#include <ostream> // ostream
#include <vector> // vector
#include "wektor.hpp"

/*!
 * \file  figura.hpp
 *  
 *  Plik zawiera definicję klasy t_figura
 */

/*!
 * \brief Klasa obslugujaca figure
 * 
 *  Klasa definiuje figure skladajaca sie z wektorow dynamicznie przypisywanych 
 *  oraz metody dotyczace tej klasy
 */
class t_figura : public vector<t_wektor>
{

public:
  /*!
 * \brief konstruktor figury
 */
  t_figura() {}
  /*!
 * \brief destruktor figury
 */
  ~t_figura() {}
  /*!
 * \brief operator dodawania figury z wektorem
 */
  t_figura operator+(t_wektor);
  /*!
 * \brief operator odejmowania figury z wektorem
 */
  t_figura operator-(t_wektor);
  /*!
 * \brief przeciazenie metody pushujacej do vectora
 */
  void push(t_wektor W) { push_back(W); }
  /*!
 * \brief przeciazenie metody popujacej z vectora
 */
  void pop() { pop_back(); }
};

/*!
 * \brief przeciazenie operatora wyswietlania dla figury
 */
ostream &operator<<(ostream &, t_figura);

#endif
#ifndef SCIEZKAH
#define SCIEZKAH

#include "obiekt.hpp"
#include "wektor.hpp"
/*!
 * \file sciezka.hpp
 *  
 *  Plik zawiera definicję klasy t_sciezka
 */

/*!
 * \brief klasa obsluguje sciezke
 * 
 *  Klasa definiuje sciezke, ktora dziedziczy po obiekcie
 *  oraz jej metody
 */
class t_sciezka : public t_obiekt
{
  static unsigned int _ilosc; // ilosc sciezek

public:
  /*!
 * \brief konstruktor sciezki
 */
  t_sciezka();
  /*!
 * \brief destruktor sciezki
 */
  virtual ~t_sciezka() {}
  /*!
 * \brief przeciazenie pushowania na vector sciezki
 */
  void push(t_wektor W) { globalne().push(W); }
  /*!
 * \brief przeciazenie popowania z vectora sciezu
 */
  void pop() { globalne().pop(); }
  /*!
 * \brief kasowanie sciezki
 */
  void kasuj();
  /*!
 * \brief metoda zapisujaca sciezke
 */
  void save();
  /*!
 * \brief metoda liczaca i zwracajaca dlugosc sciezki
 */
  float dlugosc();
};

#endif
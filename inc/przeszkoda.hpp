#ifndef PRZESZKODAH
#define PRZESZKODAH

#include "obiekt.hpp"

/*!
 * \file obiekt.hpp
 *  
 *  Plik zawiera definicję klasy t_przeszkoda
 */

/*!
 * \brief definicja klasy obslugujacej przeszkode
 * 
 *  Klasa definiuje przeszkode, ktora dziedziczy po obiekcie
 *  oraz jej metody
 */
class t_przeszkoda : public t_obiekt
{
  /*!
 * \brief static ilosc
 * ilosc wszystkich przeszkod, potrzebne do zapisu
 */
  static unsigned int _ilosc;
  int _size; // rozmiar przeszkody

public:
  /*!
 * \brief konstruktor przeszkody
 */
  t_przeszkoda();
  /*!
 * \brief destruktor przeszkody
 */
  ~t_przeszkoda() {}
  /*!
 * \brief metoda zwracajaca rozmiar obiektu
 */
  int size() const { return _size; }
  /*!
 * \brief metoda zapisujaca do pliku
 */
  void save();
};

#endif
#ifndef OBIEKTH
#define OBIEKTH

#include <string>
#include "figura.hpp"

/*!
 * \file obiekt.hpp
 *  
 *  Plik zawiera definicję klasy t_obiekt
 */

/*!
 * \brief klasa obsluguje obiekt graficzny
 * 
 *  Klasa definiuje obiekt, skladajacy sie z figury i przypisanej mu nazwy,
 *  oraz metody dotyczace tej klasy
 */
class t_obiekt
{
  t_figura _obiekt; // obiekt jest figura
  string _nazwa;    // i ma swoja nazwe

protected: // protected bo tylko klasy ktore dziedzicza maja miec do tego dostep
  /*!
 * metoda zwraca globalne wierzcholki figury
 */
  t_figura globalne() const { return _obiekt; }
  /*!
 * metoda pozwala na nadpisanie globalnych wierzcholkow figury
 */
  t_figura &globalne() { return _obiekt; }
  /*!
 * \brief konstruktor obiektu
 */
  t_obiekt() : _nazwa() {}
  /*!
 * \brief konstruktor obiektu
 * wymaga nazwy w liscie inicjalizacyjnej
 */
  t_obiekt(string nazwa) : _nazwa(nazwa) {}

  /*!
 * \brief destruktor obiektu
 */
  virtual ~t_obiekt() {}

public:
  /*!
 * \brief metoda zwracajaca nazwe obiektu
 */
  string nazwa() const { return _nazwa; }
  /*!
 * \brief metoda zwracajaca figure obiektu
 */
  t_figura *get() { return &_obiekt; }
  /*!
 * \brief wirtualna metoda zwracajaca promien(uzywana w robocie)
 */
  virtual float promien() const { return 0; }
  /*!
 * \brief wirtualna metoda zwracajaca rozmiar(przeszkody)
 */
  virtual int size() const { return 0; }
  /*!
 * \brief wirtualna metoda zapisujaca obiekt
 */
  virtual void save() = 0;
};

#endif
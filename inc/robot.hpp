#ifndef ROBOTH
#define ROBOTH

#include "wektor.hpp"
#include "figura.hpp"
#include "obiekt.hpp"

/*!
 * \file robot.hpp
 *  
 *  Plik zawiera definicję klasy t_robot
 */

/*!
 * \brief klasa obsluguje robota
 * 
 *  Klasa definiuje robota, ktora dziedziczy po obiekcie
 *  oraz jej metody
 */
class t_robot : public t_obiekt
{
  static unsigned int _ilosc; // ilosc robotow
  float _dlpromienia; // dl promienia robota
  t_wektor _punktzaczepienia; // wektor zaczepienia srodka robota w ukladzie wspolrzednych
  /*!
 * \brief kat nachylenia robota
 * w 3d kat jest macierza
 */
  t_macierz _kat;
  /*!
 * \brief lokalne wierzcholki robota
 */
  t_figura _lokalne;
  /*!
 * \brief predkosc robota
 */
  float _predkosc;
  /*!
 * \brief skala robota
 */
  float _skala;

public:
  /*!
 * \brief konstruktor robota
 */
  t_robot();
  // t_robot(t_wektor);
  /*!
 * \brief destruktor robota
 */
  ~t_robot() {}
  /*!
 * \brief operator funkcyjny
 * zwraca wierzcholek srodka robota
 */
  t_wektor operator()() const { return *globalne().begin(); }
  /*!
 * metoda obraca robota wzgledem jego srodka o zadana macierz
 */
  void obroc(t_macierz);
  /*!
 * metoda ustawia robota w punkcie zaczepienia
 */
  void ustaw();
  /*!
 * metoda zwraca promien robota
 */
  float promien() const { return _dlpromienia; }
  /*!
 * metoda jedzie robotem o jego predkosc
 */
  void move();
  /*!
 * metoda jedzie robotem o zadana odleglosc
 */
  void move(float);
  /*!
 * metoda pozwala na wczytywanie predkosci robota
 */
  float &predkosc() { return _predkosc; }
  /*!
 * metoda zwraca predkosc robota
 */
  float predkosc() const { return _predkosc; }
  /*!
 * metoda pozwala na wczytywanie skalai robota
 */
  float &skala() { return _skala; }
  /*!
 * metoda zwraca skala robota
 */
  float skala() const { return _skala; }
  /*!
 * metoda skaluje robota
 */
  void skaluj();
  /*!
 * metoda resetuje robota
 */
  void resetuj();
  /*!
 * przesuwa robota o zadany wektor
 */
  void przesun(t_wektor);
  /*!
 * metoda zapisuje robota do pliku
 */
  void save();
};

#endif
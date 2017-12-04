#ifndef SCENAH
#define SCENAH

#include <vector> // vector
#include <memory> // smart_ptr
#include "wektor.hpp"
#include "obiekt.hpp"
#include "robot.hpp"
#include "sciezka.hpp"
#include "przeszkoda.hpp"

using namespace std;

/*!
 * \file scena.hpp
 *  
 *  Plik zawiera definicję klasy t_scena
 */

/*!
 * \brief Klasa obslugujaca scene
 * 
 *  Klasa definiuje scene, ktora sklada sie z vectora wskaznikow na figury
 *  oraz jej metody
 */
class t_scena
{
  vector<pair<shared_ptr<t_obiekt>, shared_ptr<t_obiekt>>> roboty; // vector inteligentych wskaznikow na roboty i sciezki
  vector<shared_ptr<t_obiekt>> przeszkody;                         // vector inteligentych wskaznikow na przeszkod
  t_wektor _wektortranslacji;                                      // zapamietany wektor translacji

public:
  /*!
 * \brief konstruktor sceny
 */
  t_scena() { _wektortranslacji(0, 0, 0); }
  /*!
 * \brief destruktor sceny
 */
  ~t_scena();
  /*!
 * pushuje na scene inteligenty wskaznik na robota i sciezke
 */
  void push_robot(shared_ptr<t_obiekt> R, shared_ptr<t_obiekt> O2) { roboty.emplace_back(R, O2); }
  /*!
 * pushuje na scene inteligenty wskaznik na przeszkode
 */
  void push_przeszkoda(shared_ptr<t_obiekt> P) { przeszkody.push_back(P); }
  /*!
 * popuje robota wraz ze sciezka ze sceny
 */
  void pop_robot(int i) { roboty.erase(roboty.begin() + i, roboty.begin() + i + 1); }
  /*!
 * popuje przeszkode ze sceny
 */
  void pop_przeszkoda(int i) { przeszkody.erase(przeszkody.begin() + i, przeszkody.begin() + i + 1); }
  /*!
 * przesuwa scene o wektor
 */
  void przesun(t_wektor);
  /*!
 * sprawdza czy wystapila kolizja pomiedzy obiektami na scenie
 */
  bool kolizja(const unsigned int);
  /*!
 * przywraca scene do punktu wyjscia
 */
  void powroc();
  /*!
 * zwraca wektor translacji sceny
 */
  t_wektor wektor() const { return _wektortranslacji; }
};

#endif
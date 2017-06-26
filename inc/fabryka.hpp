#ifndef FABRYKAH
#define FABRYKAH

#include <memory>
#include "robot.hpp"
#include "sciezka.hpp"
#include "przeszkoda.hpp"
#include "obiekt.hpp"

/*!
 * \brief enum obslugujacy rodzaj obiektu 
 */
enum TypObiektu
{
    TO_Robot,
    TO_Sciezka,
    TO_Przeszkoda
};

/*!
 * \file  fabryka.hpp
 *  
 *  Plik zawiera definicję klasy t_fabryka
 */

/*!
 * \brief Klasa obslugujaca fabryke obiektow
 * 
 *  Klasa definiuje singleton fabryki obiektow
 */
class t_fabryka
{
    static t_fabryka _fabryka;
    /*!
 * \brief konstruktor fabryki
 */
    t_fabryka() {}
    shared_ptr<t_obiekt> utworzobiekt(TypObiektu TypOb) const
    {
        switch (TypOb)
        {
        case TO_Robot:
            return make_shared<t_robot>();
        case TO_Sciezka:
            return make_shared<t_sciezka>();
        case TO_Przeszkoda:
            return make_shared<t_przeszkoda>();
        }
        return NULL; // To tylko po to, aby kompilator
                     // nie twierdził, że metoda nic nie zwraca. Ta instrukcja
                     // i tak nigdy się nie wykona.
    }

  public:
    /*!
 * \brief destruktor fabryki
 */
    ~t_fabryka() {}
    /*!
 *  statyczna metoda zwracajaca shared_ptr z metody utworzobiekt
 */
    static shared_ptr<t_obiekt> zbuduj(TypObiektu TypOb)
    {
        return _fabryka.utworzobiekt(TypOb);
    }
};

#endif
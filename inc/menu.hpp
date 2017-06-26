#ifndef MENUH
#define MENUH

#include <ncurses.h> // window
#include <vector>
#include "robot.hpp"
#include "sciezka.hpp"
#include <memory>

/*!
 * \file  menu.hpp
 *  
 *  Plik zawiera definicję funkcji wyswietlajacych menu
 */

/*!
 * funkcja wyswietla menu w zadanym oknie, zaleznie od aktywnej opcji i czy wybrano
 */
void showmenu(WINDOW *, unsigned int, bool);
/*!
 * funkcja wyswietla menu w zadanym oknie, zaleznie od tego czy wybrano i aktywnego robota
 */
void showroboty(WINDOW *, bool, unsigned int, vector<pair<shared_ptr<t_robot>, shared_ptr<t_sciezka>>> &);
/*!
 * funkcja wyswietla informacje o programie
 */
void showinfo(WINDOW *, bool);

#endif
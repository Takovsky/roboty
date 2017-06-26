#include <ncurses.h> // obsluga menu
#include <cstring>   // c_str(), strlen()
#include <vector> 
#include <memory>
#include "menu.hpp"
#include "robot.hpp"
#include "sciezka.hpp"

void showinfo(WINDOW *programinfo, bool menu)
{
    int y = 1;
    const char *opis("Program operujacy robotem mobilnym"); // informacje wyswietlane nad menu
    const char *opis2("spacja zatwierdza wybor");           // cd
    const char *opis3(" << MENU");                          // cd
    const char *opis4("ROBOTY >> ");
    wclear(programinfo);
    box(programinfo, 0, 0);
    mvwprintw(programinfo, y++, getmaxx(programinfo) / 2 - strlen(opis) / 2, opis);   // printujemy info  o programie
    mvwprintw(programinfo, y++, getmaxx(programinfo) / 2 - strlen(opis2) / 2, opis2); // w zadanym miejscu
    if (menu)
    {
        wattron(programinfo, A_BOLD);
        mvwprintw(programinfo, y + 1, getmaxx(programinfo) / 2 - 12 /* - strlen(opis3) - 2*/, opis3); // w zadanym miejscu
        wattroff(programinfo, A_BOLD);
        mvwprintw(programinfo, y + 1, getmaxx(programinfo) / 2 + 2, opis4); // w zadanym miejscu
    }
    else
    {
        wattron(programinfo, A_BOLD);
        mvwprintw(programinfo, y + 1, getmaxx(programinfo) / 2 + 2, opis4); // w zadanym miejscu
        wattroff(programinfo, A_BOLD);
        mvwprintw(programinfo, y + 1, getmaxx(programinfo) / 2 - 12 /*- strlen(opis3) - 10*/, opis3); // w zadanym miejscu
    }
    mvwprintw(programinfo, y + 1, getmaxx(programinfo) / 2 - 4 /*- strlen(opis3) - 10*/, "      "); // w zadanym miejscu
    wrefresh(programinfo);
}

void showmenu(WINDOW *menu, unsigned int aktywny, bool wybrano)
{
    string opcje[] = {
        "(z) zmiana szybkosci ruchu",
        "(s) zmiana skali robota",
        "(o) obrot robota",
        "(j) jazda na wprost",
        "(r) resetuj robota i sciezke",
        "(l) obsluga strzalkami",
        "(d) dodaj przeszkode",
        "(u) usun wybrana przeszkode",
        "(t) zadaj translacje rysunku",
        "(p) pierwotne ustawienie rysunku",
        "(k) zakoncz dzialanie programu",
    };
    int x, y;
    y = 2;
    x = 3;
    wclear(menu);
    box(menu, 0, 0);
    if (wybrano)
    {
        y = aktywny;
        if (aktywny > 5)
        {
            y++;
            if (aktywny > 6)
                y++;
            if (aktywny > 8)
                y++;
        }
        wattron(menu, A_BOLD);
        mvwprintw(menu, y + 1, x, "%s", opcje[aktywny - 1].c_str());
        wattroff(menu, A_BOLD);
    }
    else
    {
        for (unsigned int i = 0; i < 11; i++)
        {
            if (y == 7 || y == 9 || y == 12 || y == 15)
                y++;
            if (aktywny == i + 1)
            {
                wattron(menu, A_BOLD);
                mvwprintw(menu, y, x, "%s", opcje[i].c_str());
                wattroff(menu, A_BOLD);
            }
            else
                mvwprintw(menu, y, x, "%s", opcje[i].c_str());
            y++;
        }
    }
    wrefresh(menu);
}

void showroboty(WINDOW *win, bool lewemenu, unsigned int aktywny, vector<pair<shared_ptr<t_robot>, shared_ptr<t_sciezka>>> &roboty)
{
    int x, y;
    y = 2;
    x = 3;
    wclear(win);
    if (!lewemenu)
    {
        box(win, 0, 0);
        for (unsigned int i = 0; i < roboty.size(); i++)
        {
            if (aktywny == i + 1)
            {
                wattron(win, A_BOLD);
                mvwprintw(win, y, x, ">> Robot %d.", i + 1);
                mvwprintw(win, y++, x + 21, "wsp. srodka: ", i + 1);
                wattroff(win, A_BOLD);
                mvwprintw(win, y, x + 22, "%.2f", (*roboty[i].first)()[0]);
                mvwprintw(win, y++, x, "szybkosc: %.2f", roboty[i].first->predkosc());
                mvwprintw(win, y, x + 22, "%.2f", (*roboty[i].first)()[1]);
                mvwprintw(win, y++, x, "skala:    %.2f", roboty[i].first->skala());
                mvwprintw(win, y, x + 22, "%.2f", (*roboty[i].first)()[2]);
                mvwprintw(win, y++, x, "sciezka:  %.2f", roboty[i].second->dlugosc());
            }
            else
            {
                mvwprintw(win, y, x, "Robot %d.", i + 1);
            }
            y++;
        }
        if (aktywny == roboty.size() + 1)
            wattron(win, A_BOLD);
        mvwprintw(win, y + 1, x, "  (d) dodaj robota");
        wattroff(win, A_BOLD);
        if (aktywny == roboty.size() + 2)
            wattron(win, A_BOLD);
        mvwprintw(win, y + 2, x, "  (u) usun robota");
        wattroff(win, A_BOLD);
    }
    else
    {
        x = getmaxx(win);
        wattron(win, A_BOLD);
        mvwprintw(win, y, x - 10, "Robot %d.", aktywny);
        mvwprintw(win, y + 2, x - 10, "wspol.");
        mvwprintw(win, y + 3, x - 10, "srodka");
        mvwprintw(win, y + 8, x - 10, "sciezka", roboty[aktywny - 1].second->dlugosc());
        mvwprintw(win, y + 11, x - 10, "szybkosc", roboty[aktywny - 1].first->predkosc());
        mvwprintw(win, y + 14, x - 10, "skala");
        wattroff(win, A_BOLD);
        mvwprintw(win, y + 4, x - 9, "%.2f", (*roboty[aktywny - 1].first)()[0]);
        mvwprintw(win, y + 5, x - 9, "%.2f", (*roboty[aktywny - 1].first)()[1]);
        mvwprintw(win, y + 6, x - 9, "%.2f", (*roboty[aktywny - 1].first)()[2]);
        mvwprintw(win, y + 9, x - 9, "%.2f", roboty[aktywny - 1].second->dlugosc());
        mvwprintw(win, y + 12, x - 9, "%.2f", roboty[aktywny - 1].first->predkosc());
        mvwprintw(win, y + 15, x - 9, "%.2f", roboty[aktywny - 1].first->skala());
    }
    wrefresh(win);
}
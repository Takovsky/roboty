#include <ncurses.h> // obsluga menu
#include <iostream>  // cerr
#include <cstring>   // string.c_str()
#include <vector>    // vector<>
#include <ctime>     // time(NULL)
#include <list>      // lista
#include <memory>    // shared_ptr, unique_ptr
#include <cstdlib>   // srand()
#include <unistd.h>  // usleep(), sleep()
#include "obiekt.hpp"
#include "figura.hpp"
#include "robot.hpp"
#include "wektor.hpp"
#include "sciezka.hpp"
#include "lacze_do_gnuplota.hpp"
#include "przeszkoda.hpp"
#include "macierz.hpp"
#include "scena.hpp"
#include "nazwaosi.hpp"
#include "menu.hpp"
#include "fabryka.hpp"

t_fabryka t_fabryka::_fabryka;

int main()
{
    srand(time(NULL));                                                                                                                             // zaczynamy losowac w tym miejscu
    WINDOW *menu;                                                                                                                                  // okno wyswietlajace menu
    WINDOW *robotinfo;                                                                                                                             // okno wyswietlajace informacje o robotach
    WINDOW *programinfo;                                                                                                                           // okno wyswietlajace informacje o programie
    const char *pch;                                                                                                                               // wykorzystane w strchr()
    const int menusize = 11;                                                                                                                       // ilosc opcji w menu
    unsigned int aktywny = 1;                                                                                                                      // aktywna opcja(nie wybrana), domyslnie jeden
    unsigned int aktywnyrobot = 1;                                                                                                                 // aktywny robot
    int znak;                                                                                                                                      // wczytywany znak z klawiatury
    int wiersze, kolumny;                                                                                                                          // wiersze i kolumny okna z menu
    const int sizex = 54;                                                                                                                          // szerokosc menu
    const int sizey = 20;                                                                                                                          // wysokosc menu
    unique_ptr<t_macierz> M(new t_macierz);                                                                                                        // obiekt macierzy
    t_wektor W(100, 23, -87);                                                                                                                      //
    vector<pair<shared_ptr<t_robot>, shared_ptr<t_sciezka>>> roboty;                                                                               // vector robotow
    roboty.emplace_back(static_pointer_cast<t_robot>(t_fabryka::zbuduj(TO_Robot)), static_pointer_cast<t_sciezka>(t_fabryka::zbuduj(TO_Sciezka))); // i sciezek
    roboty.emplace_back(static_pointer_cast<t_robot>(t_fabryka::zbuduj(TO_Robot)), static_pointer_cast<t_sciezka>(t_fabryka::zbuduj(TO_Sciezka))); //
    roboty.emplace_back(static_pointer_cast<t_robot>(t_fabryka::zbuduj(TO_Robot)), static_pointer_cast<t_sciezka>(t_fabryka::zbuduj(TO_Sciezka))); //
    vector<shared_ptr<t_obiekt>> przeszkody;                                                                                                       // vector przeszkod
    unique_ptr<t_scena> scena(new t_scena);                                                                                                        // obiekt sceny
    unique_ptr<PzG::LaczeDoGNUPlota> Lacze(new PzG::LaczeDoGNUPlota);                                                                              // obiekt lacza do gnuplota
    Lacze->ZmienTrybRys(PzG::TR_3D);                                                                                                               // zmieniamy rysowanie na 3d
    Lacze->UstawZakresY(-355, 355);                                                                                                                // zakres osiek
    Lacze->UstawZakresX(-355, 355);                                                                                                                //
    Lacze->UstawZakresZ(-305, 305);                                                                                                                //
    for (auto &d : roboty)
    {
        d.first->save();                                                      // zapisujemy robota
        d.second->push((*d.first)());                                         // wrzucamy wektor srodka roboa na sciezke
        d.second->save();                                                     // zapisujemy sciezke
        Lacze->DodajNazwePliku(d.first->nazwa().c_str(), PzG::RR_Ciagly, 1);  // dodajemy plik robota i sciezki do rysowania
        Lacze->DodajNazwePliku(d.second->nazwa().c_str(), PzG::RR_Ciagly, 1); // dodajemy plik robota i sciezki do rysowania
        scena->push_robot(d.first, d.second);                                 // pushujemy na scene
    }
    Lacze->ZmienSzerokoscRysowania(roboty[aktywnyrobot - 1].first->nazwa().c_str(), 2);  // aktywny robot i sciezka
    Lacze->ZmienSzerokoscRysowania(roboty[aktywnyrobot - 1].second->nazwa().c_str(), 2); // maja szerokosc rysowania 2
    const char opcje[]("zsojrldutp");                                                    // znaki uzywane do obslugi menu
    initscr();                                                                           // tworzymy okno
    getmaxyx(stdscr, wiersze, kolumny);                                                  // bierzemy wielkosci okna i zapisujemy
    if (kolumny < 54 || wiersze < 24)                                                    // jesli nasze okno jest za male
    {                                                                                    // zakoncz i poinformuj o tym
        refresh();                                                                       // odswiezamy okno
        endwin();                                                                        // konczymy
        cerr << "Potrzebny wiekszy ekran!" << endl;                                      // cerr
        return 0;                                                                        // wyjdz z programu
    }
    wiersze = wiersze / 2 + 3;                                                 // srodek menu
    kolumny = kolumny / 2;                                                     // srodek menu
    noecho();                                                                  // nie wyswietlamy wpisanych znakow
    cbreak();                                                                  // nie czekamy za echem
    programinfo = newwin(5, 54, wiersze - sizey / 2 - 5, kolumny - sizex / 2); // tworzymy okno z info o progamie
    robotinfo = newwin(20, 40, wiersze - sizey / 2, kolumny - sizex / 2 + 13); // tworzymy okno z menu obslugi
    menu = newwin(20, 40, wiersze - sizey / 2, kolumny - sizex / 2 + 1);       // tworzymy okno z menu robotow
    keypad(stdscr, TRUE);                                                      // klawiatura aktywna(znaki specjalne)
    refresh();                                                                 // odswiezamy
    bool wybrano = false;                                                      // bool mowiacy czy uzytkownik cos wybral
    bool lewemenu = true;                                                      // bool mowiacy w ktorym menu jestesmy
    showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);                     // wyswietl menu robotow
    showinfo(programinfo, lewemenu);                                           // wyswietl info
    showmenu(menu, aktywny, wybrano);                                          // wyswietl menu glowne
    Lacze->Rysuj();                                                            // rysujemy gnuplotem
    curs_set(0);                                                               // nie pokazuj kursora
    while (1)
    {
        noecho();
        showinfo(programinfo, lewemenu);
        nodelay(stdscr, TRUE);
        znak = getch();
        if (!lewemenu)
        {
            switch (znak) // MENU
            {
            case KEY_UP:               // strzalka w gore
                if (aktywnyrobot == 1) // zmieniamy tylko aktywna opcje
                    aktywnyrobot = roboty.size() + 2;
                else
                    --aktywnyrobot;
                break;
            case KEY_DOWN: // strzalka w dol analogicznie
                if (aktywnyrobot == roboty.size() + 2)
                    aktywnyrobot = 1;
                else
                    ++aktywnyrobot;
                break;
            case ' ':
                if (aktywnyrobot == roboty.size() + 1)
                {
                    roboty.emplace_back(static_pointer_cast<t_robot>(t_fabryka::zbuduj(TO_Robot)), static_pointer_cast<t_sciezka>(t_fabryka::zbuduj(TO_Sciezka))); // dorzuc przeszkode na vector przeszkod
                    roboty[roboty.size() - 1].first->save();
                    roboty[roboty.size() - 1].second->push((*roboty[roboty.size() - 1].first)());
                    roboty[roboty.size() - 1].second->save();
                    Lacze->DodajNazwePliku(roboty[roboty.size() - 1].first->nazwa().c_str(), PzG::RR_Ciagly, 1);  // dodajemy plik robota i sciezki do rysowania
                    Lacze->DodajNazwePliku(roboty[roboty.size() - 1].second->nazwa().c_str(), PzG::RR_Ciagly, 1); // dodajemy plik robota i sciezki do rysowania
                    scena->push_robot(roboty[roboty.size() - 1].first, roboty[roboty.size() - 1].second);         //
                    ++aktywnyrobot;
                }
                else if (aktywnyrobot == roboty.size() + 2)
                {
                    // showmenu(menu, aktywny, wybrano); // wyswietl nowe menu
                    if (roboty.size() <= 1)
                        break;
                    const char *info("STRZALKI - wybor");             // info
                    const char *info2("SPACJA   - zatwierdz ");       // info
                    const char *info3("ESCACPE  - anuluj");           // info
                    mvwprintw(robotinfo, aktywnyrobot + 4, 5, info);  // wyswietl info
                    mvwprintw(robotinfo, aktywnyrobot + 5, 5, info2); // wyswietl obecny wektor
                    mvwprintw(robotinfo, aktywnyrobot + 6, 5, info3); // wyswietl info
                    wrefresh(robotinfo);
                    unsigned int ktory = 0;
                    noecho(); // nie wyswietlaj co wpisywane
                    nodelay(stdscr, TRUE);
                    znak = 1;                         // resetuj znak
                    while (znak != ' ' && znak != 27) // dopoki nie klikniemy spacji lub l
                    {                                 // to jedz
                        switch (znak)                 // to zgodnie z nia obracaj robotem
                        {
                        case KEY_DOWN:
                        case KEY_RIGHT: //prawo
                            if (ktory == roboty.size() - 1)
                                ktory = 0;
                            else
                                ++ktory;
                            break;
                        case KEY_UP:
                        case KEY_LEFT: // lewo
                            if (ktory == 0)
                                ktory = roboty.size() - 1;
                            else
                                --ktory;
                            break;
                        }
                        Lacze->UsunNazwe(roboty[ktory].first->nazwa().c_str());
                        Lacze->UsunNazwe(roboty[ktory].second->nazwa().c_str());
                        Lacze->Rysuj();
                        for (int i = 0; i < 1000; i++)
                        {
                            usleep(600);
                            znak = getch();
                            if (znak == 27 || znak == ' ' || znak == KEY_LEFT || znak == KEY_RIGHT || znak == KEY_UP || znak == KEY_DOWN)
                                break;
                        }
                        if (znak != ' ')
                        {
                            Lacze->DodajNazwePliku(roboty[ktory].first->nazwa().c_str(), PzG::RR_Ciagly, 1);
                            Lacze->DodajNazwePliku(roboty[ktory].second->nazwa().c_str(), PzG::RR_Ciagly, 1);
                        }
                        Lacze->Rysuj();
                        for (int i = 0; i < 1000; i++)
                        {
                            usleep(600);
                            if (znak == 27 || znak == ' ' || znak == KEY_LEFT || znak == KEY_RIGHT || znak == KEY_UP || znak == KEY_DOWN)
                                break;
                        }
                        if (znak == ' ')
                        {
                            roboty.erase(roboty.begin() + ktory, roboty.begin() + ktory + 1);
                            scena->pop_robot(ktory);
                        }
                    }
                    nodelay(stdscr, FALSE);
                    --aktywnyrobot;
                    break;
                }
                else
                {
                    lewemenu = true;
                    showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
                    showmenu(menu, aktywny, wybrano); // pokaz menu
                }
                break;
            case KEY_LEFT:
            case KEY_RIGHT:
                if (aktywnyrobot > roboty.size())
                    aktywnyrobot = roboty.size();
                lewemenu = true;
                showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
                showmenu(menu, aktywny, wybrano); // pokaz menu
                break;
            }
            for (unsigned int i = 0; i < roboty.size(); i++)
            {
                Lacze->ZmienSzerokoscRysowania(roboty[i].first->nazwa().c_str(), 1);
                Lacze->ZmienSzerokoscRysowania(roboty[i].second->nazwa().c_str(), 1);
                if (i == (aktywnyrobot - 1))
                {
                    Lacze->ZmienSzerokoscRysowania(roboty[i].first->nazwa().c_str(), 2);
                    Lacze->ZmienSzerokoscRysowania(roboty[i].second->nazwa().c_str(), 2);
                }
            }
            Lacze->Rysuj();
            showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
        }
        else
        {
            nodelay(stdscr, FALSE);
            switch (znak) // MENU
            {
            case KEY_UP:          // strzalka w gore
                wybrano = false;  // nic nie wybralismy
                if (aktywny == 1) // zmieniamy tylko aktywna opcje
                    aktywny = menusize;
                else
                    --aktywny;
                break;
            case KEY_DOWN: // strzalka w dol analogicznie
                wybrano = false;
                if (aktywny == menusize)
                    aktywny = 1;
                else
                    ++aktywny;
                break;
            case KEY_LEFT:
            case KEY_RIGHT:
                lewemenu = false;
                showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
                break;
            }
            if ((pch = strchr(opcje, znak)) || znak == ' ') // jesli wpisalismy znak obslugujacy menu, lub wcisnelismy spacje
            {                                               //
                wybrano = true;                             // to cos wybralismy
                echo();                                     // i chcemy widziec co teraz wpisujemy
                if (strchr(opcje, znak))                    // jesli klinieto znak z "zsojrldutp", to ustaw aktywny na opcje
                    aktywny = pch - opcje + 1;              // ktora ten znak obsluguje
                switch (aktywny)                            // switchujemy zaleznie co wybralismy
                {
                case 1: // z - zmiana predkosci
                {
                    const char *info("obecna szybkosc wynosi: "); // info dla uzytkownika
                    const char *info2("wczytaj szybkosc > ");     //
                    curs_set(1);
                    showmenu(menu, aktywny, wybrano);                                  // pokaz nowe menu
                    mvwprintw(menu, aktywny + 2, 5, info, aktywny);                    // wyswietl info
                    wprintw(menu, "%.2f", roboty[aktywnyrobot - 1].first->predkosc()); // i obecna predkosc
                    mvwprintw(menu, aktywny + 3, 5, info2, aktywny);                   // info
                    wscanw(menu, "%f", &roboty[aktywnyrobot - 1].first->predkosc());   // i wczytaj
                    showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
                    curs_set(0);
                    break;
                }
                case 2: // s - skalowanie
                {
                    const char *info("obecna skala wynosi: "); // analogicznie
                    const char *info2("wczytaj skale > ");
                    curs_set(1);
                    showmenu(menu, aktywny, wybrano);
                    mvwprintw(menu, aktywny + 2, 5, info, aktywny);
                    wprintw(menu, "%.2f", roboty[aktywnyrobot - 1].first->skala());
                    mvwprintw(menu, aktywny + 3, 5, info2, aktywny);
                    wscanw(menu, "%f", &roboty[aktywnyrobot - 1].first->skala());
                    roboty[aktywnyrobot - 1].first->skaluj(); // skaluj
                    showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
                    curs_set(0);
                    break;
                }
                case 3: // o - obrot
                {
                    char oska = 'x';                        // zmienna do wczytywania osi obrotu
                    float kat = 0;                          // zmienna do wczytywania kata
                    list<pair<float, nazwaosi>> dane;       // lista wczytanych danych
                    nazwaosi tab[IL_OSI] = {osx, osy, osz}; // tabela osi
                    const char *info("Podaj os(xyz) i kat");
                    const char *info2("Znak kropki konczy wczytywanie");
                    const char *info3("> "); // informacje dla uzytkownika
                    curs_set(1);
                    showmenu(menu, aktywny, wybrano);                  // pokaz nowe menu
                    mvwprintw(menu, aktywny + 2, 5, info, aktywny);    // wyswietl informacje
                    mvwprintw(menu, aktywny + 3, 5, info2, aktywny);   // wyswietl informacje
                    mvwprintw(menu, aktywny + 4, 5, info3, aktywny);   //
                    mvwprintw(menu, aktywny + 5, 5, "Wczytane dane:"); //wczytuj dane
                    for (int licz = 0; oska != '.';)                   // dopoki nie wczytasz kropki
                    {
                        mvwscanw(menu, aktywny + 4, 5 + strlen(info3), "%c%f", &oska, &kat); // wczytujemy zawsze w tej samej linii
                        if (strchr("xyz", oska) && kat != 0)                                 // jesli wczytano dobrze
                        {                                                                    //
                            dane.emplace_back(kat, tab[oska - 'x']);                         // zapisz i wyswietl pod, co wczytano
                            mvwprintw(menu, aktywny + 6 + licz, 5, "                  ");
                            mvwprintw(menu, aktywny + 6 + licz++, 5, "%c %.2f", oska, kat); // licz++ - idziemy o linie w dol
                        }
                        else if (oska != '.')                                             // jesli wczytano zle
                        {                                                                 //
                            mvwprintw(menu, aktywny + 6 + licz, 5, "Podano bledne dane"); // poinformuj
                        }
                        mvwprintw(menu, aktywny + 4, 5 + strlen(info3), "                  "); // wymaz linijkie z ktorej wczytywano
                        kat = 0;                                                               // resetuj kat
                    }
                    curs_set(0);
                    int licz = 0;
                    for (auto d : dane) // dla wszystkich danych
                    {
                        M->Zamien(roboty[aktywnyrobot - 1].first->predkosc(), d.second);                 // zamieniaj pokolei macierz
                        for (int i = (d.first / roboty[aktywnyrobot - 1].first->predkosc()); i > 0; i--) // obracaj zgodnie z predkoscia robota
                        {
                            roboty[aktywnyrobot - 1].first->obroc(*M); // i obracaj
                            roboty[aktywnyrobot - 1].first->save();    // i zapisuj
                            Lacze->Rysuj();                            // i rysuj
                            usleep(4000);                              // i poczekaj chwilke
                        }
                        if (fmod(d.first, roboty[aktywnyrobot - 1].first->predkosc()) != 0)                 // wczytany kat % predkosc != 0
                        {                                                                                   //
                            M->Zamien(fmod(d.first, roboty[aktywnyrobot - 1].first->predkosc()), d.second); // obroc na koncu o ta koncowke
                            roboty[aktywnyrobot - 1].first->obroc(*M);
                            roboty[aktywnyrobot - 1].first->save();
                        }
                        mvwprintw(menu, aktywny + 6 + licz++, 5, "                  ");
                        wrefresh(menu);
                    }
                    dane.clear(); // zdejmij wszystkie dane z listy
                    break;
                }
                case 4: // j - jazda
                {
                    float x; // odleglosc
                    bool kolizja = false;
                    const char *info("wczytaj odleglosc > "); // info
                    curs_set(1);
                    showmenu(menu, aktywny, wybrano);               // wyswietl nowe menu
                    mvwprintw(menu, aktywny + 2, 5, info, aktywny); //pokaz info
                    wscanw(menu, "%f", &x);                         // wczytaj odleglosc
                    curs_set(0);
                    robotinfo = newwin(20, 12, wiersze - sizey / 2, kolumny - sizex / 2 + 41);
                    wrefresh(robotinfo);
                    for (int i = (x / roboty[aktywnyrobot - 1].first->predkosc()); i > 0; i--) // jedz zgodnie z predkoscia roboty[aktywnyrobot-1].firsta
                    {
                        roboty[aktywnyrobot - 1].first->move();                                     // jedz
                        roboty[aktywnyrobot - 1].first->save();                                     // zapisz
                        roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)()); // wrzuc na sciezke
                        roboty[aktywnyrobot - 1].second->save();                                    // zapisz sciezke
                        showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
                        Lacze->Rysuj();                         // rysuj
                        roboty[aktywnyrobot - 1].second->pop(); // zdejmij ze sciezki, zeby nie bylo na niej tysiecy linijek
                        usleep(5000);                           // chwile spij
                        if (scena->kolizja(aktywnyrobot - 1))
                        {
                            kolizja = true;
                            break;
                        }
                    }
                    if (fmod(x, roboty[aktywnyrobot - 1].first->predkosc()) != 0) // jesli odleglosc%predkosc != 0
                    {                                                             // analogicznie jak w obrocie
                        roboty[aktywnyrobot - 1].first->move(fmod(x, roboty[aktywnyrobot - 1].first->predkosc()));
                        roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)());
                        if (scena->kolizja(aktywnyrobot - 1))
                        {
                            kolizja = true;
                            break;
                        }
                    }
                    roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)()); // i teraz wrzuc na sciezke wektor, w ktorym robot sie zatrzymal
                    if (kolizja)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            Lacze->UsunNazwe(roboty[aktywnyrobot - 1].first->nazwa().c_str());
                            Lacze->Rysuj();
                            usleep(600000);
                            Lacze->DodajNazwePliku(roboty[aktywnyrobot - 1].first->nazwa().c_str(), PzG::RR_Ciagly, 2); // dodajemy plik robota i sciezki do rysowania
                            Lacze->Rysuj();
                            usleep(600000);
                        }
                    }
                    robotinfo = newwin(20, 40, wiersze - sizey / 2, kolumny - sizex / 2 + 13); // tworzymy okno z menu
                    showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
                    if (!kolizja)
                        break;
                }
                case 5: // r - resetuj
                {
                    roboty[aktywnyrobot - 1].first->predkosc() = 1;
                    roboty[aktywnyrobot - 1].first->skala() = 1;
                    roboty[aktywnyrobot - 1].first->resetuj(); // resetuj robota, wez pod uwage translacje sceny
                    roboty[aktywnyrobot - 1].first->ustaw();   // resetuj robota, wez pod uwage translacje sceny
                    roboty[aktywnyrobot - 1].first->przesun(scena->wektor());
                    roboty[aktywnyrobot - 1].second->kasuj(); // kasuj sciezke
                    roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)());
                    showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
                    break;
                }
                case 6: // l - obsluga strzalkami
                {
                    bool kolizja = false;
                    noecho();
                    const char *info("by zatrzymac robota");                                   // nie wyswietlaj co wpisywane
                    const char *info2("kliknij ponownie spacje lub 'l'");                      // info
                    showmenu(menu, aktywny, wybrano);                                          // pokaz nowe menu
                    mvwprintw(menu, aktywny + 3, 4, info, aktywny);                            // wyswietl info
                    mvwprintw(menu, aktywny + 4, 4, info2, aktywny);                           // wyswietl info
                    wrefresh(menu);                                                            //
                    znak = 1;                                                                  // resetuj znak
                    nodelay(stdscr, TRUE);                                                     // nie czekaj za kliknieciem
                    robotinfo = newwin(20, 12, wiersze - sizey / 2, kolumny - sizex / 2 + 41); //
                    wrefresh(robotinfo);                                                       //
                    while (znak != ' ' && znak != 'l')                                         // dopoki nie klikniemy spacji lub l
                    {                                                                          // to jedz
                        znak = getch();                                                        // jesli pobierzemy strzalke
                        switch (znak)                                                          // to zgodnie z nia obracaj robotem
                        {
                        case KEY_UP:                                                                    //gora
                            M->Zamien(3.6 * roboty[aktywnyrobot - 1].first->predkosc(), osx);           // podmien macierz
                            roboty[aktywnyrobot - 1].first->obroc(*M);                                  // obroc robota
                            roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)()); // wrzuc na sciezke
                            roboty[aktywnyrobot - 1].first->save();                                     // zapisz
                            Lacze->Rysuj();                                                             // rysuj
                            break;
                        case KEY_DOWN: //dol
                            M->Zamien(3.6 * roboty[aktywnyrobot - 1].first->predkosc(), osy);
                            roboty[aktywnyrobot - 1].first->obroc(*M);
                            roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)());
                            roboty[aktywnyrobot - 1].first->save();
                            Lacze->Rysuj();
                            break;
                        case KEY_RIGHT: //prawo
                            M->Zamien(3.6 * roboty[aktywnyrobot - 1].first->predkosc(), osz);
                            roboty[aktywnyrobot - 1].first->obroc(*M);
                            roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)());
                            roboty[aktywnyrobot - 1].first->save();
                            Lacze->Rysuj();
                        case KEY_LEFT: // lewo
                            M->Zamien(3.6 * roboty[aktywnyrobot - 1].first->predkosc(), osz);
                            roboty[aktywnyrobot - 1].first->obroc(*M);
                            roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)());
                            roboty[aktywnyrobot - 1].first->save();
                            Lacze->Rysuj();
                            break;
                        }
                        roboty[aktywnyrobot - 1].first->move();                                     // jedz
                        roboty[aktywnyrobot - 1].first->save();                                     // zapisz
                        roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)()); // wrzuc sciezke
                        roboty[aktywnyrobot - 1].second->save();                                    // zapisz
                        showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
                        Lacze->Rysuj();                         // rysuj
                        roboty[aktywnyrobot - 1].second->pop(); // zdejmij ostatni ze sciezki
                        usleep(5000);                           // czekaj
                        if (scena->kolizja(aktywnyrobot - 1))
                        {
                            kolizja = true;
                            break;
                        }
                    }
                    roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)()); // na koncu wrzuc na sciezke miejsce zatrzymania sie robota
                    roboty[aktywnyrobot - 1].second->save();                                    // zapisz sciezke
                    if (kolizja)
                    {
                        for (int i = 0; i < 3; i++)
                        {
                            Lacze->UsunNazwe(roboty[aktywnyrobot - 1].first->nazwa().c_str());
                            Lacze->Rysuj();
                            usleep(600000);
                            Lacze->DodajNazwePliku(roboty[aktywnyrobot - 1].first->nazwa().c_str(), PzG::RR_Ciagly, 2); // dodajemy plik robota i sciezki do rysowania
                            Lacze->Rysuj();
                            usleep(600000);
                        }
                        roboty[aktywnyrobot - 1].first->predkosc() = 1;
                        roboty[aktywnyrobot - 1].first->skala() = 1;
                        roboty[aktywnyrobot - 1].first->resetuj(); // resetuj robota, wez pod uwage translacje sceny
                        roboty[aktywnyrobot - 1].first->ustaw();   // resetuj robota, wez pod uwage translacje sceny
                        roboty[aktywnyrobot - 1].first->przesun(scena->wektor());
                        roboty[aktywnyrobot - 1].second->kasuj(); // kasuj sciezke
                        roboty[aktywnyrobot - 1].second->push((*roboty[aktywnyrobot - 1].first)());
                    }
                    robotinfo = newwin(20, 40, wiersze - sizey / 2, kolumny - sizex / 2 + 13); // tworzymy okno z menu
                    showroboty(robotinfo, lewemenu, aktywnyrobot, roboty);
                    nodelay(stdscr, FALSE); // i wylacz nodelay()
                    echo();                 // i wlacz echo
                    break;
                }
                case 7: // d - dodaj przeszkode
                {
                    przeszkody.push_back(t_fabryka::zbuduj(TO_Przeszkoda));                                        // dorzuc przeszkode na vector przeszkod
                    Lacze->DodajNazwePliku(przeszkody[przeszkody.size() - 1]->nazwa().c_str(), PzG::RR_Ciagly, 1); // dodaj plik do rysowania
                    scena->push_przeszkoda(przeszkody[przeszkody.size() - 1]);                                     // wrzuc na scene
                    break;
                }
                case 8: // u - usun przeszkode
                {
                    // showmenu(menu, aktywny, wybrano); // wyswietl nowe menu
                    if (przeszkody.size() < 1)
                        break;
                    const char *info("STRZALKI - wybor");       // info
                    const char *info2("SPACJA   - zatwierdz "); // info
                    const char *info3("ESCACPE  - anuluj");     // info
                    showmenu(menu, aktywny, wybrano);           // wyswietl nowe menu
                    mvwprintw(menu, aktywny + 4, 5, info);      // wyswietl info
                    mvwprintw(menu, aktywny + 5, 5, info2);     // wyswietl obecny wektor
                    mvwprintw(menu, aktywny + 6, 5, info3);     // wyswietl info
                    wrefresh(menu);
                    unsigned int ktora = 0;
                    noecho(); // nie wyswietlaj co wpisywane
                    // const char *info("kliknij ponownie spacje lub 'l', by zatrzymac robota"); // info
                    // showmenu(menu, aktywny, wybrano);                                         // pokaz nowe menu
                    // mvwprintw(menu, aktywny + 2, 14, info, aktywny);                          // wyswietl info
                    nodelay(stdscr, TRUE);
                    znak = 1;                         // resetuj znak
                    while (znak != ' ' && znak != 27) // dopoki nie klikniemy spacji lub l
                    {                                 // to jedz
                        switch (znak)                 // to zgodnie z nia obracaj robotem
                        {
                        case KEY_DOWN:
                        case KEY_RIGHT: //prawo
                            if (ktora == przeszkody.size() - 1)
                                ktora = 0;
                            else
                                ++ktora;
                            break;
                        case KEY_UP:
                        case KEY_LEFT: // lewo
                            if (ktora == 0)
                                ktora = przeszkody.size() - 1;
                            else
                                --ktora;
                            break;
                        }
                        Lacze->UsunNazwe(przeszkody[ktora]->nazwa().c_str());
                        Lacze->Rysuj();
                        for (int i = 0; i < 1000; i++)
                        {
                            usleep(600);
                            znak = getch();
                            if (znak == 27 || znak == ' ' || znak == KEY_LEFT || znak == KEY_RIGHT || znak == KEY_UP || znak == KEY_DOWN)
                                break;
                        }
                        if (znak != ' ')
                            Lacze->DodajNazwePliku(przeszkody[ktora]->nazwa().c_str(), PzG::RR_Ciagly, 1);
                        Lacze->Rysuj();
                        for (int i = 0; i < 1000; i++)
                        {
                            usleep(600);
                            if (znak == 27 || znak == ' ' || znak == KEY_LEFT || znak == KEY_RIGHT || znak == KEY_UP || znak == KEY_DOWN)
                                break;
                        }
                        if (znak == ' ')
                        {
                            przeszkody.erase(przeszkody.begin() + ktora, przeszkody.begin() + ktora + 1);
                            scena->pop_przeszkoda(ktora);
                        }
                    }
                    nodelay(stdscr, FALSE);
                    break;
                }
                case 9: // t - translacja rysunku
                {
                    t_wektor W;
                    float x, y, z;
                    x = scena->wektor()[0]; // podmien wartosci x y z z obecnym wektorem translacji
                    y = scena->wektor()[1];
                    z = scena->wektor()[2];
                    const char *info("obecny wektor translacji wynosi: "); // info
                    const char *info2("wczytaj wektor > ");                // info
                    curs_set(1);
                    showmenu(menu, aktywny, wybrano);                               // wyswietl nowe menu
                    mvwprintw(menu, aktywny + 5, 5, info);                          // wyswietl info
                    mvwprintw(menu, aktywny + 6, 5, "%.2f   %.2f   %.2f", x, y, z); // wyswietl obecny wektor
                    mvwprintw(menu, aktywny + 7, 5, info2);                         // wyswietl info
                    wscanw(menu, "%f%f%f", &x, &y, &z);                             // wczytaj wartosci
                    curs_set(0);
                    W[0] = x; // przypisz wartosci do wektora
                    W[1] = y;
                    W[2] = z;
                    scena->przesun(W); // przesun o ten wektor
                    break;
                }
                case 10: // p - powrot translacji
                {
                    scena->powroc(); // powroc do poczatkowego ustawienia sceny
                    break;
                }
                case 11:
                {
                    echo();    // wlacz echo
                    refresh(); // odswiez
                    endwin();  // zakoncz okno
                    exit(0);   // wyjdz z programu
                }
                } // co krok
                for (auto d : roboty)
                {
                    d.first->save();  // zapisz robota
                    d.second->save(); // sciezie
                }
                for (auto pd = przeszkody.begin(); pd != przeszkody.end(); pd++) // przeszkody
                    (*pd)->save();
                Lacze->Rysuj();  // rysuj
                wybrano = false; // i nie wybrano
            }
            if (lewemenu)
                showmenu(menu, aktywny, wybrano); // pokaz menu
            if (znak == 'k')                      // jesli k - wyjdz
                break;
        }
    }
    echo();    // echo
    refresh(); // odswiez
    endwin();  // zakoncz okno
}
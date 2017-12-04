CPP = g++ -Wall -pedantic -std=c++11 -c -g -Iinc

# start: roboty
# 	./roboty

roboty: obj obj/sciezka.o obj/lacze_do_gnuplota.o obj/robot.o obj/wektor.o obj/main.o obj/przeszkoda.o obj/figura.o  obj/macierz.o obj/scena.o obj/menu.o
	g++ obj/sciezka.o obj/lacze_do_gnuplota.o obj/robot.o obj/wektor.o obj/main.o obj/przeszkoda.o obj/figura.o obj/macierz.o obj/scena.o obj/menu.o -lncurses -o roboty

obj:
	mkdir obj

obj/main.o: src/main.cpp
	${CPP} src/main.cpp -o obj/main.o

obj/menu.o: src/menu.cpp
	${CPP} src/menu.cpp -lncurses -o obj/menu.o

obj/macierz.o: src/macierz.cpp inc/macierz.hpp
	${CPP} src/macierz.cpp -o obj/macierz.o

obj/scena.o: inc/scena.hpp src/scena.cpp
	${CPP} src/scena.cpp -o obj/scena.o

obj/figura.o: src/figura.cpp inc/figura.hpp
	${CPP} src/figura.cpp -o obj/figura.o

obj/sciezka.o: inc/sciezka.hpp src/sciezka.cpp
	${CPP} src/sciezka.cpp -o obj/sciezka.o

obj/wektor.o: inc/wektor.hpp src/wektor.cpp
	${CPP} src/wektor.cpp -o obj/wektor.o

obj/robot.o: inc/robot.hpp src/robot.cpp
	${CPP} src/robot.cpp -o obj/robot.o

obj/lacze_do_gnuplota.o: inc/lacze_do_gnuplota.hpp src/lacze_do_gnuplota.cpp
	${CPP} src/lacze_do_gnuplota.cpp -o obj/lacze_do_gnuplota.o

obj/przeszkoda.o: src/przeszkoda.cpp inc/przeszkoda.hpp
	${CPP} src/przeszkoda.cpp -o obj/przeszkoda.o

clean:
	rm -rf obj roboty *.dat
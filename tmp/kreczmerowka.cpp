#include <iostream>
#include <vector>
#include <list>

using namespace std;
float x;

class KlasaLiczby
{
    float _Liczba;

  public:
    float PobierzLiczbe() const { return _Liczba; }
    float &PobierzLiczbe() { return _Liczba; }
};

void Dzialaj(const KlasaLiczby Lx){};

int main()
{
    KlasaLiczby Li;
    Dzialaj(Li);
}

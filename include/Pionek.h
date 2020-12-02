#ifndef PIONEK_H
#define PIONEK_H
#include <SFML/Graphics.hpp>


class Pionek
{
    public:
        Pionek(sf::Sprite nowysprite, int nr_gracza, int nr_pionka);
        Pionek();
        ~Pionek() = default;

        sf::Sprite sprite;
        int nr_gracz;
        int nr_pionek;
        int static pozycje_na_planszy[40][2];
        int static pozycje_startowe[4][4][2];

        void ruch(int odleglosc);
        int pozycja();
        void start();

    protected:

    private:

};

#endif // PIONEK_H

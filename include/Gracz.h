#ifndef GRACZ_H
#define GRACZ_H
#include <stdio.h>
#include <iostream>
#include <Pionek.h>


class Gracz
{
    public:
        Gracz(std::vector<Pionek> lista, int nr);
        Gracz() = delete;
        ~Gracz() = default;

        std::vector<Pionek> lista_pionkow;
        int nr_gracza;
        static std::vector<Gracz> lista_graczy;

    protected:

    private:
};

#endif // GRACZ_H

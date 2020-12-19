#include "Gracz.h"

Gracz::Gracz(std::vector<Pionek> lista, int nr)
{
    nr_gracza = nr;
    lista_pionkow = lista;
    po_losowaniu = false;
}

bool Gracz::pionek_na_planszy(){

    for(Pionek &pionek : lista_pionkow){

        if(!pionek.skonczyl()&&!pionek.w_domu()){
            return true;
        }


    }
    return false;

}

bool Gracz::czy_wygral(){

    for(Pionek &pionek : lista_pionkow){

        if(!pionek.skonczyl()){
            return false;
        }

    }
    return  true;

}


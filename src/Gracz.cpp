#include "Gracz.h"

Gracz::Gracz(std::vector<Pionek> lista, int nr)
{
    nr_gracza = nr;
    lista_pionkow = lista;
    po_losowaniu = false;
}


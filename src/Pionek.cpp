#include "Pionek.h"
#include<SFML/Graphics.hpp>
#include <Gracz.h>

Pionek::Pionek(sf::Sprite nowysprite, int nr_gracza, int nr_pionka)
{
    sprite = nowysprite;
    nr_gracz = nr_gracza;
    nr_pionek = nr_pionka;


}


void Pionek::ruch(int odleglosc){

    if(odleglosc<7&&odleglosc>0){
            bool sprawdz = false;
            for (Gracz &gracz : Gracz::lista_graczy){
                for(Pionek &pionek : gracz.lista_pionkow){
                    if(pionek.sprite.getPosition().x==pozycje_na_planszy[pozycja()+odleglosc][0]&&pionek.sprite.getPosition().y==pozycje_na_planszy[pozycja()+odleglosc][1]){
                        pionek.sprite.setPosition(pozycje_startowe[pionek.nr_gracz][pionek.nr_pionek][0]-17,pozycje_startowe[pionek.nr_gracz][pionek.nr_pionek][1]-22);
                        sprawdz=true;
                        break;
                    }
                }
                if(sprawdz){
                    break;
                }
            }
            sprite.setPosition(pozycje_na_planszy[pozycja()+odleglosc][0],pozycje_na_planszy[pozycja()+odleglosc][1]);
    }


}

int Pionek::pozycja(){

    int pozycja = 0;

    for(int i = 0;i<40;i++){
        if(pozycje_na_planszy[i][0]==sprite.getPosition().x&&pozycje_na_planszy[i][1]==sprite.getPosition().y){
            pozycja=i;
            break;
        }
    }
    return pozycja;

}

void Pionek::start(){

    sprite.setPosition(pozycje_na_planszy[nr_gracz*10][0], pozycje_na_planszy[nr_gracz*10][1]);

}





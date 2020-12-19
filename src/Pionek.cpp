#include "Pionek.h"
#include<SFML/Graphics.hpp>
#include <Gracz.h>
#include <iostream>
#include <stdio.h>

Pionek::Pionek(sf::Sprite nowysprite, int nr_gracza, int nr_pionka)
{
    sprite = nowysprite;
    nr_gracz = nr_gracza;
    nr_pionek = nr_pionka;
    czy_wystartowal = false;


}


void Pionek::ruch(int odleglosc){

    if(odleglosc<7&&odleglosc>0){
            bool sprawdz = false;
            for (Gracz &gracz : Gracz::lista_graczy){
                for(Pionek &pionek : gracz.lista_pionkow){
                    if(pionek.sprite.getPosition().x==pozycje_na_planszy[pozycja()+odleglosc][0]&&pionek.sprite.getPosition().y==pozycje_na_planszy[pozycja()+odleglosc][1]){
                        pionek.sprite.setPosition(pozycje_startowe[pionek.nr_gracz][pionek.nr_pionek][0]-17,pozycje_startowe[pionek.nr_gracz][pionek.nr_pionek][1]-22);
                        pionek.czy_wystartowal=false;
                        sprawdz=true;
                        break;
                    }
                }
                if(sprawdz){
                    break;
                }
            }
            if(pozycja()+odleglosc>39){
                sprite.setPosition(pozycje_na_planszy[pozycja()+odleglosc-40][0],pozycje_na_planszy[pozycja()+odleglosc-40][1]);
            }else{
                sprite.setPosition(pozycje_na_planszy[pozycja()+odleglosc][0],pozycje_na_planszy[pozycja()+odleglosc][1]);
            }


            if(!czy_wystartowal){
                if(pozycja_a_start()>5){
                    czy_wystartowal=true;
                }
            }else{

                if(pozycja_a_start()<=5){
                    sprite.setPosition(pozycje_koncowe[nr_gracz][nr_pionek][0],pozycje_koncowe[nr_gracz][nr_pionek][1]);
                }

            }
    }


}

//zwraca pozycje liczbowa wzgledem startu niebieskiego
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

//zwaraca pozycje liczbowa wzgledem swojego startu
int Pionek::pozycja_a_start(){


    int start = nr_gracz*10;
    int pozycja = 0;

    while(true){

        if(start > 39){

            start = 0;
        }

        if(pozycje_na_planszy[start][0]==sprite.getPosition().x&&pozycje_na_planszy[start][1]==sprite.getPosition().y){
            break;
        }
        start ++;
        pozycja ++;
    }

    return pozycja;

}

void Pionek::start(){

    sprite.setPosition(pozycje_na_planszy[nr_gracz*10][0], pozycje_na_planszy[nr_gracz*10][1]);
    czy_wystartowal = true;


}

bool Pionek::w_domu(){

        if(sprite.getPosition().x==pozycje_startowe[nr_gracz][nr_pionek][0]-17&&sprite.getPosition().y==pozycje_startowe[nr_gracz][nr_pionek][1]-22){

            return true;


        }
        return false;

}

bool Pionek::skonczyl(){


        if(sprite.getPosition().x==pozycje_koncowe[nr_gracz][nr_pionek][0]&&sprite.getPosition().y==pozycje_koncowe[nr_gracz][nr_pionek][1]){

            return true;

        }
        return false;

}





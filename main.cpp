#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>
#include <thread>
#include <Pionek.h>
#include <Gracz.h>
using namespace std;

//pierwszy gracz niebieski, drugi gracz zolty, trzeci gracz czerwony, czwarty gracz zielony

int Pionek::pozycje_startowe[4][4][2]={
    76,77,155,77,76,157,155,157,
    645,77,725,77,645,157,725,157,
    645,644,725,644,645,723,725,723,
    74,644,155,644,74,723,155,723

};


//pozycje na planszy zaczynajac od niebieskiego
/*
int Pionek::pozycje_na_planszy[40][2]={
    //start niebieskiego
    40,310, 108,310, 176,310, 245,310, 315,310, 315,241, 315,172, 315,104, 315,36, 383,36,
    //start zoltego
    451,36, 451,104, 451,172, 451,240, 451,308, 518,308, 587,308, 657,308, 726,308, 726,377,
    //start brazowego
    726,446
    };
    */
int Pionek::pozycje_na_planszy[40][2]={
    38,310, 107,310, 176,310, 245,310, 314,310, 314,241, 314,172, 314,103, 314,34, 383,34,
    452,34, 452,103, 452,172, 452,241, 452,310, 521,310, 590,310, 659,310, 728,310, 728,379,
    728,448, 659,448, 590,448, 521,448, 452,448, 452,517, 452,586, 452,655, 452,724, 383,724,
    314,724, 314,655, 314,586, 314,517, 314,448, 245,448, 176,448, 107,448, 38,448, 38,379};






int ilosc_graczy;


float czas1;
float czas2;
float czas3;
bool nieWeszlo= true;
bool klik = false;
bool started = true;
int wynik=0;
int nowywynik = 0;
int obecny_gracz = 0;
sf::Texture dice_texture;
sf::Sprite dice;
sf::RenderWindow window(sf::VideoMode(800, 800),"Gra Chinczyk");
std::vector<Gracz> Gracz::lista_graczy;



void rzut_kostka(float jakkolwiek, float obecnyCzas){



    float doNast = jakkolwiek;
    if(nieWeszlo){
        czas3 = obecnyCzas;
        nieWeszlo = false;
    }
    if(obecnyCzas>=czas3+doNast){
        nowywynik = 1 + (rand() % 6);



        switch(nowywynik){
            case 1:
                dice_texture.loadFromFile("tekstury/jeden.png");
                break;
            case 2:
                dice_texture.loadFromFile("tekstury/dwa.png");
                break;
            case 3:
                dice_texture.loadFromFile("tekstury/trzy.png");
                break;
            case 4:
                dice_texture.loadFromFile("tekstury/cztery.png");
                break;
            case 5:
                dice_texture.loadFromFile("tekstury/piec.png");
                break;
            case 6:
                dice_texture.loadFromFile("tekstury/szesc.png");
                break;


        }
        dice.setTexture(dice_texture);
        dice.setPosition(400-31.5,400-34);
        nieWeszlo = true;
    }

}





void start(){

    //kostka
    dice_texture.loadFromFile("tekstury/szesc.png");
    dice.setTexture(dice_texture);
    dice.setPosition(400-31.5,400-34);


    //pionki graczy na pozycjach startowych
    for(int i = 0;i<ilosc_graczy;i++){
            std::vector<Pionek> lista;

        for(int j = 0;j<4;j++){
            sf::Texture board;
            switch(i){
            case 0:
                board.loadFromFile("tekstury/niebieski.png");
                break;
            case 1:
                board.loadFromFile("tekstury/zolty.png");
                break;
            case 2:
                board.loadFromFile("tekstury/czerwony.png");
                break;
            case 3:
                board.loadFromFile("tekstury/zielony.png");
                break;


            }
            sf::Sprite temp = sf::Sprite(board);
            temp.setPosition(Pionek::pozycje_startowe[i][j][0]-17, Pionek::pozycje_startowe[i][j][1]-22);
            Pionek pionek = Pionek(temp, i, j);
            lista.push_back(pionek);

        }
        Gracz::lista_graczy.push_back(Gracz(lista,i));
    }

}




void rysowanie_pionkow_graczy(){

    for (Gracz &gracz : Gracz::lista_graczy){
        for(Pionek &pionek : gracz.lista_pionkow){
            sf::Texture board;
            switch(pionek.nr_gracz){
            case 0:
                board.loadFromFile("tekstury/niebieski.png");
                break;
            case 1:
                board.loadFromFile("tekstury/zolty.png");
                break;
            case 2:
                board.loadFromFile("tekstury/czerwony.png");
                break;
            case 3:
                board.loadFromFile("tekstury/zielony.png");
                break;
            }
            pionek.sprite.setTexture(board);
            window.draw(pionek.sprite);
        }
    }

}
int main()
{


    ilosc_graczy = 4;

    sf::Texture board;
    board.loadFromFile("tekstury/plansza.png");
    sf::Sprite boardSprite(board);
    sf::Clock clock;
    sf::Event event;

    //Eventy
    while (window.isOpen())
    {
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){

                if(event.key.code == sf::Mouse::Left){
                    if(dice.getGlobalBounds().contains(pos.x, pos.y)){
                        klik = true;
                        czas1=clock.getElapsedTime().asSeconds();
                        czas2=clock.getElapsedTime().asSeconds()+5;
                    }
                }
                if(wynik!=0){
                    for(Pionek &pionek : Gracz::lista_graczy.at(obecny_gracz).lista_pionkow){

                            if(pionek.sprite.getGlobalBounds().contains(pos.x, pos.y)){

                                pionek.ruch(wynik);
                                wynik=0;

                            }

                    }
                }
            }
        }


        //wczytanie danych startowych
        if(started){
        start();
        Gracz::lista_graczy.at(1).lista_pionkow.at(0).start();
        Gracz::lista_graczy.at(0).lista_pionkow.at(0).start();

        started=false;
        }

        //losowanie liczb
        if(klik){
            float obecnyCzas = clock.getElapsedTime().asSeconds();
            if(obecnyCzas<czas2){
                 if(obecnyCzas>=czas1+3 && obecnyCzas<czas1+4){
                   rzut_kostka(0.4,obecnyCzas);
                 }
                 else if(obecnyCzas>=czas1+4){
                    rzut_kostka(0.6,obecnyCzas);
                 }else{
                 rzut_kostka(0.2,obecnyCzas);
                 }
            }else{
                klik = false;
                wynik = nowywynik;




            }
        }

        //rysowanie
        window.clear();
        window.draw(boardSprite);
        window.draw(dice);
        rysowanie_pionkow_graczy();
        window.display();

    }

    return 0;

}

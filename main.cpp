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

int Pionek::pozycje_koncowe[4][4][2]={
    107,379,176,379,245,379,314,379,
    383,103,383,172,383,241,383,310,
    659,379,590,379,521,379,452,379,
    383,655,383,586,383,517,383,448

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
bool ma_6 = false;
int wynik=0;
int nowywynik = 0;
int obecny_gracz = 0;
sf::Texture dice_texture;
sf::Sprite dice;
sf::RenderWindow window(sf::VideoMode(800, 900),"Gra Chinczyk");
std::vector<Gracz> Gracz::lista_graczy;


string obecny_gracz_to_string(){

    switch(obecny_gracz){
    case 0:
        return "Niebieski";
    case 1:
        return "Zolty";
    case 2:
        return "Czerwony";
    case 3:
        return "Zielony";

    }

}

void kolejny_gracz(){

    if(obecny_gracz==ilosc_graczy-1){
        obecny_gracz=0;
    }else{
        obecny_gracz++;
    }

}


void rzut_kostka(float jakkolwiek, float obecnyCzas){



    float doNast = jakkolwiek;
    if(nieWeszlo){
        czas3 = obecnyCzas;
        nieWeszlo = false;
    }
    if(obecnyCzas>=czas3+doNast){

        //nowywynik = 1 + (rand() % 6);
        nowywynik = 6;

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




    ilosc_graczy = 2;

    sf::Texture board;
    board.loadFromFile("tekstury/plansza.png");
    sf::Sprite boardSprite(board);
    sf::Clock clock;
    sf::Event event;
    sf::Text info;
    info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nKliknij w kostke aby rozpoczac ruch");
    info.setCharacterSize(24);
    info.setFillColor(sf::Color(255, 102, 0));
    info.setPosition(15,810);
    sf::Font font;
    bool sprawdzenie = false;
    if (!font.loadFromFile("tekstury/arial.ttf"))
    {

    }
    info.setFont(font);

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
                    if(dice.getGlobalBounds().contains(pos.x, pos.y)&&(wynik==0||ma_6)){

                        klik = true;
                        sprawdzenie = false;

                        ma_6 = false;
                        czas1=clock.getElapsedTime().asSeconds();
                        czas2=clock.getElapsedTime().asSeconds()+5;
                    }

                    if(wynik!=0){
                            int lokalny = obecny_gracz;
                        for(Pionek &pionek : Gracz::lista_graczy.at(obecny_gracz).lista_pionkow){
                                if(!Gracz::lista_graczy.at(obecny_gracz).po_losowaniu){
                                    if(lokalny==obecny_gracz){

                                         kolejny_gracz();

                                    }

                                    info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nKliknij w kostke aby rozpoczac ruch");

                                }else{
                                    if(pionek.sprite.getGlobalBounds().contains(pos.x, pos.y)&&!pionek.skonczyl()){
                                        if(sprawdzenie){
                                                if(pionek.w_domu()){

                                                    pionek.start();
                                                    sprawdzenie=false;
                                                    kolejny_gracz();
                                                    info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nKliknij w kostke aby rozpoczac ruch");
                                                    wynik=0;
                                                    ma_6 = false;

                                                }



                                        }else{
                                            if(wynik==6&&!pionek.w_domu()){

                                                pionek.ruch(6);

                                                if(!Gracz::lista_graczy.at(obecny_gracz).pionek_na_planszy()){
                                                    for(int i = 0;i<4;i++){

                                                        if(Gracz::lista_graczy.at(obecny_gracz).lista_pionkow.at(i).w_domu()){


                                                            Gracz::lista_graczy.at(obecny_gracz).lista_pionkow.at(i).start();
                                                            cout<<"wypisuje sie"<<endl;
                                                            Gracz::lista_graczy.at(obecny_gracz).po_losowaniu=true;

                                                            break;
                                                        }
                                                    }
                                                    wynik=0;
                                                    kolejny_gracz();
                                                    info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nKliknij w kostke aby rozpoczac ruch");
                                                }else{
                                                    info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nRzuc kostka ponownie lub wyprowadz nowego pionka");

                                                    //wynik=0;
                                                    ma_6 = true;
                                                }
                                                sprawdzenie = true;


                                            }else{
                                                if(!pionek.w_domu()){

                                                    pionek.ruch(wynik);
                                                    if(!Gracz::lista_graczy.at(obecny_gracz).pionek_na_planszy()){
                                                        Gracz::lista_graczy.at(obecny_gracz).po_losowaniu=false;
                                                    }
                                                    kolejny_gracz();
                                                    info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nKliknij w kostke aby rozpoczac ruch");
                                                    wynik=0;
                                                    ma_6 = false;



                                                }

                                            }
                                        }



                                    }
                                }

                        }
                    }
                }
            }
        }


        //wczytanie danych startowych
        if(started){
        start();

        started=false;
        }

        //losowanie liczb
        if(klik){

            if(nowywynik!=0)info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nLosowanie liczby: "+to_string(nowywynik));

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
                if(wynik==6){
                        if(!Gracz::lista_graczy.at(obecny_gracz).po_losowaniu){
                            Gracz::lista_graczy.at(obecny_gracz).po_losowaniu=true;
                            for(int i = 0;i<4;i++){

                                if(Gracz::lista_graczy.at(obecny_gracz).lista_pionkow.at(i).w_domu()){

                                    Gracz::lista_graczy.at(obecny_gracz).lista_pionkow.at(i).start();
                                    break;
                                }
                            }
                            kolejny_gracz();
                            info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nKliknij w kostke aby rozpoczac ruch");
                            wynik = 0;
                        }else{

                            info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nGratulacje wylosowano liczbe: "+to_string(wynik)+" Wybierz pionka");

                        }



                }else{

                    if(!Gracz::lista_graczy.at(obecny_gracz).po_losowaniu){

                        kolejny_gracz();
                        info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nKliknij w kostke aby rozpoczac ruch");
                        wynik=0;

                    }else{

                        info.setString("Ruch wykonuje gracz: "+obecny_gracz_to_string()+"\nWylosowano liczbe: "+to_string(wynik)+" Wybierz pionka");

                    }

                }





            }
        }

        //rysowanie
        window.clear();
        window.draw(boardSprite);
        window.draw(dice);
        rysowanie_pionkow_graczy();
        window.draw(info);
        window.display();

    }

    return 0;

}

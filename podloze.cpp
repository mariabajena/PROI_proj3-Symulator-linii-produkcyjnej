#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include<limits>
#include <fstream>
#include "podloze.h"

using namespace std;

//m-liczba podlozy
int ustawM(){
    int m;
    cout<<"Ile bedzie podlozy"<<endl;
    cin>>m;
    while(!cin){
        cout << "Zla wartosc!";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Ile bedzie podlozy"<<endl;
        cin >> m;
    }
    return m;
}

//n-liczba urzadzen
int ustawN(){
    int n=7;
    return n;
}

//konstruktor
Plansza::Plansza(){
    m=ustawM();
    n=ustawN();

    vector<std::vector<int> > tab1(m, std::vector<int>(n, 0));

    tab=tab1;
}

vector<std::vector<int> > Plansza::zwrocTab(){
    return tab;
}

//destruktor
Plansza::~Plansza(){}

//wyswietlanie planu dzialania linii produkcyjnej
void Plansza::wyswietl(){

    planowanieKrokow(); //zaplanowanie kolejnosci urzadzen dla danego podloza

        for (int i=0; i< m; i++)
        {
            for (int j=0; j< n; j++)
            {
                cout<<tab[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;

    zapiszDoPliku(); //zapisywanie do pliku

    oczekiwanyCzas(); //wyliczenie oczekiwanego czasu dzialania wykonania zadanych podlozy
}

void Plansza::planowanieKrokow(){
    int liczba;
    for (int i=0; i< m; i++)
    {
        cout<<"Podloze nr "<<i<<endl;
        for (int j=0; j< n; j++) //dla kazdego podloza ustalam przez jakie urzadzenia przejdzie i w jakiej kolejnosci
        {
            if(j==0 || j==5 || j==6) {
                tab[i][j]=j;
                cout<<"Krok nr "<<j<<": "<<j<<" (z warunkow zadania)"<<endl;
            }
            else {
                cout<<"Wpisz krok nr"<<j<<" (od 1 do 4): "<<endl;
                cin>>liczba;

                while(!cin || liczba>4 ){
                cout << "Zla wartosc!";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Wpisz krok nr : ";
                cin >> liczba;
            }

                tab[i][j]=liczba;
            }
        }
}
}

void Plansza::oczekiwanyCzas(){

    int opoznienie;
    opoznienie=0;

    for (int i=0; i< m; i++)
    {
        for (int j=0; j< n; j++)
        {
           for (int k=1; k< m; k++)
            {
                if((i+k)<m){
                    if((j-k)>0){
                        if(tab[i][j]==tab[i+k][j-k]) opoznienie+=15; //sprawdzam czy na przekatnej wektora sa jakies powtarzajace sie urzadzenia
                    }
                }
            }
        }
        cout<<endl;
    }

    cout<<endl<<"Liczba podlozy dodanych do linii produkcyjnej: "<<m<<endl;
    cout<<"Oczekiwany czas wytworzenia podlozy to:" <<((n*15)+opoznienie)<<" minut."<<endl; //przejscie przez kazde urzadzenie to 15 min + czekanie w kolejce
}

//sprawdzanie istorii urzadzen lub podlozy
void Plansza::sprawdzStanProdukcji(){
    do{
        cout<<endl<<"-----Sprawdzanie historii-----"<<endl;
        coSprawdzic();
        }
        while(decyzja());
}

//do sprawdzania historii
void Plansza::coSprawdzic(){
        int coSprawdzic1;

        cout<<"Co chcesz sprawdzic? Podloze--->0 Urzadzenie--->1"<<endl;
        cin>>coSprawdzic1;

        if(coSprawdzic1==0) sprawdzanieHistoriiPodloza();
        else if(coSprawdzic1==1) sprawdzanieHistoriiUrzadzenia();
        else {
            cout << "AAA Zla wartosc!";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            coSprawdzic();
        }
}

//do sprawdzania historii
void Plansza::sprawdzanieHistoriiUrzadzenia(){
    int numer;
    int czyBylo;
    czyBylo=0;
    int ileRazy;
    ileRazy=0;

    cout<<"Wpisz numer urzadzenia: ";
    cin>>numer;

    cout<<"To numer"<<numer<<endl;


    cout<<"Numery podlozy zapisane w historii pracy urzadzenia nr "<<numer<<" to: ";

    for (int i=0; i< m; i++)
    {
        czyBylo=0;
        ileRazy=0;
        for (int j=0; j< n; j++)
        {
            if(tab[i][j]==numer) {
                    czyBylo=1;
                    ileRazy+=1;
            }
        }
        if(czyBylo==1) cout<<endl<<"Podloze "<<i<<": "<<ileRazy<<" razy";
    }
    cout<<endl;
}

//do sprawdzania historii
void Plansza::sprawdzanieHistoriiPodloza(){
    int numer;

    cout<<"Wpisz numer podloza: ";
    cin>>numer;

    while(!cin || numer>m || numer==m){
        cout << "Zla wartosc!";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Wpisz numer podloza: ";
        cin >> numer;
    }

    cout<<"Numery urzadzen zapisane w historii pracy podloza nr "<<numer<<" to: "; //wypisywanie wiersza z wektora o danym numerze

    for (int j=0; j< n; j++)
    {
        cout<<tab[numer][j]<<" ";
    }
}

void Plansza::sprawdzPlanKrokowPodloza(){
        int numer;

        cout<<endl<<"----SPRAWDZANIE PLANU KROKOW PODLOZA----";
        cout<<"Wpisz numer podloza: ";
        cin>>numer;

        while(!cin || numer>m){
                cout << "Zla wartosc!";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Wpisz numer podloza: ";
                cin >> numer;
            }

            wypiszPlanKrokow(numer); //wypisywanie wiersza z wektora o danym numerze

}

void Plansza::wypiszPlanKrokow(int numer){
     cout<<"Plan krokow podloza nr "<<numer<<" to: ";
        for (int j=0; j< n; j++)
        {
            cout<<tab[numer][j]<<" ";
        }
}

int decyzja(){
    int decyzja;
    cout<<endl<<"Czy to wszystko? 0-->tak  1-->nie"<<endl;
    cin>>decyzja;

    //obsluga bledu strumienia wejsciowego
    while(!cin || decyzja>1){
    cout << "Zla wartosc!";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> decyzja;
}
    return decyzja;
}

//czytanie wektora z zapisanego pliku
void Plansza::czytajTabZPliku(){
    fstream plik;

    plik.open("plik.txt", ios::in);

    if(plik.good() == true)
    {
        for (int i=0; i< m; i++)
                {
                    for (int j=0; j< n; j++)
                    {
                        plik>>tab[i][j];
                    }
                }
    }
    plik.close();


    for (int i=0; i< m; i++)
    {
        for (int j=0; j< n; j++)
        {
            cout<<tab[i][j]<<" ";
        }
        cout<<endl;
    }

    oczekiwanyCzas();
}

//zapisywanie do pliku
void Plansza::zapiszDoPliku(){
fstream plik;
    plik.open( "plik.txt", std::ios::in | std::ios::out );
    if( plik.good() == true )
    {

        for (int i=0; i< m; i++)
        {
            for (int j=0; j< n; j++)
            {
                plik<<tab[i][j]<<" ";
            }
            plik<<endl;
        }
        plik.close();
    }
}

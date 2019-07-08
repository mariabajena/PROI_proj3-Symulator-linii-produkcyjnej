#include <iostream>
#include <stdlib.h>
#include <string.h>
#include<limits>
#include <fstream>
#include <vector>

using namespace std;

class Plansza
{
    protected:
        int m, n; //m - liczba podlozy, n - liczba urzadzen
        vector<std::vector<int> > tab; //wektor, w ktorego wierszach zapisywana jest kolejnosc krokow dla konkretnych podlozy
        public:
        Plansza(); //konstruktor
        virtual void wyswietl(); //wyswietlanie wektora
        virtual vector<std::vector<int> > zwrocTab(); //zwracanie wektora
        friend int ustawM(); //ustawianie liczby podlozy
        friend int ustawN(); //ustawianie liczby urzadzen
        virtual void sprawdzStanProdukcji(); //sprawdzanie historii podlozy i urzadzen
        void sprawdzPlanKrokowPodloza(); //sprawdzenie planu krokow dla danego podloza
        void czytajTabZPliku(); //pobranie wektora tab z pliku
        void zapiszDoPliku(); //zapisywanie wektora tab do pliku
        void oczekiwanyCzas(); //ustalenie oczekiwanego czasu dzialaania linii produkcyjnej
        void planowanieKrokow(); //ustalanie krokow dla danego podloza
        void wypiszPlanKrokow(int numer); //wpypisanie planu krokow dla danego podloza
        void sprawdzanieHistoriiPodloza(); //sprawdzanie historii podlozy
        void sprawdzanieHistoriiUrzadzenia();
        void coSprawdzic(); //Podloze czy Urzadzenie?
        ~Plansza(); //destruktow
};

int decyzja(); //wczytuje decyzje uzytkownika co do podjecia krokow w programie
bool good(); //do obslugi pliku
bool is_open(); //do obslugi pliku

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include<limits>
#include <fstream>
#include "podloze.h"

using namespace std;

int main()
{

    cout<<"PROGRAM TESTUJACY MOZLIWOSCI KLASY"<<endl<<endl;
    Plansza Pl;
    Pl.wyswietl();
    //Pl.czytajTabZPliku();
    Pl.sprawdzPlanKrokowPodloza();
    Pl.sprawdzStanProdukcji();

    return 0;
}

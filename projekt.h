#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

#define NSIZE 4464
#define M_PI 3.14159265358979323846


void InputData( vector <string>& timevec, vector <double>& powervec, vector <double>& gvec, vector <double>& svec, vector <double>& tvec, vector <double>& wvec,
    vector <double>& rvec, const char* filename );//pobiera dane z pliku i zapisuje do wektorów

void CheckMonth( int month, vector<string> timevec, int* tab );// znajduje i zapisuje do tab indeksy wektorów które s¹ z miesi¹ca month

double Year_mean( vector <double>& powervec ); //oblicza œredni¹ moc roczn¹ 
double Month_mean( vector <double>& powervec, int* tab, int nSize ); //oblicza œredni¹ moc otrzyman¹ w podanym miesi¹cu


class Gospodarstwo {
private:
    double kwota;
    double prad;
public:
    Gospodarstwo( ): kwota( 0 ), prad( 0 ) {};
    Gospodarstwo( double kw, double pr ) {
        kwota = kw;
        prad = pr;
    }

    double rachunek( ) {
        return kwota * prad;
    }
    void WriteOut( ) {
        cout << "Your electricity rate is: " << kwota << " and your average electricity consumption: " << prad;
    };
    int ShowOption( ) {
        int opcje;
        cout << "\n\nBased on this data, we can calculate for you\n1. the annual average of the power produced \n";
        cout << "2. average power produced in one month \n3. Chart showing annual energy gain each month.\n Enter the number of the option you would like to get: ";
        cin >> opcje;
        return opcje;
    }
    void Output( ofstream& output, vector <string> vect, vector <double> vec) {
        for( int i = 1; i < 13; i++ )
        {
            int* tab = new int[ NSIZE ];
            CheckMonth( i, vect, tab );
            double srednia = Month_mean( vec, tab,NSIZE );
            output << i << "\t" <<srednia  << endl;
        }
        return;
    }
    void Rachunek( Gospodarstwo& h, double mean ) {
        double rach_pan = mean * h.kwota;
        double rach_pr = h.kwota * h.prad;
        if( rach_pan < rach_pr ) cout << "It is not profitable to buy panels for your smallholding!";
        else cout << "Within a month, you would pay for the electricity you produced " << rach_pan<< " zl";
    }
};

class Turbina:public Gospodarstwo {
private:
    double dl;
    int type;
    double sred;
public:
    Turbina( ):dl( 3 ), type( 1 ), sred( 0 ) {}
    Turbina( double d, int t, double s ) {
        dl = d;
        type = t;
        sred = s;
    }
    double powierzchnia( ) {
        if( type == 1 ) {
            return dl * dl * M_PI;
        }
        if( type == 2 ) {
            return dl * sred;
        }
    }
    void WriteOut( ) {
        cout << "You have selected the type of turbine: " << type << " of blade length: " << dl;
        if( type == 2 ) {
            cout << " and rotor diameter: " << sred << ".\n";
        }
    };
    double moc( double powierz, double sr_wiatru )//oblicza œrednia moc otrzyman¹ z turbiny wiatrowej
    {
        return powierz * 1.225 * sr_wiatru / 2;//powierzchnia * œrednia gêstoœc powietrza*œrednia predkosc wiatru/2
    }
    void OutputData( ofstream& output, vector <string> vect, vector <double> vec, double pole ) {
        for( int i = 1; i < 13; i++ )
        {
            int *tab =new int[NSIZE];
            CheckMonth( i, vect, tab );
            output << i << "\t" << this->moc( pole, Month_mean( vec, tab, NSIZE) ) << endl;
        }
        return;
    }
};


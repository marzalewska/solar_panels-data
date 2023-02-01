#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

#define NSIZE 4464
#define NSIZE2  52563

using namespace std;

#include "projekt.h"


int main( )
{
    //POBRANIE DANYCH
    vector <string> timevec;
    vector <double> gvec;
    vector <double> powervec;
    vector <double> svec;
    vector <double> wvec;
    vector <double> rvec;
    vector <double> tvec;

    timevec.reserve( NSIZE2 );
    gvec.reserve( NSIZE2 );
    powervec.reserve( NSIZE2 );
    svec.reserve( NSIZE2 );
    wvec.reserve( NSIZE2 );
    rvec.reserve( NSIZE2 );
    tvec.reserve( NSIZE2 );

    InputData( timevec, powervec, gvec, svec, tvec, wvec, rvec, "Timeseries_2005_2006kopia.csv" );
    InputData( timevec, powervec, gvec, svec, tvec, wvec, rvec, "Timeseries_2007_2008kopia.csv" );
    InputData( timevec, powervec, gvec, svec, tvec, wvec, rvec, "Timeseries_2009_2010kopia.csv" );

    int opt, type;
    int opcje;
    double dlugosc=0, srednica=0;//dlugosc lopatki i srednica wirnika
    cout << "Good morning, here is your helper in starting to be ECO!\n If you want to use me to calculate the energy you will get thanks to solar panels, press 1, and if you want to find out if you will profit from your own wind turbine, press 2: ";
    cin >> opt;
    if( opt == 1 ) {
        //POBRANIE DANYCH DO KLASY GOSPODARSTWO
        double k;
        double p;
        cout << "Enter the rate you pay per kWh: ";
        cin >> k;
        while( k < 0 ) {
            if( k < 0 ) cout << "Enter a positive number! ";
            cin >> k;
        }
        cout << "\nEnter the average electricity consumption in your household: ";
        cin >> p;
        while( p < 0 ) {
            if( p < 0 ) cout << "Enter a positive number! ";
            cin >> p;
        }
        Gospodarstwo Home( k, p );
        label1:
        opcje = Home.ShowOption( );
        if( opcje == 1 ) {
            cout << "Average annual power from solar panels would reach " << Year_mean( powervec ) << endl;;
        }
        if( opcje == 2 ) {
           
            int month;
            cout << "Enter the month from which you want to receive data: ";
            do
            {
                cin >> month;
            } while(!( month >= 1 && month <=12) );
 
            int* tab = new int[ NSIZE ];
            CheckMonth( month, timevec, tab );
           
            double month_mean = Month_mean( powervec, tab, NSIZE );
            cout << "The average power in a " << month << ". month from solar panels would reach " << month_mean<<" kWh";
            double rach = month_mean * k;

        }
        if( opcje == 3 ) {
            ofstream outfile2;
            outfile2.open( "wyniki2.txt", ios::out | ios::trunc );
            if( outfile2.good( ) == true ) {
                Home.Output( outfile2, timevec, powervec );
                outfile2.close( );
            }
            else cout << "\nError opening output file!" << endl;

            system( "gnuplot  D:\\projekty\\PROJEKT2\\Project1\\Project1\\plotP.txt" );
            
        }
        goto label1;
    }
    else if( opt == 2 )
    {   //POBRANIE DANYCH DO KLASY TURBINA
        cout << "Enter the type of wind turbine you want to install, press 1 if you want a horizontal axis wind turbine, and 2 if you want a vertical axis wind turbine: ";
        cin >> type;
        if( type == 1 ) {
            cout << "Enter the length of the turbine blade (in meters) that you would like and can use in your turbine: ";
            cin >> dlugosc;
            srednica = 0;
        }
        else if( type == 2 ) {
            cout << "Enter the height of the turbine blade (in meters) and the diameter of the impeller that you would like and can use in your turbine:  ";
            cin >> dlugosc >> srednica;
        }
        
        Turbina t1( dlugosc, type, srednica);
        t1.WriteOut( );
        double pole = t1.powierzchnia( );
        label2:
        opcje=t1.ShowOption( );

        if( opcje == 1 ) {
            double wind_mean = Year_mean( wvec );
            double moc = t1.moc( pole, wind_mean );
            cout << "The average annual value of the power that the turbine will produce for you is: " <<moc<<endl ;
        }
        if( opcje == 2 ) {
            int month;
            cout << "Enter the month from which you want to receive data: ";
            cin >> month;
            do
            {
              cin >> month;
            } while( !( month >= 1 && month <= 12 ) );

            int* tab = new int[ NSIZE ];
            CheckMonth( month, timevec, tab );
            double moc2 = t1.moc( pole, Month_mean( wvec, tab,NSIZE ) );
            cout << "The power you would get from the turbine in " << month << ". month is: " << moc2<<endl;
        }
        if( opcje == 3 ) {
            ofstream outfile;
            outfile.open( "wyniki.txt", ios::out | ios::trunc );
            if( outfile.good( ) == true ) {
                t1.OutputData( outfile, timevec, wvec, pole );
                outfile.close( );
            }
            else cout << "\nError opening output file!" <<endl;

            system( "gnuplot D:\\projekty\\PROJEKT2\\Project1\\Project1\\plotT.txt" );
        }
        goto label2;
    }
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>
#include <iostream>

using namespace std;

void InputData( vector <string>& timevec, vector <double>& powervec, vector <double>& gvec
    , vector <double>& svec, vector <double>& tvec, vector <double>& wvec,
    vector <double>& rvec, const char* filename ) {
    fstream plik( filename );
    
    if( !plik )cout << "B³¹d w otworzeniu pliku! \n";
    string line;
    string time;
    string Power, G, S_Height, Temp, Wind, Rec;
    while( getline( plik, line ) ) {
        stringstream ss( line );
        getline( ss, time, ',' );
        timevec.push_back( time );
        getline( ss, Power, ',' );
        powervec.push_back( stod( Power ) );
        getline( ss, G, ',' );
        gvec.push_back( stod( G ) );
        getline( ss, S_Height, ',' );
        svec.push_back( stod( S_Height ) );
        getline( ss, Temp, ',' );
        tvec.push_back( stod( Temp ) );
        getline( ss, Wind, ',' );
        wvec.push_back( stod( Wind ) );
        getline( ss, Rec, ',' );
        rvec.push_back( stod( Rec ) );
    }
  
}


void CheckMonth( int month, vector<string> powervec, int* tab )
{
    for( size_t i = 0; i < powervec.size( ); i++ )
    {
        string miesiac = powervec[ i ].substr( 4, 2 );
        int num = stoi( miesiac );
        if( num == month ) {
            *tab++ = i;
        }
    }
}

double Month_mean( vector <double>& timevec, int* tab, int nSize) {
    double suma = 0;
    double srednia = 0;
    for( int i = 0; i <nSize ; i++ ) {
        suma += timevec[ tab[ i ] ];
    }
    
    srednia = suma / 6;//suma jest z powtarzaj¹cego siê 6 razy miesi¹ca
    return srednia;
}

double Year_mean( vector <double>& powervec ) {
    double suma = accumulate( powervec.begin( ), powervec.end( ), 0.0 );
    double srednia = suma / 6;// w plikach znajduj¹ siê dane z 6 lat;
    return srednia;
}


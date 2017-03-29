//Connor Kunstek
//CS315
//Programming Assignment 1
//Traveling Salesmen
//March 28, 2017
//City Header File

//include guards////////////////////////////////////////////////////////////////
#ifndef City_h
#define City_h
//includes//////////////////////////////////////////////////////////////////////
#include <string>
#include <iostream>
using namespace std;
class City
{
    public:
        //constructors//////////////////////////////////////////////////////////
        City();
        City(string name, double latitude, double longitude);
        //to access private data////////////////////////////////////////////////
        string getName();
        double getLat();
        double getLong();
        vector<double> getPoint();
    private:
        string name;
        double latitude;
        double longitude;
};
//closing include guard/////////////////////////////////////////////////////////
#endif

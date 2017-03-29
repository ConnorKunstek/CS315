//Connor Kunstek
//CS315
//Header File - City
//Traveling Salesman

#include<string>
#include<iostream>

using namespace std;
#ifndef City_h
#define City_h

class City
{
  public:
    City();
    City(string cityName, double cityLatitude, double cityLongitude);
    string getName();
    double getLat();
    double getLong();
    void display1();
    void display2();
  private:
    string name;
    double latitude;
    double longitude;

};

#endif

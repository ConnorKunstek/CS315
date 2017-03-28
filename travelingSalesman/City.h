//Connor Kunstek
//CS315
//Header File - City
//Traveling Salesman

#include<string>
#include<iostream>

using namespace std;
#ifndef CLASSES_H
#define CLASSES_H

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

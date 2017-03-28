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
    getName();
    getLat();
    getLong();
    display();
  private:
    string name;
    double latitude;
    double longitude;

};

#endif

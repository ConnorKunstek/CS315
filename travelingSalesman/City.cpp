//Connor Kunstek
//CS315
//Class City
//Traveling Salesman

#include<iostream>
#include<vector>
#include "City.h"
#include <map>

using namespace std;

City::City()
{
  name = NULL;
  latitude = 0.0;
  longitude = 0.0;
};

City::City(string cityName, double cityLatitude, double cityLongitude)
{
  name = cityName;
  latitude = cityLatitude;
  longitude = cityLongitude;
};

string City::getName()
{
  return name;
};

double City::getLat()
{
  return latitude;
};

double City::getLong()
{
  return longitude;
};

void City::display1()
{
  cout << endl << "Name: \t" << name << endl;
  cout << "Latitude: \t" << latitude << endl;
  cout << "longitude: \t" << longitude << endl;
};

void City::display2()
{
  cout << "\t Name: " << name << "\t Latitude: " << latitude << " \t Longitude: " << longitude;
}

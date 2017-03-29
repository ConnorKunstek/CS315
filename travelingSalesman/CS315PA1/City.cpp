//Connor Kunstek
//CS315
//Programming Assignment 1
//Traveling Salesmen
//March 28, 2017
//City .cpp File

//include header file
#include "City.h"
#include<vector>
using namespace std;
//Constructor with default values for if no data is passed in///////////////////
City::City()
{
  name = "NULL";
  latitude = 0.0;
  longitude = 0.0;
}
//Constructor for when data is passed in////////////////////////////////////////
City::City(string tempName, double tempLatitude, double tempLongitude)
{
  name = tempName;
  latitude = tempLatitude;
  longitude = tempLongitude;
}
//Used to access private data///////////////////////////////////////////////////
string City::getName()
{
  return name;
}
//Used to access private data latitude//////////////////////////////////////////
double::City::getLat()
{
  return latitude;
}
//Used to access private data longitude/////////////////////////////////////////
double::City::getLong()
{
  return longitude;
}
//Used to return both Lat and Long//////////////////////////////////////////////
vector<double> City::getPoint()
{
    vector<double> point;
    point.push_back(latitude);
    point.push_back(longitude);
    return point;
}

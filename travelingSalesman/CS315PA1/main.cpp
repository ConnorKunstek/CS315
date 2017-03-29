//Connor Kunstek
//CS315
//Programming Assignment 1
//Traveling Salesmen
//March 28, 2017
//Main File

//includes//////////////////////////////////////////////////////////////////////
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <math.h>
#include <sstream>
#include <chrono>
//to use City Class//////////////////////////////////////////////////////////////
#include "City.h"
using namespace std;
//globals///////////////////////////////////////////////////////////////////////
#define DISTANCEMULT 0.621371
#define PIMULTIPLIER 3.14159
//To get radians////////////////////////////////////////////////////////////////
double convertToRadians(double degrees)
{
    double returnVar =  (degrees * PIMULTIPLIER / 180);
    return returnVar;
}

//Haversine Formula to find distance////////////////////////////////////////////
double findDistance(vector<double> point1, vector<double> point2)
{
    double latitudeCon1 = convertToRadians(point1[0]);
    double longitudeCon1 = convertToRadians(point1[1]);
    double latitudeCon2 = convertToRadians(point2[0]);
    double longitudeCon2 = convertToRadians(point2[1]);
    double latitude = latitudeCon2 - latitudeCon1;
    double longitude = longitudeCon2 - longitudeCon1;
    double tempDistance = sqrt(pow(sin(latitude/2), 2) + (cos(latitudeCon1) * cos(latitudeCon2) * pow(sin(longitude/2), 2)));
    double distance = 2 * 6371 * asin(tempDistance);
    return distance;
}
//To get miles//////////////////////////////////////////////////////////////////
double convertToMiles(double km)
{
    double returnVar = (DISTANCEMULT * km);
    return returnVar;
}
// Checks if string is a double/////////////////////////////////////////////////
bool doubleCheck(string number)
{
    istringstream iss(number);
    double doubleNumber;
    char character;
    return iss >> doubleNumber && !(iss >> character);
}
//Split/////////////////////////////////////////////////////////////////////////
vector<string> split( string line, string delimiters ) {
  vector<string> result;

  int start_loc = 0;
  bool is_delim = true;
  int curr_loc = 0;
  for( char curr_char : line ){
    // Check if delimiter
    bool found_del = false;
    for( char delim : delimiters ){
      if( curr_char == delim ){
        found_del = true;
        // If wasn't a delimeter then start_loc -> curr_loc is a word
        if( !is_delim ){
          result.push_back( line.substr(start_loc, curr_loc-start_loc) );
        }
        break;
      }
    }
    // If no delimeter matched
    if( !found_del && is_delim ){
      is_delim = false;
      start_loc = curr_loc;
    }
    is_delim = found_del;
    curr_loc++;
  }
  // Check if the last word ended at the end of the string, start_loc -> end
  if( !is_delim ){
    result.push_back( line.substr(start_loc, curr_loc-start_loc) );
  }
  return result;
}
//MAIN//////////////////////////////////////////////////////////////////////////
int main()
{
      //maps needed/////////////////////////////////////////////////////////////
      map<string, City*> cities;
      map<string, City*> names;
      map<double, City*> lats;
      map<double, City*> longs;
      //variables needed////////////////////////////////////////////////////////
      string tempName = "";
      double tempLatitude = 0.0;
      double tempLongitude = 0.0;
      string line;
      //timing//////////////////////////////////////////////////////////////////
      chrono::time_point<chrono::system_clock> start, end;
      start = std::chrono::system_clock::now();
      //timer started
      //Data read in and stored/////////////////////////////////////////////////
      while(getline(cin, line))
      {
            //remains true is data is valid/////////////////////////////////////
            bool check = true;
            tempName = "";
            vector<string> parts = split(line, " ,\t");
            int count = 0;
            if(doubleCheck(parts[0]))
            {
                  check = false;
                  cout << "wrong formating: " << line << endl;
            }
            for(int i = 0; i < parts.size(); i++)
            {
                if(doubleCheck(parts[i]))
                {
                    if(i == parts.size() - 1)
                    {tempLongitude = stod(parts[i]);}
                    if(i == parts.size() - 2)
                    {tempLatitude = stod(parts[i]);}
                }
                else
                {
                    if (count == 0){tempName += parts[i];}
                    else{tempName += " " + parts[i];}
                }count++;
            }
            if(check)
            {
                City *temp = new City(tempName, tempLatitude, tempLongitude);
                names.insert(make_pair(tempName, temp));
                lats.insert(make_pair(tempLatitude, temp));
                longs.insert(make_pair(tempLongitude, temp));
            }
      }
      vector<double>point1;
      vector<double>point2;
      //totals distance for North to South//////////////////////////////////////
      double northSouth = 0.0;
      for(map<double, City*>::iterator curr=lats.begin(); curr!=lats.end(); ++curr)
      {
          map<double, City*>::iterator next = curr; next++;
          if (next != lats.end())
          {
              point1 = curr->second->getPoint();
              point2 = next->second->getPoint();
              northSouth = northSouth + findDistance(point1, point2);
              point1.clear();
              point2.clear();
          }
      }
      //calculates Distance West to East///////////////////////////////////////
      double westEast = 0;
      for (map<double, City*>::iterator curr=longs.begin(); curr!=longs.end(); ++curr)
      {
          map<double, City*>::iterator next = curr; next++;
          if (next != longs.end())
          {
              point1 = curr->second->getPoint();
              point2 = next->second->getPoint();
              westEast = westEast + findDistance(point1, point2);
              point1.clear();
              point2.clear();
          }
      }
      //Convert to Miles////////////////////////////////////////////////////////
      double westEastMiles = convertToMiles(westEast);
      double northSouthMiles = convertToMiles(northSouth);
      //Round Calculations//////////////////////////////////////////////////////
      westEast = round(westEast);
      northSouth = round(northSouth);
      westEastMiles = round(westEastMiles);
      northSouthMiles = round(northSouthMiles);
      //End Timer///////////////////////////////////////////////////////////////
      end = std::chrono::system_clock::now();
      chrono::duration<double> elapsed_seconds = end-start;
      time_t end_time = std::chrono::system_clock::to_time_t(end);
      //Output//////////////////////////////////////////////////////////////////
      cout << endl << endl;
      cout << "West to East: " << longs.begin()->second->getName() << " to " << longs.rbegin()->second->getName() << endl;
      cout << "Distance in Kilometers: " << westEast << " km" << endl;
      cout << "Distance in Miles: " << westEastMiles << " miles" << endl;
      cout << "North to South: " << lats.rbegin()->second->getName() << " to " << lats.begin()->second->getName() << endl;
      cout << "Distance in Kilometers: " << northSouth << " km" << endl;
      cout << "Distance in Miles: " << northSouthMiles << " miles" << endl << endl;
      cout << "Time: " << elapsed_seconds.count() << " seconds" << endl << endl;
      //return statement
      return 0;
}

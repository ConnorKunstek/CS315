//Connor Kunstek
//CS315
//PA1
//Traveling Salesman, Distance of KY Cities N-S and W-E

#include<iostream>
#include<vector>
#include "City.h"
#include <map>
#include <math.h>
#include <chrono>
#include <string>

using namespace std;

#define MULT 1.60934
#define PI 3.14159265
#define EARTHKM 6371
#define EARTHMILES 3959

/* Splits a string on specified delimiters. It will match the delimiters greedily. */
vector<string> split( string line, string delimiters )
{
  vector<string> result;

  int start_loc = 0;
  bool is_delim = true;
  int curr_loc = 0;
  for( char curr_char : line ){
  // Check if delimiter
  bool found_del = false;
  for(char delim : delimiters)
  {
    if(curr_char == delim)
    {
      found_del = true;
      // If wasn't a delimeter then start_loc -> curr_loc is a word
      if( !is_delim )
      {
        result.push_back(line.substr(start_loc, i-start_loc));
      }
      break;
    }
  }
  // If no delimeter matched
  if(!found_del && is_delim)
  {
    is_delim = false;
    start_loc = curr_loc;
  }
  is_delim = found_del;
  curr_loc++;
  }
  // Check if the last word ended at the end of the string, start_loc -> end
  if(!is_delim)
  {
    result.push_back(line.substr(start_loc, i-start_loc));
  }
  return result;
}

double convertToKm(double miles)
{
  double km = miles * MULT;
  return km;
}

double convertToMiles(double km)
{
  double miles = km / MULT;
  return miles;
}

double convertToRadians(double degrees)
{
  double radians = degrees * PI / 180;
  return radians;
}

double convertToDegree(double radians)
{
  double degrees = (rad * 180 / PI);
  return degrees;
}

double findDistance(City city1, City city2)
{
  double lat1 = convertToRadians(city1.getLat());
  double long1 = convertToRadians(city1.getLong());
  double lat2 = convertToRadians(city2.getLat());
  double long2 = convertToRadians(city2.getLong());

  double lat = lat2 - lat1;
  double lng = long2 - long1;

  double d = pow(sin(lat * 0.5), 2) + cos(lat1) * cos(lat2) * pow(sin(lng * 0.5), 2);
  double distanceInKm = 2 * EARTHKM * asin(sqrt(d));

  double round(distanceInKm);

  return distanceInKm;
}

int main(int argc, char *argv[] )
{

  //Timing
  chrono::time_point<chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  //Timer Started

  //Maps needed
  map<string, City> cities;
  map<string, City> names;
  map<double, City> lats;
  map<double, City> longs;

  //data file read in
  string line;
  int line_num = 0;

  while(getline(cin, line))
  {
    // Remove possible delimiters
    vector<string> parts = split(line, " ,\t");
    // You are going to need to process the line of text somehow... split is helpful
    // TODO
    vector<City> cityList;
    City temp = new City(parts[0], stod(parts[1]), stod(parts[2]));
    cityList.push_back(temp);
    /*
    city_key = parts[0];
    city_lat = stod(parts[1]);
    city_long = stod(parts[2]);
    // type SOME_REPRESENTATION
    // If not in maps
    if(cities.find(city_key) == cities.end())
    {
      cities[city_key] = city_data;
    }
    */

    //STILL IN WHILE LOOP
    names.insert(make_pair(parts[0], temp));
    lats.insert(make_pair(parts[1], temp));
    longs.insert(make_pair(parts[2], temp));
  }

  //compute distance East to West
  double westEast = 0.0;
  for (map<double, City*>::iterator current=longs.begin(); current!=longs.end(); ++current)
  {
    map<double, City*>::iterator next = current; // creating second iterator to access other set of coordinates
    ++next; //iterating the iterator

    // Logic to ensure that a non-existent index tries to be accessed
    if (next != longs.end())
    {
      westEast += findDistance(current, next); //using haversine formula to compute distance and adding to running sum
    }
  }

  //compute distance North to South
  double northSouth = 0.0;
  for (map<double, City*>::iterator current = lats.begin(); current != lats.end(); ++current)
  {
    map<double, City*>::iterator next = current;
    ++next; //iterating the iterator

    // Logic to ensure that a non-existent index tries to be accessed
    if (next != lats.end())
    {
      northSouth += findDistance(current, next);
    }
  }

  //Displays to screen
  cout << endl << "West to East: " << longs.begin()->second->display2() << " to " << longs.rbegin()->second->display2() << endl;
  cout << "Total Distance: " << westEast << " km, " << convertToMiles(westEast) << " miles" << endl;
  cout << "North to South: " << lats.rbegin()->second->display2() << " to " << lats.begin()->second->display2() << endl;
  cout << "Total Distance: " << northSouth  << " km, " << convertToMiles(northSouth) << " miles" << endl;


  //More Timing
  end = std::chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end-start;
  time_t end_time = std::chrono::system_clock::to_time_t(end);
  cout << endl << "Elapsed Time: \t" << elapsed_seconds.count() << "s" << endl;
  //Timer stopped and displayed

  return 0;
}

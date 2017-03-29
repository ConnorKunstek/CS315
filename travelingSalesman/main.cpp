//Connor Kunstek
//CS315
//PA1
//Traveling Salesman, Distance of KY Cities N-S and W-E

#include "City.h"

#include<iostream>
#include<vector>
#include<map>
#include<sstream>
#include<cmath>
#include<math.h>
#include<chrono>
#include<string>

using namespace std;

#define MULT 1.60934
#define PI 3.14159265
#define EARTHKM 6371
#define EARTHMILES 3959


////////////////////////////////////////////////////////////////////////////////
///////SPLIT////////////SPLIT//////////////////SPLIT//////////////SPLIT/////////////
////////////////////////////////////////////////////////////////////////////////

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

/*
bool isLessThan(City city1, City city2, string type)
{
  bool returnVar = true;

  if (type == "latitudes")
  {
    returnVar = (city1.getLat() < city2.getLat());
  }
  else if (type == "longitudes")
  {
    returnVar = (city1.getLong() < city2.getLong());
  }
  else
  {
    returnVar = (city1.getName() < city2.getName());
  }
  return returnVar;
}
*/

////////////////////////////////////////////////////////////////////////////////
///////Conversions//////////////Conversions////////////////Conversions//////////
////////////////////////////////////////////////////////////////////////////////

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
  double degrees = (radians * 180 / PI);
  return degrees;
}

////////////////////////////////////////////////////////////////////////////////
///////Find Distance/////////Find Distance/////////////////Find Distance////////
////////////////////////////////////////////////////////////////////////////////

double findDistance(City *city1, City *city2)
{
  double lat1 = convertToRadians(city1->getLat());
  double long1 = convertToRadians(city1->getLong());
  double lat2 = convertToRadians(city2->getLat());
  double long2 = convertToRadians(city2->getLong());

  double lat = lat2 - lat1;
  double lng = long2 - long1;

  double d = pow(sin(lat * 0.5), 2) + cos(lat1) * cos(lat2) * pow(sin(lng * 0.5), 2);
  double distanceInKm = 2 * EARTHKM * asin(sqrt(d));

  double round(distanceInKm);

  return distanceInKm;
}

//returns true if string is a double //////////////////////////////////////////
bool doubleCheck(string check)
{
    istringstream iss(check);
    double number;
    char character;
    return iss >> number && !(iss >> character);
}

////////////////////////////////////////////////////////////////////////////////
///////MAIN////////////MAIN//////////////////MAIN//////////////MAIN/////////////
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[] )
{

  //Maps needed/////////////////Maps needed/////////////////Maps needed////////
  map<string, City*> cities;
  map<string, City*> names;
  map<double, City*> lats;
  map<double, City*> longs;

  //vectors needed/////////////////////vectors needed///////////////////////////
  vector<City> cityVec;
  vector<string> namesVec;
  vector<double> latsVec;
  vector<double> longsVec;

  //initials for City(s) and data input/////////////////////////////////////////
  string name = "NULL";
  double latitude = 0.0;
  double longitude = 0.0;
  string line;
  int line_num = 0;

  //Timing//////////////////////////////////////////////////////////////////////
  chrono::time_point<chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  //Timer Started


  //DATA READ IN and STORED/////////////////////////////////////////////////////
  while(getline(cin, line))
  {
    // Remove possible delimiters
    //vector<string> parts = split(line, " ,\t");
    // You are going to need to process the line of text somehow... split is helpful
    // TODO

/////////////////////////////////////////////////
    bool check = true;

    name = "";
    vector<string> parts = split(line, " ,\t");


    int count = 0;
    if(doubleCheck(parts[0])){
      cout << "wrong format: " << line << endl;
      check = false;
    }

    for(int i = 0; i < parts.size(); i++)
    {
      if(doubleCheck(parts[i]))
      {
        if(i == parts.size() - 1)
        {
          longitude = stod(parts[i]);
        }
        if(i == parts.size() - 2)
        {
          latitude = stod(parts[i]);
        }
      }
      else
      {
        if(count == 0)
        {
          name += parts[i];
        }
        else
        {
          name += " " + parts[i];
        }
      }
      count ++;
    }

    //"if everything is validated...."/////////////////////////////////////////
    if(check)
    {
        //assign for city creation/////////////////////////////////
        name = parts[0];
        latitude = stod(parts[1]);
        longitude = stod(parts[2]);

        //create temp city pointer////////////
        City *temp = new City(name, latitude, longitude);

        temp->display2();

        //store in vectors//////////////////////
        cityVec.push_back(*temp);
        namesVec.push_back(name);
        latsVec.push_back(latitude);
        longsVec.push_back(longitude);

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

        //store in maps/////////////////////////////
        cities.insert(make_pair(name, temp));
        names.insert(make_pair(name, temp));
        lats.insert(make_pair(latitude, temp));
        longs.insert(make_pair(longitude, temp));
    }
  }

  //sort vectors//////////////////
  sort(namesVec.begin(), namesVec.end());
  sort(latsVec.begin(), latsVec.end());
  sort(longsVec.begin(), longsVec.end());

  //compute distance East to West
  double westEast = 0.0;

  City *first = longs.at(longsVec[0]);

  for(int i = 1; i < longsVec.size(); i++)
  {
    City *second = longs.at(longsVec[i]);

    westEast += findDistance(first, second);

    first = second;
  }

  double northSouth = 0.0;

  City *third = longs.at(latsVec[0]);

  for(int i = 1; i < latsVec.size(); i++)
  {
    City *fourth = longs.at(latsVec[i]);

    westEast += findDistance(third, fourth);

    third = fourth;
  }


    /*
    map<double, City*>::iterator next = current; // creating second iterator to access other set of coordinates
    ++next; //iterating the iterator

    // Logic to ensure that a non-existent index tries to be accessed
    if (next != longs.end())
    {
      westEast += findDistance(longs[current], longs[next]->second); //using haversine formula to compute distance and adding to running sum
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
      northSouth += findDistance(lats[current]->second, lats[next]->second);
    }
  }
  */

  //Displays to screen
  cout << endl << "West to East: " << longs.begin()->second->getName() << " to " << longs.rbegin()->second->getName() << endl;
  cout << "Total Distance: " << westEast << " km, " << convertToMiles(westEast) << " miles" << endl;
  cout << "North to South: " << lats.rbegin()->second->getName() << " to " << lats.begin()->second->getName() << endl;
  cout << "Total Distance: " << northSouth  << " km, " << convertToMiles(northSouth) << " miles" << endl;


  //More Timing
  end = std::chrono::system_clock::now();
  chrono::duration<double> elapsed_seconds = end-start;
  time_t end_time = std::chrono::system_clock::to_time_t(end);
  cout << endl << "Elapsed Time: \t" << elapsed_seconds.count() << "s" << endl;
  //Timer stopped and displayed

  return 0;
}

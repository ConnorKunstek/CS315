Connor Kunstek
CS315
Programming Assignment 1
Traveling Salesmen
March 28, 2017
README File

To compile:
1) make
2) CS315PA1 <
    Followed by an input file such as Tests/test100.in
Optional 3) >
    Followed by an output file such as Tests/test100.out to store the output
    in a file instead of displaying it

The purpose of this program is to find the distance between given sets of cities
both from North to South and from West to East. This happens as the cities are
sorted both by their given latitudes and by their given longitudes. This is then
used to determine the order of the cities with which to calculate the distance.
For each City, data is given in the form:
                'Name' 'Latitude' 'Longitude'
This information is stored as a custom object City, and those are stored into
maps that each have a different key value. All of this is then manipulated
to determine the correct distances utilizing the Haversine Formula so that the
curvature of the earth is factored in.

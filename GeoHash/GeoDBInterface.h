#pragma once
#include <list>
using namespace std;

class GeoDBInterface
{
public:
    GeoDBInterface() {}
    virtual ~GeoDBInterface() {}
    virtual void InsertLocation(double lat, double lon) = 0;    // 0 indicates pure virtual, abstract
    virtual bool DeleteLocation(double lat, double lon) = 0;
    virtual std::vector<std::pair<double, double>> DeleteAll(double lat, double lon, int bitsOfPrecision) = 0;
    virtual bool ContainsLocation(double lat, double lon, int bitsOfPrecision) = 0;
    virtual std::vector<std::pair<double, double>> NearbyLocations(double lat, double lon, int bitsOfPrecision) = 0;
};


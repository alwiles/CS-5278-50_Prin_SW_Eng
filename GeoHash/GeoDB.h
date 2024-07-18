#pragma once
#include <vector> 
#include <stddef.h>
#include "GeoDBInterface.h"
#include "GeoHash.h"
#include "GeoHashDefs.h"

class GeoDB : GeoDBInterface
{
public:
    GeoDB(int bitsOfPrecision);
    ~GeoDB(){}
    void InsertLocation(double lat, double lon);
    bool DeleteLocation(double lat, double lon);
    std::vector<std::pair<double, double>> DeleteAll(double lat, double lon, int bitsOfPrecision);
    bool ContainsLocation(double lat, double lon, int bitsOfPrecision);
    std::vector<std::pair<double, double>> NearbyLocations(double lat, double lon, int bitsOfPrecision);

private:
    int m_bitsOfPrecision = 0;
    struct Node_s* m_rootNode = NULL;
    GeoHash m_geoHashGenerator;

    bool deleteNodes(struct Node_s* targetNode, uint32_t valueToDelete);
    std::vector<std::pair<double, double>> getAll();
    std::vector<std::pair<double, double>> traverseEntireTree();
    void treeTraversal(struct Node_s* node, std::vector<std::pair<double, double>>& visited);
    void clearTree();
    void clearTree(struct Node_s* node);
};


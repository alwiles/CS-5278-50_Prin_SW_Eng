#pragma once
#include "GeoDB.h"
class GeoDBFactory
{
public:
	static GeoDB CreateDatabase(int bitsOfPrecision);
};

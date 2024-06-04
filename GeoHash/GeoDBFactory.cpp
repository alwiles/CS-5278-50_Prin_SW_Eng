#include "GeoDBFactory.h"

GeoDB GeoDBFactory::CreateDatabase(int bitsOfPrecision)
{
	return GeoDB(bitsOfPrecision);
}

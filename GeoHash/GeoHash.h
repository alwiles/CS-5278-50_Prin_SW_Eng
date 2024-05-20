#pragma once

class GeoHash {
public:
	GeoHash(void);
	~GeoHash(void);
	void Sample(void);
	bool GetGeohashString(double targetValue1, double targetValue2, int bitsOfPrecision, char* outGeohashString);
	bool GetGeohashString(double targetValue, double* targetValueRange, int bitsOfPrecision, char* outGeohashString);
	int GetGeohashInteger(double targetValue1, double targetValue2, int bitsOfPrecision);
	
	double LATITUDE_RANGE[2] = { -90, 90 };
	double LONGITUDE_RANGE[2] = { -180, 180 };

private:
	bool ToHashString(short* bitArray, size_t sz, char* resultString);
	int To32BitInt(short* bitArray, size_t sz);
	bool Geohash1D(double valueToHash, double* valueRange, int bitsOfPrecision, short* outBitArray);
	bool Geohash2D(double v1, double* v1range, double v2, double* v2range, int bitsOfPrecision, short* outBitArray);
	bool IsEven(int value);
};

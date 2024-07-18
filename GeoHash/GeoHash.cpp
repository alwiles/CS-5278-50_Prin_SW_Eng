

// GeoHash.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <cstring>
#include "GeoHash.h"

#define SIZE_OF_INT 32
#define MAX_BITS_OF_PRECISION SIZE_OF_INT

GeoHash::GeoHash(void)
{
}

GeoHash::~GeoHash(void) = default;

void GeoHash::Sample(void)
{
	// 1st bit of the geohash
	double longitude = 0.0;
	double bounds[2] = { LONGITUDE_RANGE[0], LONGITUDE_RANGE[1] };
	double midpoint = (bounds[0] + bounds[1]) / 2;
	bool bit = false;

	if (longitude >= midpoint) {
		bit = true;
		bounds[0] = midpoint;
	}
	else {
		bit = false;
		bounds[1] = midpoint;
	}

	// 2nd bit of the geohash
	bool bit2 = false;
	midpoint = (bounds[0] + bounds[1]) / 2;
	if (longitude >= midpoint) {
		bit2 = true;
		bounds[0] = midpoint;
	}
	else {
		bit2 = false;
		bounds[1] = midpoint;
	}

	// 3rd bit of the geohash
	bool bit3 = false;
	midpoint = (bounds[0] + bounds[1]) / 2;
	if (longitude >= midpoint) {
		bit3 = true;
		bounds[0] = midpoint;
	}
	else {
		bit3 = false;
		bounds[1] = midpoint;
	}

	short bitArray[3] = { 0 };
	bitArray[0] = bit;
	bitArray[1] = bit2;
	bitArray[2] = bit3;

	int valueEncodedAsInteger = To32BitInt(bitArray, 3);
	char geocodeTestString[4] = { 0 }; // 4 for the null terminator
	bool testHashToString = ToHashString(bitArray, 4, geocodeTestString);
	std::cout << "Sample output string representation: " << geocodeTestString << ";\nInteger representation: " << valueEncodedAsInteger;

	return;
}

int GeoHash::To32BitInt(short* bitArray, size_t sz)
{
	//take array of bits and return the corresponding 
	//32 bit integer, little endian
	unsigned int result = 0;

	if (bitArray == NULL)
	{
		return 0;
	}
	if (sz > SIZE_OF_INT)
	{
		return 0; //out of range
	}

	int positionArray[SIZE_OF_INT] = { 0 };
	
	//initialize the position array
	for (int i = 0; i < SIZE_OF_INT; i++)
	{
		positionArray[i] = pow(2, i);
	}

	short* marker = bitArray;
	
	for (size_t n = 0; n < sz; n++)
	{
		short markerValue = *marker;
		if (markerValue)
		{
			result |= positionArray[n];
		}
		
		marker++;
	}

	return (int)result;
}

bool GeoHash::ToHashString(short* bitArray, size_t sz, char* resultString)
{
	//take array of bits and simply return a string representation

	if (bitArray == NULL)
	{
		return false;
	}
	if (resultString == NULL)
	{
		return false;
	}

	short* marker = bitArray;

	for (int n = 0; n < sz; n++)
	{
		marker = bitArray + n;
		short markerValue = *marker;
		resultString[n] = markerValue ? '1' : '0';		
	}

	//force null terminated
	resultString[sz - 1] = '\0';

	return true;
}

bool GeoHash::Geohash1D(double valueToHash, double* valueRange, int bitsOfPrecision, short* outBitArray)
{
	bool isSuccess = false;
	bool bit = false;
	
	if (valueRange == NULL)
	{
		return isSuccess;
	}
	if (outBitArray == NULL)
	{
		return isSuccess;
	}

	double lowerRangeBound = valueRange[0];
	double upperRangeBound = valueRange[1];
	double midpoint = (lowerRangeBound + upperRangeBound) / 2;

	if (bitsOfPrecision < 1 || bitsOfPrecision > MAX_BITS_OF_PRECISION)
	{
		return isSuccess;
	}

	for (int i = 0; i < bitsOfPrecision; i++)
	{
		bit = false;
		if (valueToHash >= midpoint) {
			bit = true;
			lowerRangeBound = midpoint;
		}
		else {
			bit = false;
			upperRangeBound = midpoint;
		}
		outBitArray[i] = bit;
		midpoint = (lowerRangeBound + upperRangeBound) / 2;
	}

	isSuccess = true;

	return isSuccess;
}

bool GeoHash::IsEven(int value)
{
	bool isEven = true;

	if (value == 0)
	{
		return isEven;
	}

	if (value % 2)
	{
		isEven = false;
	}

	return isEven;
}

bool GeoHash::Geohash2D(double v1, double* v1range, double v2, double* v2range, int bitsOfPrecision, short* outBitArray)
{
	bool isSuccess = false;
	short* bitArray1 = NULL;
	short* bitArray2 = NULL;

	if (bitsOfPrecision < 1 || bitsOfPrecision > MAX_BITS_OF_PRECISION)
	{
		return false;
	}

	if (v1range == NULL || v2range == NULL)
	{
		return false;
	}

	bitArray1 = (short*)malloc(sizeof(short) * bitsOfPrecision);
	bitArray2 = (short*)malloc(sizeof(short) * bitsOfPrecision);

	if (bitArray1 == NULL)
	{
		return false;
	}
	if (bitArray2 == NULL)
	{
		return false;
	}

	isSuccess = Geohash1D(v1, v1range, bitsOfPrecision, bitArray1);
	if (!isSuccess)
	{
		return isSuccess;
	}
	isSuccess = Geohash1D(v2, v2range, bitsOfPrecision, bitArray2);
	if (!isSuccess)
	{
		return isSuccess;
	}

	int idx = 0;
	for (int i = 0; i < bitsOfPrecision; i++)
	{
		short targetValue = (IsEven(i) ? bitArray1[idx] : bitArray2[idx]);
		outBitArray[i] = targetValue;
		if (!IsEven(i))
		{
			idx++;
		}
	}

	free(bitArray1);
	free(bitArray2);

	return isSuccess;
}

bool GeoHash::GetGeohashString(double targetValue1, double targetValue2, int bitsOfPrecision, char* outGeohashString)
{
	bool isSuccess = false;
	short* bitArray2D = NULL;

	if (bitsOfPrecision < 1 || bitsOfPrecision > MAX_BITS_OF_PRECISION)
	{
		return false;
	}

	if (outGeohashString == NULL)
	{
		return false;
	}
	
	bitArray2D = (short*)malloc(sizeof(short) * bitsOfPrecision);
	if (bitArray2D == NULL)
	{
		return false; //no memory
	}
	isSuccess = Geohash2D(targetValue1, LATITUDE_RANGE, targetValue2, LONGITUDE_RANGE, bitsOfPrecision, bitArray2D);
	if (!isSuccess)
	{
		if(bitArray2D)
		{
			free(bitArray2D);
		}
		
		return isSuccess;
	}
	isSuccess = ToHashString(bitArray2D, (size_t)bitsOfPrecision + 1, outGeohashString);

	if (bitArray2D)
	{
		free(bitArray2D);
	}

	return isSuccess;
}

bool GeoHash::GetGeohashString(double targetValue, double* targetValueRange, int bitsOfPrecision, char* outGeohashString)
{
	bool isSuccess = false;
	short* bitArray1D = NULL;

	if (targetValueRange == NULL)
	{
		return false;
	}

	if (bitsOfPrecision < 1 or bitsOfPrecision > MAX_BITS_OF_PRECISION)
	{
		return false;
	}

	bitArray1D = (short*)malloc(sizeof(short) * bitsOfPrecision);
	if (bitArray1D == NULL)
	{
		return false; //no memory
	}
	isSuccess = Geohash1D(targetValue, targetValueRange, bitsOfPrecision, bitArray1D);
	if (!isSuccess)
	{
		if (bitArray1D)
		{
			free(bitArray1D);
		}

		return isSuccess;
	}
	isSuccess = ToHashString(bitArray1D, (size_t)bitsOfPrecision + 1, outGeohashString);

	if (bitArray1D)
	{
		free(bitArray1D);
	}

	return isSuccess;
}

int GeoHash::GetGeohashInteger(double targetValue1, double targetValue2, int bitsOfPrecision)
{
	bool isSuccess = false;
	int resultValue = 0;
	short* bitArray2D = NULL;

	if (bitsOfPrecision < 1 || bitsOfPrecision > MAX_BITS_OF_PRECISION)
	{
		return 0;
	}

	bitArray2D = (short*)malloc(sizeof(short) * bitsOfPrecision); //aw test was bitsOfPrecision
	if (bitArray2D == NULL)
	{
		return 0; //no memory
	}
	
	memset((void*)bitArray2D, 0, sizeof(short) * bitsOfPrecision);
	isSuccess = Geohash2D(targetValue1, LATITUDE_RANGE, targetValue2, LONGITUDE_RANGE, bitsOfPrecision, bitArray2D);
	if (!isSuccess)
	{
		if (bitArray2D)
		{
			free(bitArray2D);
		}

		return 0;
	}

	resultValue = To32BitInt(bitArray2D, bitsOfPrecision);
	
	if (bitArray2D)
	{
		free(bitArray2D);
	}

	return resultValue;
}

	int main()
	{
		
		GeoHash myGeoHash = GeoHash();

		// just output the sample
		myGeoHash.Sample();

	}


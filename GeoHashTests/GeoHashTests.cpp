#include "pch.h"
#include "../GeoHash/GeoHash.h"
#include <gtest/gtest.h>


namespace GeoHashTests
{
	TEST(GeoHashTests, Test1)
	{
			GeoHash MyGeoHash = GeoHash();
			char geoHashString[6] = { 0 };

			MyGeoHash.GetGeohashString(MyGeoHash.LONGITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("00000", geoHashString);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LATITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("00000", geoHashString);

			MyGeoHash.GetGeohashString(MyGeoHash.LONGITUDE_RANGE[1], MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("11111", geoHashString);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[1], MyGeoHash.LATITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("11111", geoHashString);

			MyGeoHash.GetGeohashString(0, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("10000", geoHashString);

			MyGeoHash.GetGeohashString(90.0, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("11000", geoHashString);

			MyGeoHash.GetGeohashString(135.0, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("11100", geoHashString);

			MyGeoHash.GetGeohashString(157.5, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("11110", geoHashString);

			MyGeoHash.GetGeohashString(168.75, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("11111", geoHashString);

			MyGeoHash.GetGeohashString(-1, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("01111", geoHashString);

			MyGeoHash.GetGeohashString(-91.0, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("00111", geoHashString);

			MyGeoHash.GetGeohashString(-136.0, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("00011", geoHashString);

			MyGeoHash.GetGeohashString(-158.5, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("00001", geoHashString);

			MyGeoHash.GetGeohashString(-169.75, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			ASSERT_EQ("00000", geoHashString);

		}

		TEST(GeoHashTests, TestGeoHash2D)
		{
			GeoHash MyGeoHash = GeoHash();
			char geoHashString10Bit[11] = { 0 };
			char geoHashString11Bit[12] = { 0 };
			char geoHashString14Bit[15] = { 0 };

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[0], 10, geoHashString10Bit);
			ASSERT_EQ("0000000000", geoHashString10Bit);
			
			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[1], 10, geoHashString10Bit);
			ASSERT_EQ("0101010101", geoHashString10Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[1], 11, geoHashString11Bit);
			ASSERT_EQ("01010101010", geoHashString11Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[0], 11, geoHashString11Bit);
			ASSERT_EQ("00000000000", geoHashString11Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[1], -158.5, 10, geoHashString10Bit);
			ASSERT_EQ("1010101011", geoHashString10Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[1], -158.5, 11, geoHashString11Bit);
			ASSERT_EQ("10101010111", geoHashString11Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[1], -158.5, 14, geoHashString14Bit);
			ASSERT_EQ("10101010111111", geoHashString14Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[1], MyGeoHash.LONGITUDE_RANGE[1], 14, geoHashString14Bit);
			ASSERT_EQ("11111111111111", geoHashString14Bit);

		}

		TEST(GeoHashTests, TestIntegerEncoding)
		{
			GeoHash MyGeoHash = GeoHash();

			ASSERT_EQ(0, MyGeoHash.GetGeohashInteger(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[0], 10));
			ASSERT_EQ(682, MyGeoHash.GetGeohashInteger(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[1], 10));
			ASSERT_EQ(16213, MyGeoHash.GetGeohashInteger(MyGeoHash.LATITUDE_RANGE[1], -158.5, 14));
		}
	};


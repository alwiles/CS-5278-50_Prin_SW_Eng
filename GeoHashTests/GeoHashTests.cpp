#include "pch.h"
#include "CppUnitTest.h"
#include "../GeoHash/GeoHash.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeoHashTests
{
	TEST_CLASS(GeoHashTests)
	{
	public:
		
		TEST_METHOD(TestGeoHash1D)
		{
			GeoHash MyGeoHash = GeoHash();
			char geoHashString[6] = { 0 };

			MyGeoHash.GetGeohashString(MyGeoHash.LONGITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("00000", geoHashString);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LATITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("00000", geoHashString);

			MyGeoHash.GetGeohashString(MyGeoHash.LONGITUDE_RANGE[1], MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("11111", geoHashString);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[1], MyGeoHash.LATITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("11111", geoHashString);

			MyGeoHash.GetGeohashString(0, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("10000", geoHashString);

			MyGeoHash.GetGeohashString(90.0, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("11000", geoHashString);

			MyGeoHash.GetGeohashString(135.0, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("11100", geoHashString);

			MyGeoHash.GetGeohashString(157.5, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("11110", geoHashString);

			MyGeoHash.GetGeohashString(168.75, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("11111", geoHashString);

			MyGeoHash.GetGeohashString(-1, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("01111", geoHashString);

			MyGeoHash.GetGeohashString(-91.0, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("00111", geoHashString);

			MyGeoHash.GetGeohashString(-136.0, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("00011", geoHashString);

			MyGeoHash.GetGeohashString(-158.5, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("00001", geoHashString);

			MyGeoHash.GetGeohashString(-169.75, MyGeoHash.LONGITUDE_RANGE, 5, geoHashString);
			Assert::AreEqual("00000", geoHashString);

		}

		TEST_METHOD(TestGeoHash2D)
		{
			GeoHash MyGeoHash = GeoHash();
			char geoHashString10Bit[11] = { 0 };
			char geoHashString11Bit[12] = { 0 };
			char geoHashString14Bit[15] = { 0 };

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[0], 10, geoHashString10Bit);
			Assert::AreEqual("0000000000", geoHashString10Bit);
			
			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[1], 10, geoHashString10Bit);
			Assert::AreEqual("0101010101", geoHashString10Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[1], 11, geoHashString11Bit);
			Assert::AreEqual("01010101010", geoHashString11Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[0], 11, geoHashString11Bit);
			Assert::AreEqual("00000000000", geoHashString11Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[1], -158.5, 10, geoHashString10Bit);
			Assert::AreEqual("1010101011", geoHashString10Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[1], -158.5, 11, geoHashString11Bit);
			Assert::AreEqual("10101010111", geoHashString11Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[1], -158.5, 14, geoHashString14Bit);
			Assert::AreEqual("10101010111111", geoHashString14Bit);

			MyGeoHash.GetGeohashString(MyGeoHash.LATITUDE_RANGE[1], MyGeoHash.LONGITUDE_RANGE[1], 14, geoHashString14Bit);
			Assert::AreEqual("11111111111111", geoHashString14Bit);

		}

		TEST_METHOD(TestIntegerEncoding)
		{
			GeoHash MyGeoHash = GeoHash();

			Assert::AreEqual(0, MyGeoHash.GetGeohashInteger(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[0], 10));
			Assert::AreEqual(341, MyGeoHash.GetGeohashInteger(MyGeoHash.LATITUDE_RANGE[0], MyGeoHash.LONGITUDE_RANGE[1], 10));
			Assert::AreEqual(10943, MyGeoHash.GetGeohashInteger(MyGeoHash.LATITUDE_RANGE[1], -158.5, 14));
		}
	};
}

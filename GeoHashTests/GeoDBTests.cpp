#include "pch.h"
#include "CppUnitTest.h"
//#include "../GeoHash/GeoHash.h"
//#include "../GeoHash/GeoDB.h"
#include "../GeoHash/GeoDBFactory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GeoDBTests
{
	TEST_CLASS(GeoDBTests)
	{
	public:

		TEST_METHOD(TestSimpleInsert)
		{
			int bitsOfPrecision = 16;
			GeoDB db = GeoDBFactory::CreateDatabase(bitsOfPrecision);
			db.InsertLocation(0, 0);
			
			for (int i = 0; i < bitsOfPrecision; i++) {
				Assert::IsTrue(db.ContainsLocation(0, 0, i));
			}
		}

		TEST_METHOD(TestSimpleDelete)
		{
			int bitsOfPrecision = 16;
			GeoDB db = GeoDBFactory::CreateDatabase(bitsOfPrecision);
			db.InsertLocation(0, 0);
			db.DeleteLocation(0, 0);

			//changed this because 0 should always return true, per the requirements
			for (int i = 1; i < bitsOfPrecision; i++) { 
				// this test doesn't make a whole lot of sense, since simple delete uses the max precision
				// this assert only works because there was only a single entry inserted
				Assert::IsTrue(!db.ContainsLocation(0, 0, i));
			}
		}

		TEST_METHOD(TestZeroBits)
		{
			int bitsOfPrecision = 16;
			GeoDB db = GeoDBFactory::CreateDatabase(bitsOfPrecision);
			db.InsertLocation(0, 0);
			db.InsertLocation(90, 180);
			db.InsertLocation(-90, -180);
			db.InsertLocation(-90, 180);
			db.InsertLocation(90, -180);
			
			Assert::AreEqual(5.0, (double)db.NearbyLocations(0, 0, 0).size(), .01);
		}

		TEST_METHOD(TestZeroBitsDelete)
		{
			int bitsOfPrecision = 16;
			GeoDB db = GeoDBFactory::CreateDatabase(bitsOfPrecision);
			
			db.InsertLocation(0, 0);
			db.InsertLocation(90, 180);
			db.InsertLocation(-90, -180);
			db.InsertLocation(-90, 180);
			db.InsertLocation(90, -180);

			db.DeleteAll(0, 0, 0);

			Assert::AreEqual(0.0, (double)db.NearbyLocations(0, 0, 0).size(), .01);
		}

		TEST_METHOD(TestInsertDeleteSeries)
		{
			int bitsOfPrecision = 16;
			GeoDB db = GeoDBFactory::CreateDatabase(bitsOfPrecision);

			db.InsertLocation(0, 0);
			db.InsertLocation(90, 180);
			db.InsertLocation(-90, -180);
			db.InsertLocation(-90, 180);
			db.InsertLocation(90, -180);

			Assert::IsTrue(db.ContainsLocation(0, 0, 16));
			Assert::IsTrue(db.ContainsLocation(90, 180, 16));
			Assert::IsTrue(db.ContainsLocation(-90, -180, 16));
			Assert::IsTrue(db.ContainsLocation(-90, 180, 16));
			Assert::IsTrue(db.ContainsLocation(90, -180, 16));
			Assert::IsTrue(db.ContainsLocation(90.5, -180.5, 16));
			Assert::IsTrue(!db.ContainsLocation(1, -1, 16));
			Assert::IsTrue(!db.ContainsLocation(45, -45, 16));
			
			db.DeleteLocation(90, -180);
			Assert::IsTrue(!db.ContainsLocation(90, -180, 16));
			
			db.DeleteAll(1, 1, 1);
			Assert::IsTrue(db.ContainsLocation(-90, -180, 16));
			Assert::IsTrue(!db.ContainsLocation(90, 180, 16));
			
			db.InsertLocation(90, 180);
			Assert::IsTrue(db.ContainsLocation(90, 180, 16));
		}
	};
}

#include "pch.h"
#include "../GeoHash/GeoDBFactory.h"
#include <gtest/gtest.h>


namespace GeoDBTests
{
		TEST(GeoDBTests, TestSimpleInsert)
		{
			int bitsOfPrecision = 16;
			GeoDB db = GeoDBFactory::CreateDatabase(bitsOfPrecision);
			db.InsertLocation(0, 0);
			
			for (int i = 0; i < bitsOfPrecision; i++) {
				ASSERT_TRUE(db.ContainsLocation(0, 0, i));
			}
		}

		TEST(GeoDBTests, TestSimpleDelete)
		{
			int bitsOfPrecision = 16;
			GeoDB db = GeoDBFactory::CreateDatabase(bitsOfPrecision);
			db.InsertLocation(0, 0);
			db.DeleteLocation(0, 0);

			//changed this because 0 should always return true, per the requirements
			for (int i = 1; i < bitsOfPrecision; i++) { 
				// this test doesn't make a whole lot of sense, since simple delete uses the max precision
				// this assert only works because there was only a single entry inserted
				ASSERT_TRUE(!db.ContainsLocation(0, 0, i));
			}
		}

		TEST(GeoDBTests, TestZeroBits)
		{
			int bitsOfPrecision = 16;
			GeoDB db = GeoDBFactory::CreateDatabase(bitsOfPrecision);
			db.InsertLocation(0, 0);
			db.InsertLocation(90, 180);
			db.InsertLocation(-90, -180);
			db.InsertLocation(-90, 180);
			db.InsertLocation(90, -180);
			
			ASSERT_FLOAT_EQ(5.0, (double)db.NearbyLocations(0, 0, 0).size());
		}

		TEST(GeoDBTests, TestZeroBitsDelete)
		{
			int bitsOfPrecision = 16;
			GeoDB db = GeoDBFactory::CreateDatabase(bitsOfPrecision);
			
			db.InsertLocation(0, 0);
			db.InsertLocation(90, 180);
			db.InsertLocation(-90, -180);
			db.InsertLocation(-90, 180);
			db.InsertLocation(90, -180);

			db.DeleteAll(0, 0, 0);

			ASSERT_FLOAT_EQ(0.0, (double)db.NearbyLocations(0, 0, 0).size());
		}

		TEST(GeoDBTests, TestInsertDeleteSeries)
		{
			int bitsOfPrecision = 16;
			GeoDB db = GeoDBFactory::CreateDatabase(bitsOfPrecision);

			db.InsertLocation(0, 0);
			db.InsertLocation(90, 180);
			db.InsertLocation(-90, -180);
			db.InsertLocation(-90, 180);
			db.InsertLocation(90, -180);

			ASSERT_TRUE(db.ContainsLocation(0, 0, 16));
			ASSERT_TRUE(db.ContainsLocation(90, 180, 16));
			ASSERT_TRUE(db.ContainsLocation(-90, -180, 16));
			ASSERT_TRUE(db.ContainsLocation(-90, 180, 16));
			ASSERT_TRUE(db.ContainsLocation(90, -180, 16));
			ASSERT_TRUE(db.ContainsLocation(90.5, -180.5, 16));
			ASSERT_TRUE(!db.ContainsLocation(1, -1, 16));
			ASSERT_TRUE(!db.ContainsLocation(45, -45, 16));
			
			db.DeleteLocation(90, -180);
			ASSERT_TRUE(!db.ContainsLocation(90, -180, 16));
			
			db.DeleteAll(1, 1, 1);
			ASSERT_TRUE(db.ContainsLocation(-90, -180, 16));
			ASSERT_TRUE(!db.ContainsLocation(90, 180, 16));
			
			db.InsertLocation(90, 180);
			ASSERT_TRUE(db.ContainsLocation(90, 180, 16));
		}
	
}

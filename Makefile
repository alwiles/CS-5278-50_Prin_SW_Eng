output: GeoDB.o
	g++ GeoDB.o -o output

GeoDB.o: GeoHash/GeoHash.cpp GeoHash/GeoHash.h GeoHash/GeoDB.cpp GeoHash/GeoDB.h
	g++ -c GeoHash/GeoHash.cpp GeoHash/GeoDB.cpp GeoHash/GeoDBFactory.cpp

clean:
	rem *.o output
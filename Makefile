output: GeoDB.o
	g++ GeoDB.o -o output

GeoDB.o: GeoHash/GeoDB.cpp GeoHash/GeoDB.h
	g++ -c GeoDB.cpp

clean:
	rem *.o output
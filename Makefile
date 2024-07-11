output: GeoDB.o
	gcc GeoDB.o -o output

GeoDB.o: GeoDB.cpp
	gcc -c MakfileTest.cpp

clean:
	rem *.o output
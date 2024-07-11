output: GeoDB.o
	gcc GeoDB.o -o output

GeoDB.o: GeoDB.cpp GeoDB.h
	gcc -c GeoDB.cpp

clean:
	rem *.o output
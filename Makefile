all: GenreCounter.out maps.out reduce.out

GenreCounter.out: GenreCounter.o
	g++ GenreCounter.o -o GenreCounter.out

GenreCounter.o: GenreCounter.cpp
	g++ -c GenreCounter.cpp -o GenreCounter.o

maps.out: maps.o
	g++ maps.o -o maps.out

maps.o: maps.cpp
	g++ -c maps.cpp -o maps.o

reduce.out: reduce.o
	g++ reduce.o -o reduce.out

reduce.o: reduce.cpp
	g++ -c reduce.cpp -o reduce.o

clean:
	rm -rf *.out
	rm -r -f *.o
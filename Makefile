Flags = -std=c++11 -Wall -Wextra

server : Makefile server.o responseBuilder.o utils.o sockwrap.o
	g++ $(Flags) -o server server.o responseBuilder.o utils.o sockwrap.o

server.o : Makefile server.cpp utils.o responseBuilder.o
	g++ -c $(Flags) server.cpp -o  server.o

responseBuilder.o : Makefile responseBuilder.cpp utils.o
	g++ -c $(Flags) responseBuilder.cpp -o responseBuilder.o

utils.o : Makefile utils.cpp
	g++ -c $(Flags) utils.cpp -o utils.o

sockwrap.o : Makefile sockwrap.c
	g++ -c $(Flags) sockwrap.c -o sockwrap.o

clean:
	rm -rf *.o

distclean:
	rm -rf *.o server .*.swp
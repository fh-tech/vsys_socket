all: socket-lib

socket-lib: *.o
	cd ../../bin/ && ar rcs socketlib.a ../build/lib/*.o

*.o: *.cpp *.h
	cd ../../build/lib/ && g++ -Wall -Wextra -Werror -c ../../src/shared/*.cpp

clean:
	cd ../../build/lib/ && rm -f *.o *.gch *.a
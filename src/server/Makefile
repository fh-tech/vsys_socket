all: server

server: lib *.o
	cd ../../bin/ && g++ -Wall -Wextra -Werror -o server ../build/server/*.o socketlib.a

lib: ../shared/*.cpp
	cd ../shared/ && make

*.o: *.cpp
	cd ../../build/server/ && g++ -Wall -Wextra -Werror -c ../../src/server/*.cpp

clean:
	cd ../../build/server/ && rm -f *.o *.gch *.a
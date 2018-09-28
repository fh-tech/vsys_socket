all: client

client: lib *.o
	cd ../../bin/ && g++ -Wall -Wextra -Werror -g -o client ../build/client/*.o socketlib.a

lib: ../shared/*.cpp
	cd ../shared/ && make

*.o: *.cpp
	cd ../../build/client/ && gcc -Wall -Wextra -Werror -g -c ../../src/client/*.cpp

clean:
	cd ../../build/client/ && rm -f *.o *.gch *.a
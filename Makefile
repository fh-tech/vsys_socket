all: lib server client

server:
	cd src/server && make

client:
	cd src/client && make

lib:
	cd src/shared && make

clean:
	cd src/server && make clean
	cd src/client && make clean
	cd src/shared && make clean

.PHONY: lib
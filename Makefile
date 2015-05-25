noisy-mingw:
	mingw32-g++ -std=c++11 -I include/ -c src/noisy.cpp -o bin/noisy.o
	mingw32-g++ -o bin/noisy.exe bin/noisy.o
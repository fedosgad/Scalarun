STD = --std=c++11


all: interface math generator

interface: rtl-sdr_interface.cpp
	g++ $(STD) -c -o rtl-sdr_interface.o rtl-sdr_interface.cpp

math: math.cpp
	g++ $(STD) -c -fopenmp -o math.o math.cpp -lfftw3 -lfftw3_omp

generator: generator.cpp
	g++ $(STD) -c -o generator.o generator.cpp

clean:
	rm -f *.o

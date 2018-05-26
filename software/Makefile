STD = --std=c++11


all: interface math generator

interface: rtl-sdr_interface.cpp
	g++ $(STD) -c -o rtl-sdr_interface.o rtl-sdr_interface.cpp

math: math.cpp
	g++ $(STD) -c -o math.o math.cpp

generator: generator.cpp
	g++ $(STD) -c -o generator.o generator.cpp

clean:
	rm *.o

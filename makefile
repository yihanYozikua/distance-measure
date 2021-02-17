# MAKEFILE

OPENCV = `pkg-config --cflags --libs opencv4`
LIBS = $(OPENCV)

# all: tools.o main.o	
# 	g++ -std=c++11 $(LIBS) tools.o main.o -o main
# tools.o: tools.cpp tools.h
# 	g++ -std=c++11 $(LIBS) -c tools.cpp
# main.o: main.cpp 
# 	g++ -std=c++11 $(LIBS) -c main.cpp 

main:
	g++ -std=c++11 $(LIBS) main.cpp tools.cpp backend.cpp dataProcessing.cpp -o main

clean:
	rm -f *.o main
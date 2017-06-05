CXX=g++
CXXFLAGS=-Wall -pedantic -g -std=c++11 -Wno-long-long -O0 -ggdb
EXECUTABLE=buresda4
SOURCES=./src/main.cpp ./src/game.cpp ./src/background.cpp ./src/load.cpp ./src/ship.cpp ./src/bullet.cpp ./src/obstacleC.cpp ./src/obstacleB.cpp ./src/obstacleA.cpp ./src/obstacle.cpp ./src/yxpart.cpp ./src/timer.cpp ./src/object.cpp


all:
	make compile
	make doc

doc:
	doxygen ./src/doxyfile.cpp

compile:$(SOURCES:.cpp=.o)
		$(CXX) $(SOURCES:.cpp=.o) -o $(EXECUTABLE) -lncurses
		 
clean:
	$(RM) $(SOURCES:.cpp=.o) $(EXECUTABLE)
	rm -rf ./doc

run:
	./buresda4

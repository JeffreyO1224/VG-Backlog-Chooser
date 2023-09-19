CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -O2

PROG ?= VGChooser
OBJS = Chooser.o main.o

all: $(PROG)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(PROG): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	rm -rf $(EXEC) *.o *.out VGChooser results.txt

rebuild: clean all

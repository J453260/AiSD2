ifeq ($(OS), Windows_NT)
    RM = del /f /q
else
    RM = rm -f
endif

CXX = g++
LIBS =
CXXFLAGS = -Wall -Wextra -std=c++17 -g
OBJECTS = main.o
#HFILES = edge.hpp basegraph.hpp iterator.hpp graph.hpp bfs.hpp
HFILES = bfs.hpp
TARGET = main.out

%.o : %.cpp $(HFILES) Makefile
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LIBS) -o $(TARGET)

.PHONY : clean run all

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean :
	$(RM) $(TARGET) *.o core

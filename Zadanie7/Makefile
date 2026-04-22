CXX = g++
CXXFLAGS = -Wall -Wextra -g
OBJECTS = main.o
HFILES = graph.hpp connected.hpp
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

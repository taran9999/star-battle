CXX = g++
CXXFLAGS = -Wall -Wextra
LXXFLAGS = -lSDL2

TARGET = main

SRCS = main.cpp grid.cpp puzzle.cpp solver.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LXXFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
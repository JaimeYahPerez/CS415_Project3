CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
TARGET = a.out
SOURCES = main.cpp input.cpp stdtrie.cpp bsttrie.cpp
HEADERS = input.hpp stdtrie.hpp bsttrie.hpp

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean

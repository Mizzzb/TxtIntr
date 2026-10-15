CX	 = g++
CXXFLAGS = -Wall -Wextra -O2
SRC      = calc.cpp
TARGET   = calc

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean

CXX = g++
CXXFLAGS = -I./src
SRC = src/Item.cpp src/test_Item.cpp src/NPC.cpp src/test_NPC.cpp
TARGET = test_NPC

all: $(TARGET)

$(TARGET): $(SRC)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
    rm -f $(TARGET)
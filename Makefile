CXXFLAGS += -std=c++17
LDFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs -IprovaPGE
CC = g++

SRCDIR = provaPGE
SRC = $(wildcard $(SRCDIR)/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = celestial
VPATH = $(SRCDIR)

.PHONY: all clean

all: $(TARGET)

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o $@ -c $^

$(TARGET): $(OBJ)
	$(CC) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)

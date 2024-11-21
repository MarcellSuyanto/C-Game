CXX = g++                   
CXXFLAGS = -std=c++11 -pedantic-errors  
SRC = main.cpp blackjack.cpp HighOrLow.cpp slotmachine.cpp Baccarat.cpp playingcards.cpp profile.cpp

TARGET = run
all: $(TARGET)
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
clean:
	rm -f $(TARGET) *.o
.PHONY: all clean

CC = g++
CFLAGS = -Wall -g

#CFLAGS = -Wall -O2

TARGET = CA_SIMULATOR

all:  $(TARGET)

CA_SIMULATOR: main.o human.o CA.o globals.o
	$(CC) $(CFLAGS) -o CA_SIMULATOR main.o human.o CA.o globals.o

main.o: main.cpp human.hpp CA.hpp globals.hpp
	$(CC) $(CFLAGS) -c main.cpp

CA.o: CA.hpp human.hpp globals.hpp

human.o: human.hpp globals.hpp

globals.o: globals.hpp

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)
	rm *.o

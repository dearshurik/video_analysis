CC=g++
EXEC=main
CFLAGS=-std=gnu++14 -I../include -g -Wall
LDFLAGS=-lvideoanalysis -L../lib

SOURCES= \
	main.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(EXEC)
	
$(EXEC): $(OBJECTS) 
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	
%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm $(OBJECTS) $(EXEC)

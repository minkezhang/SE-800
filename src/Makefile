CC=g++
CFLAGS=-Wall -Werror -O3 -std=c++11
LIBS=-pthread -lm

# all the source files that we need
SOURCES=classes/*cpp *cpp
OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=se800

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

clean:
	rm -f $(EXECUTABLE) *.o

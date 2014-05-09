CC=g++

# beware synchronization issues with -O3 -- remember to use volatile for shared variables
# CFLAGS=-Wall -Werror -O3 -std=c++11 -g
CFLAGS=-Wall -std=c++11 -g
LIBS=-pthread -lm -lprotobuf

# all the source files that we need should be listed here
SOURCES=engines/*/*cc ../lib/*cc *cc networks/server.cc networks/packetprotos.pb.cc networks/netpacket.cc classes/ship.cc
OBJECTS=$(SOURCES:.c*=.o)

EXECUTABLE=se800

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

clean:
	rm -f $(EXECUTABLE) *.o

run: $(EXECUTABLE)
	valgrind ./$(EXECUTABLE) server 6667

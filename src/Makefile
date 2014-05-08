CC=g++

# beware synchronization issues with -O3 -- remember to use volatile for shared variables
# CFLAGS=-Wall -Werror -O3 -std=c++11
CFLAGS=-Wall -O3 -std=c++11
LIBS=-pthread -lm -lprotobuf

# all the source files that we need should be listed here
SOURCES=engines/*/*cpp engines/physics/*cc ../lib/*cpp *cpp networks/server.cc networks/packetprotos.pb.cc networks/netpacket.cc classes/ship.cc # networks/client.cc
OBJECTS=$(SOURCES:.c*=.o)

EXECUTABLE=se800

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

clean:
	rm -f $(EXECUTABLE) *.o

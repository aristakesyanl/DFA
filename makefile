CFLAGS=-c -Wall
LDFLAGS=
SOURCES=DFA.cpp Source.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=dfa

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

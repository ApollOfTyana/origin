.PHONY: all clean install uninstall run

CC = clang++
CXXFLAGS = -Wall -std=c++17
LDFLAGS =
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(EXECUTABLE) *.o out.txt

install:
	@echo "Installing..."
	@cp $(EXECUTABLE) /usr/local/bin/

uninstall:
	@echo "Uninstalling..."
	@rm -f /usr/local/bin/$(EXECUTABLE)

run:
	@./$(EXECUTABLE)
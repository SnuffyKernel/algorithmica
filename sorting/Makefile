CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -O3
SRCS = sorting.cpp command_line.cpp
OBJS = $(SRCS:.cpp=.o)

RUN = ./$(TARGET)
DEBUG = $(RUN) -d
RUN_ALL = $(DEBUG) -r 10000 -np

ifeq ($(OS),Windows_NT)
	TARGET = sorting.exe
	RM = del /Q
else
	TARGET = sorting
	RM = rm -f
endif

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(TARGET)

run: $(TARGET)
	$(RUN)

debug: $(TARGET)
	$(DEBUG)

run_all: $(TARGET)
	$(RUN_ALL)

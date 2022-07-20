MAKEFLAGS += --silent

CXX = g++
CXXFLAGS = -Wall -std=c++17

BUILD = build
EXECUTABLE = build/main.out
LDLIBS = $(shell pkg-config sfml-all --libs)
SOURCE_FOLDER = src
INCLUDE = include

CPPFLAGS = -I $(INCLUDE)

SOURCES = $(wildcard $(SOURCE_FOLDER)/*)
BUILDS = $(patsubst $(SOURCE_FOLDER)/%.cpp, $(BUILD)/%.o, $(SOURCES))

run: $(EXECUTABLE)
	$(EXECUTABLE)

$(EXECUTABLE): $(BUILDS)
	$(CXX) $(BUILDS) $(CPPFLAGS) -o $(EXECUTABLE) $(LDLIBS)

$(BUILD)/%.o: $(SOURCE_FOLDER)/%.cpp $(INCLUDE)/%.h
	$(CXX) $(CXXFLAGS) $< -c -o $@ $(CPPFLAGS)

$(BUILD)/Main.o: $(SOURCE_FOLDER)/Main.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@ $(CPPFLAGS)

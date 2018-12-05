	CC := g++
CPPFLAGS := -std=c++11 -Wall 
CXXFLAGS := -MMD
LFLAGS := `pkg-config --cflags --libs gtkIOStream`
LDFLAGS := -lwiringPi -ljack
LDFLAGS_OSX :=

SRC := ./src
OBJ := ./obj
BUILD := ./build

SRC_FILES := $(wildcard $(SRC)/*.cpp)
OBJ_FILES := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILES))

Darwin = Darwin

uname_s := $(shell uname -s)
$(info uname_s=$(uname_s))
uname_m := $(shell uname -m)
$(info uname_m=$(uname_m))


all: $(BUILD)/rsynth


$(BUILD)/rsynth: $(OBJ_FILES)

	g++ $(LDFLAGS) -o $@ $^
#	g++ $(LDFLAGS_OSX) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp 
	g++ $(CPPFLAGS) $(CXXFLAGS) $(LFLAGS) -I./src -c -o $@ $<
#	g++ $(CPPFLAGS) $(CXXFLAGS) -I./src -c -o $@ $<

clean:
	rm -f $(OBJ)/*.o $(OBJ)/*.d $(BUILD)/rsynth


-include $(OBJ_FILES:.o=.d)

SRC_DIR   = src
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LINUX   = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.linux.o,$(SRC))
OBJ_WINDOWS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.win.o,$(SRC))
CXX_LINUX   = g++
CXX_WINDOWS = x86_64-w64-mingw32-g++
CXXFLAGS = -std=c++11 -Wall -O2
WINFLAGS = -static
TARGET_LINUX   = $(BUILD_DIR)/Backgammon
TARGET_WINDOWS = $(BUILD_DIR)/Backgammon.exe
all: $(TARGET_LINUX) $(TARGET_WINDOWS)
#Linux
$(TARGET_LINUX): $(OBJ_LINUX)
	$(CXX_LINUX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.linux.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX_LINUX) $(CXXFLAGS) -c $< -o $@
#Windows
$(TARGET_WINDOWS): $(OBJ_WINDOWS)
	$(CXX_WINDOWS) $(CXXFLAGS) $(WINFLAGS) -o $@ $^

$(BUILD_DIR)/%.win.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX_WINDOWS) $(CXXFLAGS) $(WINFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean

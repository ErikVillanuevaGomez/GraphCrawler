CXX = g++
CXXFLAGS = -O3 -std=c++17

RAPIDJSON_INCLUDE_DIR = -I./rapidjson/include

LIBS = -lcurl

TARGET = GraphCrawler

all: $(TARGET)

$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) $(RAPIDJSON_INCLUDE_DIR) -o $(TARGET) main.cpp $(LIBS)

clean:
	rm -f $(TARGET)

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -O2
GTEST_INC = -I$(shell brew --prefix)/include/
GTEST_LDLIBS = -lgtest -lgtest_main
GTEST_LDFLAGS = -L$(shell brew --prefix)/lib/

TARGET = peak peak_unittest
SRCS = $(shell ls *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

all: peak

peak: main.o methods.o
	$(CXX) $(CXXFLAGS) -o $@ $^

peak_unittest: main_unittest.o methods_unittest.o methods.o
	$(CXX) $(CXXFLAGS) $(GTEST_INC) -o $@ $^ $(GTEST_LDFLAGS) $(GTEST_LDLIBS)
	./$@

$(filter %_unittest.o, $(OBJS)): %.o: %.cpp
	$(CXX) $(CXXFLAGS) $(GTEST_INC) -c -MMD -o $@ $<

$(filter-out %_unittest.o, $(OBJS)): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

.PHONY: all clean
-include $(DEPS)

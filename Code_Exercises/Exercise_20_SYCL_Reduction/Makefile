CXX := clang++

SOURCES := $(wildcard *.cpp)
TARGETS := $(SOURCES:.cpp=)

INCLUDE_FLAGS := -I../../Utilities/include
CXX_FLAGS := -fsycl $(INCLUDE_FLAGS) $(TRIPLE)

.PHONY: all clean run

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

run: $(TARGETS)
	for target in $^; do echo "./$$target" && ./$$target ; done

clean:
	rm -f $(TARGETS) report*

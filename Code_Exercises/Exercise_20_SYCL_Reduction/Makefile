CXX := clang++
CXXFLAGS := -fsycl -fsycl-targets=nvidia_gpu_sm_60

SOURCES := $(wildcard *.cpp)
TARGETS := $(SOURCES:.cpp=)

.PHONY: all clean run profile

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

run: $(TARGETS)
	for target in $^; do echo "./$$target" && ./$$target ; done

profile: $(TARGETS)
	for target in $^; do \
		echo "\n\nProfiling $$target\n\n" && nsys profile --stats=true ./$$target ; \
	done

clean:
	rm -f $(TARGETS) report*

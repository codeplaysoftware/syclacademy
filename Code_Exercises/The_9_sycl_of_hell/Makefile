CXX ?= icpx
CXXFLAGS ?= -fsycl

SRCS := $(wildcard *.cpp)
PRGS := $(patsubst %.cpp,%,$(SRCS))
RUN :=  $(addprefix run_, $(PRGS))

.PHONY: all
all: $(PRGS)

.PHONY: run_all
run_all: $(sort $(RUN))

%: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

run_%:%
	./$^

.PHONY: clean
clean:
	rm -f $(PRGS)

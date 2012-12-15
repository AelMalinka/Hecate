CXXFLAGS := -Wall -Wextra -Werror -pedantic-errors -std=c++0x $(CXXFLAGS)

ifeq ($(DEBUG),1)
	CXXFLAGS := $(CXXFLAGS) -O0 -g3 -ggdb -DDEBUG
endif

default: test

TARGETS = libHecate.so
TESTS = Percentage

clean:
	rm -rf build
	rm -f $(TARGETS)

all: $(TARGETS)

.PHONY: default clean test all

libHecate.so: build/libHecate.so
	cp -f build/libHecate.so $@

HECATE = Percentage
HECATE_OBJS = $(foreach i,$(HECATE),build/src/$(i).o)
HECATE_FLAGS = $(CXXFLAGS) -fPIC
HECATE_LDFLAGS = $(LDFLAGS) -shared

$(HECATE_OBJS): build/src/%.o: src/%.cc
	mkdir -p build/src
	$(CXX) $(HECATE_FLAGS) -c -o $@ $<

build/libHecate.so: $(HECATE_OBJS)
	$(CC) $(HECATE_LDFLAGS) -o $@ $(HECATE_OBJS)

TEST_BINS = $(foreach test,$(TESTS),build/test/$(test).t)
TEST_FLAGS = $(CXXFLAGS) -Isrc
TEST_LDFLAGS = $(LDFLAGS) -pthread -lgtest -lgtest_main -L. -lHecate

$(TEST_BINS): build/test/%.t: test/%.cc libHecate.so
	mkdir -p build/test
	$(CXX) $(TEST_FLAGS) $(TEST_LDFLAGS) -o $@ $<

test: all $(TEST_BINS)
	for t in $(TEST_BINS) ; do \
		LD_LIBRARY_PATH=".:${LD_LIBRARY_PATH}" $$t; \
	done

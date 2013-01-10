TARGETS = libHecate.so
# 2012-12-28 AMR TODO: make double recursive variable
TESTS = Percentage Stat

libHecate.so: build/libHecate.so
	cp -f build/libHecate.so $@

libHecate.so = Percentage Stat
HECATE_OBJS = $(foreach i,$(libHecate.so),build/src/$(i).o)
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

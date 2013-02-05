TARGETS = libHecate.so
# 2012-12-28 AMR TODO: make double recursive variable
TESTS = Percentage StatPrototype #Stat

libHecate.so: build/libHecate.so
	cp -f build/libHecate.so $@

libHecate.so = StatPrototype
libHecate.so_OBJS = $(foreach i,$(libHecate.so),build/src/$(i).o)
libHecate.so_FLAGS = $(CXXFLAGS) -fPIC -I../Main/build
libHecate.so_LDFLAGS = $(LDFLAGS) -shared

$(libHecate.so_OBJS): build/src/%.o: src/%.cc
	mkdir -p build/src
	$(CXX) $(libHecate.so_FLAGS) -c -o $@ $<

build/libHecate.so: $(libHecate.so_OBJS)
	$(CC) $(libHecate.so_LDFLAGS) -o $@ $(libHecate.so_OBJS)

TEST_BINS = $(foreach test,$(TESTS),build/test/$(test).t)
TEST_FLAGS = $(CXXFLAGS) -Isrc -I../Main/build
TEST_LDFLAGS = $(LDFLAGS) -pthread -lgtest -lgtest_main -L. -lHecate

all:

#
# test Makefile
#

TOPDIR= ../
-include $(TOPDIR)/Makefile.config.incl

TARGET= cppunit-test.exe
all: $(TARGET)

SRC:= $(wildcard *.cpp)
OBJS= $(patsubst %.cpp,%.o,$(SRC))
DEPS= $(patsubst %.cpp,%.d,$(SRC))

%.o: %.cpp
	@$(MAKEDEPEND)
	$(CXX) $(CXXFLAGS) -c $<

-include $(DEPS)

clean:
	rm -f $(OBJS)

cleaner: clean
	rm -f $(DEPS)

cleanest: cleaner
	rm -f $(TARGET)

$(TARGET): $(OBJS) $(LIB_CREATED_FILE)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIB_CREATED_INCL) $(LIB_CPPUNIT_INCL)

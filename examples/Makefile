all:

#
# src Makefile
#

TOPDIR= ../
-include $(TOPDIR)/Makefile.config.incl

SRC:= $(wildcard *.cpp)
DEPS= $(patsubst %.cpp,%.d,$(SRC))
OBJS= $(patsubst %.cpp,%.o,$(SRC))
EXES= $(patsubst %.cpp,%.exe,$(SRC))

all: $(EXES)

%.o: %.cpp
	@$(MAKEDEPEND)
	$(CXX) $(CXXFLAGS) -c $<

%.exe: %.o $(LIB_CREATED_FILE)
	@$(MAKEDEPEND)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIB_CREATED_LINK})

-include $(DEPS)

clean:
	rm -f $(OBJS)

cleaner: clean
	rm -f $(DEPS)

cleanest: cleaner
	rm -f $(EXES)

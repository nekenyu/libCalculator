all:

#
# src Makefile
#

TOPDIR= ../
-include $(TOPDIR)/Makefile.config.incl

TARGET= $(LIB_CREATED_FILE)
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

$(TARGET): $(TARGET)($(OBJS))

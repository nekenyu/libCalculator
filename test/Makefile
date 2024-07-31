#
# test Makefile
#

TOPDIR= ../

# Libraries
include $(TOPDIR)/Makefile.lib.incl
CXXFLAGS+= ${LIB_CALCULATOR_FLAGS}
LIBS+= ${LIB_CALCULATOR_LIBS}

CXXFLAGS+= ${LIB_CPPUNIT_FLAGS}
LIBS+= ${LIB_CPPUNIT_LIBS}

# Targets
MAKE_EXE=cppunit-test.exe
include $(TOPDIR)/Make/Makefile.incl

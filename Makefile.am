bin_PROGRAMS = \
	tsfilter \
	tsanalyse

tsfilter_SOURCES = src/tsfilter.cpp

tsanalyse_SOURCES = src/tsanalyse.cpp
	    
check_PROGRAMS = test/testPSI

test_testPSI_SOURCES = test/testPSI.cpp

TESTS_ENVIRONMENT = builddir=$(builddir)
TESTS = test/testBasic.sh \
	    test/testArgs.sh \
	    test/testClean.sh \
	    test/testAuto.sh \
	    test/testPSI
	    
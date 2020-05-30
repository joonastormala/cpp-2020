# For MacOS: install homebrew, run command "brew install gcc" and uncomment the next line if clang does not work
#CXX=g++-9

GCHECK_DIR = ../../../gcheck

include $(GCHECK_DIR)/vars.make
GCHECK_OBJECTS:=$(foreach OBJECT, $(GCHECK_OBJECTS), $(GCHECK_DIR)/$(OBJECT))

# Where to find user code.
USER_DIR = ../src
TEST_DIR = .

HEADERS := $(foreach HEADER, $(HEADERS), $(USER_DIR)/$(HEADER))

# Flags passed to the preprocessor.
# Set gcheck's header directory as a system directory, such that
# the compiler doesn't generate warnings in gcheck headers.
CPPFLAGS += -c -isystem $(GCHECK_DIR)

# Flags passed to the C++ compiler.
CXXFLAGS += -std=c++17 -g -Wall -Wextra -Wno-missing-field-initializers

# All gcheck headers. Usually you shouldn't change this definition.
GCHECK_HEADERS = $(GCHECK_DIR)/gcheck.h $(GCHECK_DIR)/argument.h

ifeq ($(OS),Windows_NT)
	RM=del /f /q
	TEST:=$(TESTNAME).exe
else
	RM=rm -f
	TEST:=$(TESTNAME)
endif

# House-keeping build targets.

.PHONY: all clean clean-all run run-test valgrind-run get-results get-points get-report

all : $(TEST)
	
clean :
	$(RM) $(TESTNAME) $(TESTNAME).exe *.o report.json output.html valgrind_out.txt $(CLEAN_FILES)

clean-all : clean
	$(MAKE) -C $(GCHECK_DIR) clean

run: $(TEST)
	./$(TEST)

run-test: clean $(TEST)
	./$(TEST) --json report.json

valgrind-run: clean $(TEST)
	valgrind --track-origins=yes --leak-check=full ./$(TEST)
	
valgrind-run-test: clean $(TEST)
	valgrind -q --track-origins=yes --leak-check=full --log-file=valgrind_out.txt ./$(TEST) --json report.json

get-results:
	../../../scripts/get_results.sh "$(GCHECK_DIR)/beautify.py -p $(MAX_POINTS)"

get-report: $(TEST)
	./$(TEST) --json report.json


# $(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

# Builds a sample test.

$(TEST).o : $(TEST_DIR)/$(TEST_SOURCE) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(TEST_DIR)/$(TEST_SOURCE) -o $@

$(OBJECTS): %.o : $(USER_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
	
$(GCHECK_OBJECTS): %.o : %.cpp $(GCHECK_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -o $@
	
$(COBJECTS): %.o : $(USER_DIR)/%.c $(HEADERS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@
	
$(TEST): $(OBJECTS) $(COBJECTS) $(TEST).o $(GCHECK_OBJECTS)
	$(CXX) $(LDFLAGS) $(LOADLIBES) $(LDLIBS) $(OBJECTS) $(COBJECTS) $(TEST).o $(GCHECK_OBJECTS) -o $@

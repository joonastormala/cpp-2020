MAIN_DIR = src
TEST_DIR = test

.PHONY: main test clean clean-all run-main run-test valgrind-run valgrind-test get-points get-results

all: main test

main:
	$(MAKE) -C $(MAIN_DIR)

test:
	$(MAKE) -C $(TEST_DIR)

clean:
	$(MAKE) -C $(MAIN_DIR) clean
	$(MAKE) -C $(TEST_DIR) clean

clean-all:
	$(MAKE) -C $(MAIN_DIR) clean
	$(MAKE) -C $(TEST_DIR) clean-all

run-main:
	$(MAKE) -C $(MAIN_DIR) run

run-test:
	$(MAKE) -C $(TEST_DIR) run
	
run-test-json:
	$(MAKE) -C $(TEST_DIR) run-test

valgrind-run:
	$(MAKE) -C $(MAIN_DIR) valgrind-run
	
valgrind-test:
	$(MAKE) -C $(TEST_DIR) valgrind-run
	
valgrind-test-json:
	$(MAKE) -C $(TEST_DIR) valgrind-run-test

get-points:
	$(MAKE) -C $(TEST_DIR) get-points
	
get-results:
	$(MAKE) -C $(TEST_DIR) get-results
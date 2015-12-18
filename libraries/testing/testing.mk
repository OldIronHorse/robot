TEST_BASE_DIR=$(USER_LIB_PATH)/testing
TEST_DIR=$(CURDIR)/test
TESTBIN_DIR=$(TEST_DIR)/bin
TESTOBJ_DIR=$(TEST_DIR)/obj

TEST_BASE_SRCS=$(wildcard $(TEST_BASE_DIR)/*.cpp) 
TEST_BASE_OBJS_FILES=$(TEST_BASE_SRCS:.cpp=.o)
TEST_BASE_OBJS=$(subst $(TEST_BASE_DIR),$(TESTOBJ_DIR),$(TEST_BASE_OBJS_FILES))

TEST_SRCS=$(wildcard $(TEST_DIR)/*.cpp) 
TEST_OBJS_FILES=$(TEST_SRCS:.cpp=.o)
TEST_OBJS=$(subst $(TEST_DIR),$(TESTOBJ_DIR),$(TEST_OBJS_FILES))

PROD_SRCS=$(wildcard *.cpp)
PROD_OBJS_FILES=$(PROD_SRCS:.cpp=.o)
PROD_OBJS=$(patsubst %,$(TESTOBJ_DIR)/%,$(PROD_OBJS_FILES))

$(TESTBIN_DIR):
	@$(MKDIR) $(TESTBIN_DIR)

$(TESTOBJ_DIR):
	@$(MKDIR) $(TESTOBJ_DIR)

$(TESTOBJ_DIR)/%.o: %.cpp $(TESTOBJ_DIR)
	clang++ -std=c++11 -c $< -o $@ -I$(TEST_BASE_DIR) 

$(TESTOBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(TESTOBJ_DIR)
	clang++ -std=c++11 -c $< -o $@ -I$(TEST_DIR) -I$(TEST_BASE_DIR)

$(TESTOBJ_DIR)/%.o: $(TEST_BASE_DIR)/%.cpp $(TESTOBJ_DIR)
	clang++ -std=c++11 -c $< -o $@ -I$(TEST_BASE_DIR)

$(TESTBIN_DIR)/tests: $(TEST_BASE_OBJS) $(TEST_OBJS) $(PROD_OBJS) $(TESTBIN_DIR)
	clang++ -o $(TESTBIN_DIR)/tests $(TEST_OBJS) $(PROD_OBJS) $(TEST_BASE_OBJS)

build_tests: $(TESTBIN_DIR)/tests

run_tests: build_tests
	@$(TESTBIN_DIR)/tests

clean_tests:
	rm -rf $(TESTBIN_DIR)
	rm -rf $(TESTOBJ_DIR)

CC = gcc
CFLAGS = -Wall -Werror -Wextra
ARFLAGS = rcs

GCOV_FLAGS = --coverage
LCOV_FLAGS = --no-external
REMOVE_PATTERNS = "*/tetris_tests.c"

TEST_SRC = $(wildcard tests/*.c) $(wildcard tests/*/*.c)
TEST_BIN = tetris_tests

S21_LIB = tetris.a
OBJ_DIR = out
LIB_SRC = $(wildcard brick_game/tetris/*.c)
LIB_OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(LIB_SRC))

APP_SRC = tetris.c $(wildcard gui/cli/*.c)
APP_OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(APP_SRC))
APP = BrickGame

LIBS = -lm -lncurses
CHECK_LIBS = $(shell pkg-config --cflags --libs check)
UNAME = $(shell uname)

DOC_DIR = ./doc
DOC_INDEX_FILE = html/index.html

PACKAGE = tetris.tar.gz
INSTALL_DIR = ./game

CVG_NAME = coverage.out
CVG_DIR = coverage

.PHONY: all install uninstall clean dvi dist test gcov_report doc

all: $(S21_LIB) $(APP)

$(S21_LIB): $(LIB_OBJ)
	@$(AR) $(ARFLAGS) $@ $^
	@ranlib $@

$(APP): $(APP_OBJ) $(S21_LIB)
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(TEST_BIN): $(TEST_SRC) $(LIB_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) $(LIB_SRC) -o $@ $(CHECK_LIBS) $(LIBS)

install: $(APP)
	@mkdir -p $(INSTALL_DIR)
	@cp $(APP) $(INSTALL_DIR)/
	@$(RM) -f $(S21_LIB) $(LIB_OBJ) $(APP_OBJ) $(APP)
	@$(RM) -rf $(OBJ_DIR)

uninstall:
	@$(RM) -rf $(INSTALL_DIR)

test: $(TEST_BIN)
	@./$(TEST_BIN)

dvi:
	@mkdir -p $(DOC_DIR)
	@doxygen Doxyfile

doc:
	@open $(DOC_DIR)/$(DOC_INDEX_FILE)

dist: dvi $(APP) $(S21_LIB)
	@tar -czf $(PACKAGE) \
		brick_game \
		gui \
		inc \
		tests \
		Makefile \
		Doxyfile \
		doc \
		$(APP) \
		$(S21_LIB)
	@$(RM) -f $(S21_LIB) $(LIB_OBJ) $(APP_OBJ) $(APP)
	@$(RM) -rf $(OBJ_DIR) $(DOC_DIR)

gcov_report: CFLAGS += $(GCOV_FLAGS)
gcov_report: clean $(TEST_BIN)
	@./$(TEST_BIN)
	@lcov -d . -c -o $(CVG_NAME) $(LCOV_FLAGS) --rc lcov_branch_coverage=1
	@lcov --remove $(CVG_NAME) $(REMOVE_PATTERNS) -o $(CVG_NAME) --rc lcov_branch_coverage=1
	@genhtml $(CVG_NAME) -o $(CVG_DIR) --rc genhtml_branch_coverage=1

ifeq ($(UNAME), Linux)
	@xdg-open $(CVG_DIR)/index.html
endif
ifeq ($(UNAME), Darwin)
	@open $(CVG_DIR)/index.html
endif

clean:
	@$(RM) -f $(TEST_BIN) $(APP) $(S21_LIB) $(LIB_OBJ) $(APP_OBJ) *.gcno *.gcda $(CVG_NAME) $(PACKAGE)
	@$(RM) -rf $(CVG_DIR) $(OBJ_DIR) $(DOC_DIR) $(INSTALL_DIR)
	


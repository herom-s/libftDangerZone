# ============================================================================
# Configuration
# ============================================================================

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = -lbsd

# Directories
LIBFT_DIR = ../libft
TEST_DIR = tests
DEPS_DIR = deps
MUNIT_DIR = $(DEPS_DIR)/munit

# Source files
LIBFT_SOURCES = $(wildcard $(LIBFT_DIR)/*.c)
TEST_SOURCES = $(TEST_DIR)/test_main.c $(wildcard $(TEST_DIR)/test_suite_*.c) $(wildcard $(TEST_DIR)/ft_*/test_suite_*.c)

# Object files
LIBFT_OBJECTS = $(LIBFT_SOURCES:.c=.o)
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

# Target binaries
LIBFT_LIB = $(LIBFT_DIR)/libft.a
TEST_BINARY = libft_tests

# Include directories
INCLUDES = -I$(LIBFT_DIR) -I$(MUNIT_DIR)

# Test function names (for individual tests)
TEST_FUNCTIONS = isalpha \
				 isdigit \
				 isalnum \
				 isascii \
				 isprint \
				 strlen \
				 memset \
				 strchr \
				 strrchr \
				 bzero \
				 memcpy \
				 memmove \
				 strlcpy \
				 strlcat \
				 toupper \
				 tolower \
				 strncmp

# ============================================================================
# Phony targets
# ============================================================================

.PHONY: all clean fclean re test setup deps help $(TEST_FUNCTIONS)

# ============================================================================
# Main targets
# ============================================================================

all: $(LIBFT_LIB) $(TEST_BINARY)

# ============================================================================
# Setup and dependencies
# ============================================================================

# Setup dependencies (only run when needed)
$(MUNIT_DIR)/munit.c:
	@echo "Setting up dependencies..."
	@mkdir -p $(DEPS_DIR)
	@echo "Cloning munit..."
	@git clone https://github.com/nemequ/munit.git $(MUNIT_DIR)

# Munit header depends on munit source
$(MUNIT_DIR)/munit.h: $(MUNIT_DIR)/munit.c

# Legacy setup target for manual use
setup: $(MUNIT_DIR)/munit.c

deps: setup

# ============================================================================
# Build rules
# ============================================================================

# Build libft library
$(LIBFT_LIB): $(LIBFT_OBJECTS)
	@echo "Creating libft library..."
	ar rcs $@ $^

# Build test executable
$(TEST_BINARY): $(TEST_OBJECTS) $(LIBFT_LIB) $(MUNIT_DIR)/munit.o
	@echo "Linking test binary..."
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# ============================================================================
# Compilation rules
# ============================================================================

# Compile libft source files
$(LIBFT_DIR)/%.o: $(LIBFT_DIR)/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

# Compile test source files
$(TEST_DIR)/%.o: $(TEST_DIR)/%.c $(MUNIT_DIR)/munit.h
	@echo "Compiling test $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile test source files in subdirectories
$(TEST_DIR)/*/%.o: $(TEST_DIR)/*/%.c $(MUNIT_DIR)/munit.h
	@echo "Compiling test $<..."
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile munit
$(MUNIT_DIR)/munit.o: $(MUNIT_DIR)/munit.c
	@echo "Compiling munit..."
	$(CC) $(CFLAGS) -c $< -o $@

# ============================================================================
# Test execution
# ============================================================================

# Run all tests
test: $(TEST_BINARY)
	@echo "Running tests..."
	./$(TEST_BINARY)

# Function to create individual test rules
define create_test_rule
$(1): $(LIBFT_LIB) $(MUNIT_DIR)/munit.o tests/ft_$(1)/test_suite_ft_$(1).o tests/ft_$(1)/main_$(1).o
	@echo "Building and running ft_$(1) tests..."
	$(CC) $(CFLAGS) tests/ft_$(1)/main_$(1).o tests/ft_$(1)/test_suite_ft_$(1).o $(LIBFT_LIB) $(MUNIT_DIR)/munit.o -o test_$(1) $(LDFLAGS)
	@echo "Running ft_$(1) tests..."
	./test_$(1)
	@rm -f test_$(1)
endef

# Generate individual test rules
$(foreach func,$(TEST_FUNCTIONS),$(eval $(call create_test_rule,$(func))))

# ============================================================================
# Cleanup
# ============================================================================
# Clean object files
clean:
	@echo "Cleaning object files..."
	rm -f $(LIBFT_OBJECTS)
	rm -f $(TEST_OBJECTS)
	rm -f $(MUNIT_DIR)/munit.o
	rm -f test_*

# Full clean including binaries and dependencies
fclean: clean
	@echo "Full clean..."
	rm -f $(LIBFT_LIB)
	rm -f $(TEST_BINARY)
	rm -rf $(DEPS_DIR)

# Rebuild everything
re: fclean all

# ============================================================================
# Help
# ============================================================================

help:
	@echo "Available targets:"
	@echo "  all        - Build everything (default)"
	@echo "  setup      - Setup dependencies"
	@echo "  test       - Run all unit tests"
	@echo ""
	@echo "Individual tests:"
	@$(foreach func,$(TEST_FUNCTIONS),echo "  $(func)      - Run ft_$(func) tests only";)
	@echo ""
	@echo "Cleanup:"
	@echo "  clean      - Remove object files"
	@echo "  fclean     - Remove all generated files"
	@echo "  re         - Rebuild everything"
	@echo "  help       - Show this help message"

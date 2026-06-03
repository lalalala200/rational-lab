CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -fPIC -g
LDFLAGS = -shared

LIB_NAME = librational.so
TARGET = build/$(LIB_NAME)
APP = build/test_app
TEST_C = build/test_c

all: $(TARGET) $(APP)

$(TARGET): src/rational.c
	mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) src/rational.c

$(APP): src/main.c $(TARGET)
	mkdir -p build
	$(CC) $(CFLAGS) -o $(APP) src/main.c -Lbuild -lrational -Wl,-rpath,build

$(TEST_C): tests/test_rational.c $(TARGET)
	mkdir -p build
	$(CC) $(CFLAGS) -o $(TEST_C) tests/test_rational.c -Lbuild -lrational -Wl,-rpath,build

run: $(APP)
	./$(APP)

test-c: $(TEST_C)
	./$(TEST_C)

test-py: $(TARGET)
	python3 tests/test_rational.py

docs-html:
	mkdir -p docs
	doxygen Doxyfile

analyze:
	cppcheck --enable=all --suppress=missingIncludeSystem include/ src/ tests/

sanitize: $(TEST_C)
	$(CC) $(CFLAGS) -fsanitize=address,undefined -o build/test_sanitize tests/test_rational.c -Lbuild -lrational -Wl,-rpath,build
	./build/test_sanitize

clean:
	rm -rf build/ docs/ html/ reports/

.PHONY: all run test-c test-py docs-html analyze sanitize clean

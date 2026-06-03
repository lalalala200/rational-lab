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

test-c: $(TEST_C)
	./$(TEST_C)

run: $(APP)
	./$(APP)

test-c: $(TEST_C)
	./$(TEST_C)

test-py: $(TARGET)
	python3 tests/test_rational.py

clean:
	rm -rf build/

.PHONY: all run test-c test-py clean

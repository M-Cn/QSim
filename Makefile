CC = gcc
CFLAGS = -Wall -lm
CFLAGS_DEBUG = -Wall -lm -g -D _DEBUG
SOURCE_FILES = source/QDirective.c source/QDirectiveHandler.c source/QSim.c source/Math/Complex.c source/Math/ComplexVector.c source/Math/ComplexMatrix.c

all_release: qsim_release autotest_release
all_debug: qsim_debug autotest_debug

qsim_release:
	mkdir -p bin/
	$(CC) $(SOURCE_FILES) source/main.c -o bin/qsim $(CFLAGS)

autotest_release:
	mkdir -p bin/
	$(CC) $(SOURCE_FILES) source/AutoTest.c -o bin/autotest $(CFLAGS)

qsim_debug:
	mkdir -p bin/
	$(CC) $(SOURCE_FILES) source/main.c -o bin/qsim $(CFLAGS_DEBUG)

autotest_debug:
	mkdir -p bin/
	$(CC) $(SOURCE_FILES) source/AutoTest.c -o bin/autotest $(CFLAGS_DEBUG)

.PHONY: clean

clean:
	rm -f bin/qsim bin/autotest
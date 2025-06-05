CC = gcc
CFLAGS = -Wall -lm -g
SOURCE_FILES = source/QDirective.c source/QDirectiveHandler.c source/QSim.c source/Math/Complex.c source/Math/ComplexVector.c source/Math/ComplexMatrix.c

all: qsim autotest

qsim:
	$(CC) $(SOURCE_FILES) source/main.c -o bin/qsim $(CFLAGS)

autotest:
	$(CC) $(SOURCE_FILES) source/AutoTest.c -o bin/autotest $(CFLAGS)

.PHONY: clean

clean:
	rm -f bin/qsim bin/autotest
CC = gcc
CFLAGS = -Wall -lm -g

all: qsim autotest

qsim:
	$(CC) source/Properties/Property.c source/Properties/Properties.c source/Math/Complex.c source/Math/ComplexVector.c source/Math/ComplexMatrix.c source/main.c -o bin/qsim $(CFLAGS)

autotest:
	$(CC) source/Properties/Property.c source/Properties/Properties.c source/Math/Complex.c source/Math/ComplexVector.c source/Math/ComplexMatrix.c source/AutoTest.c -o bin/autotest $(CFLAGS)

.PHONY: clean

clean:
	rm -f bin/qsim bin/autotest
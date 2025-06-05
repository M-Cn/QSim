# QSim
Quantum bit gate simulator written in ANSI C.

## Project structure
`esempi-input`: Input files used when running `autotest`.

`input`: Input files used when running `qsim`.


`include/Math/Complex.h`: Math header for handling complex numbers.

`include/Math/ComplexMatrix.h`: Math header for handling complex matrices.

`include/Math/ComplexVector.h`: Math header for handling complex vectors.

`include/Debug.h`: Helper header with debugging and output related defines.

`include/QDirective.h`: Header containing the definition of the QDirective object. QDirective is built from the input .txt files and used to define the simulator's parameters and behaviour.

`include/QDirectiveHandler.h`: Header containing the handler functions for each QDirective object. Basically, makes QDirective talk with QSim.

`include/QSim.h`: Header containing the simulator's core definition and parameters list.

`include/QuantumCircuitDef.h`: Header containing the definition of a quantum circuit object.

`include/QuantumGate.h`: Header containing the definition of a quantum gate object.

`include/QuantumState.h`: Header containing the definition of a quantum state object.

`include/utils.h`: Header containing general utility functions and defines.


The `source` directory respects the same structure as the `include` directory. Each file contains the implementations of what's defined in the corresponding header.

The two extra files `main.c` and `autotest.c` contain the entry point of `qsim` and `autotest`, respecitvely.

## Building
Run either `make all_release` or `make all_debug` in the terminal, depending on the configuration you wish to use.

## Running
If you wish to run unit tests, simply run `bin/autotest`.
If you wish to run the main program, run `bin/qsim`. A menu will pop up, allowing different actions from the user:
* Inputting `1` will run the simulation, printing the circuit's initial and final states when done.
* Inputting `c` will clear the console.
* Inputting `q` will quit the program.

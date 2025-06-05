# QSim

**QSim** is a quantum bit circuit simulator written in ANSI C.

---

## Project Structure

### Input Files

- `esempi-input/` — Sample input files used by `autotest`.
- `input/` — Input files used when running `qsim`.

### Header Files (`include/`)

#### Math Utilities

- `Math/Complex.h` — Complex number operations.
- `Math/ComplexMatrix.h` — Complex matrix operations.
- `Math/ComplexVector.h` — Complex vector operations.

#### Core Simulation

- `QDirective.h` — Defines the `QDirective` object, which encapsulates simulator parameters from `.txt` input files.
- `QDirectiveHandler.h` — Functions that interpret and apply `QDirective` settings to the simulator.
- `QSim.h` — Main definitions and configuration for the simulator.
- `QuantumCircuitDef.h` — Defines the structure of a quantum circuit.
- `QuantumGate.h` — Describes individual quantum gates.
- `QuantumState.h` — Represents a quantum state.

#### Utilities and Debugging

- `Debug.h` — Macros and tools for debugging and logging.
- `utils.h` — General-purpose utility functions and constants.

### Source Files (`source/`)

Each `.c` file mirrors its corresponding `.h` file in the `include/` directory and contains the implementation.

### Entrypoints

- `main.c` — Entry point for the main `qsim` simulator.
- `autotest.c` — Entry point for the `autotest` test runner.

### Other Files

- `Makefile` — Contains build targets and settings for different build configurations.

---

## Building

To compile the project, run one of the following commands:

```bash
make all_release   # Optimized build
make all_debug     # Debug build with additional outputs and symbols
```

## Running

### Running Tests

To execute the automated test suite, run:

```bash
bin/autotest
```

### Running the simulator

To execute the main simulator, run:

```bash
bin/qsim
```

You will be presented with an interactive menu with the following actions:

```
1 — Run the simulation. This will display the circuit's initial and final quantum states.

c — Clear the console screen.

q — Quit the program.
```
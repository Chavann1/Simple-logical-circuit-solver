# Logic Circuit Simulator in C++

A command-line program written in C++ that simulates digital logic circuits based on text input. The program evaluates logic gate operations for multiple input combinations and generates corresponding output signals.

---

## Features

* Supports common logic gates: AND, NAND, OR, NOR, XOR, XNOR, NOT
* File-based circuit definition and input handling
* Batch processing of multiple input combinations
* Input validation and error handling
* Outputs results to a file in structured format

---

## Technologies

* C++
* Standard Library (iostream, fstream, vector, map, string)

---

## How It Works

* The circuit is defined in a text file using gate operations and pin connections
* Input combinations are provided in a separate file
* The program maps pins to values and processes logic gates sequentially
* For each input combination, the circuit is evaluated and results are written to an output file

---

## Usage

### Command-line arguments

```
-u <circuit_file>   input file with circuit definition
-i <input_file>     input file with input combinations
-o <output_file>    output file
```

### Example

```
program.exe -u circuit.txt -i inputs.txt -o output.txt
```

---

## Input Format

### Circuit file

```
IN: 1 2 3
OUT: 5
OR 1 2 4
AND 3 4 5
```

### Input combinations

```
1:0 2:1 3:1
1:0 2:0 3:0
```

---

## Output Format

```
IN: 1:0 2:1 3:1 OUT: 5:1
IN: 1:0 2:0 3:0 OUT: 5:0
```

---

## Project Structure

* `main.cpp` — program entry point and execution flow
* `logfunc.h / .cpp` — logic gate implementation and utilities

---

## Notes

* The program assumes correct ordering of logic gates (dependencies must be resolved in sequence)
* Input files must use `.txt` format
* Designed as a command-line tool for learning and experimentation with digital logic

---

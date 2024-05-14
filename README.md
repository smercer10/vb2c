# vb2c

vb2c compiles a unique dialect of BASIC, Very BASIC, to C.

[![MIT License](https://img.shields.io/badge/License-MIT-green.svg)](https://github.com/smercer10/vb2c/blob/main/LICENSE)
[![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/smercer10/vb2c/ci.yml?label=CI)](https://github.com/smercer10/vb2c/actions/workflows/ci.yml)

## Current Language Features

- Numerical variables
- Floating-point arithmetic
- Comparison operators
- If statements
- While loops
- Goto and labels
- User input
- Console output
- Comments
- Conditional includes
- Basic compile-time error checking

## Usage

```bash
vb2c -s <path to source file> [-o <path to output file>]
```

If unspecified, the default output file is `out.c` in the current working directory.

The `vbas` file extension is recommended for Very BASIC source code, but it is by no means required.

## Example

### **Very BASIC** Source Code

```bas
# Compute the mean of a specified number of test scores

LET a = 0
WHILE a < 1 REPEAT
    PRINT "Enter number of scores: "
    INPUT a
ENDWHILE

LET b = 0
LET s =  0
PRINT "Enter one value at a time: "
WHILE b < a REPEAT
    INPUT c
    LET s = s + c
    LET b = b + 1
ENDWHILE

PRINT "Average: "
PRINT s / a
```

### Generated **C** Code (After Autoformatting)

```c
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    float a;
    float b;
    float s;
    float c;
    a = 0;
    while (a < 1)
    {
        printf("Enter number of scores: \n");
        if (scanf("%f", &a) == EOF)
        {
            printf("Error: Invalid input\n");
            exit(EXIT_FAILURE);
        }
    }
    b = 0;
    s = 0;
    printf("Enter one value at a time: \n");
    while (b < a)
    {
        if (scanf("%f", &c) == EOF)
        {
            printf("Error: Invalid input\n");
            exit(EXIT_FAILURE);
        }
        s = s + c;
        b = b + 1;
    }
    printf("Average: \n");
    printf("%.2f\n", s / a);
    return EXIT_SUCCESS;
}
```

## Grammar Specification

The current Very BASIC grammar is defined by the following EBNF:

```ebnf
program ::= {statement}
statement ::= "PRINT" (expression | string) newline
    | "IF" comparison "THEN" newline {statement} "ENDIF" newline
    | "WHILE" comparison "REPEAT" newline {statement} "ENDWHILE" newline
    | "LABEL" ident newline
    | "GOTO" ident newline
    | "LET" ident "=" expression newline
    | "INPUT" ident newline
comparison ::= expression (("==" | "!=" | ">" | ">=" | "<" | "<=") expression)+
expression ::= term {( "-" | "+" ) term}
term ::= unary {( "/" | "*" ) unary}
unary ::= ["+" | "-"] primary
primary ::= number | ident
newline ::= "\n"+
```

## Build Locally

### Prerequisites

- C++20 compiler (tested with GCC and Clang)
- CMake 3.14+
- Clang-Format (optional)
- Clang-Tidy (optional)

### Steps

1. Clone the project:

```bash
  git clone https://github.com/smercer10/vb2c.git
```

2. Navigate to the project directory:

```bash
  cd vb2c
```

3. Generate the build files:

```bash
  cmake -S . -B build
```

4. Build the project:

```bash
  cmake --build build
```

## Running Tests

The project utilises the GoogleTest framework with CTest.

To execute the testcases, run the following command from the project root:

```bash
  cmake --build build --target test
```

## Contributing

Contributions are always welcome!

See [open issues](https://github.com/smercer10/vb2c/issues) for ways to get started.

## Acknowledgements

The compiler design is based on the excellent [blog series](https://austinhenley.com/blog/teenytinycompiler1.html) by Austin Henley.

# BigInt Multi-Base Arithmetic and Polish Notation Calculator
This project extends the template BigInt<size_t Base> to handle arithmetic operations between large integers in different numerical bases. A new version introduces a more flexible and polymorphic design to support multi-base operations.

## Overview

A base class `Number` is defined, from which all classes derived from the `BigInt<size_t Base>` template inherit. This allows operations between numbers in different bases to be decided at runtime through virtual methods.

## Key Features

### 1. Polymorphic Arithmetic Operations

`Number` defines several virtual arithmetic methods:
> - virtual Number* add(const Number*) const = 0;
> - virtual Number* subtract(const Number*) const = 0;
> - virtual Number* multiply(const Number*) const = 0;
> - virtual Number* divide(const Number*) const = 0;
> - virtual Number* module(const Number*) const = 0;
> - virtual Number* pow(const Number*) const = 0;

### 2. Base Conversion Operations

Each derived class can convert between different numerical bases through explicit conversion operators:
> - virtual operator BigInt<2>() const = 0;
> - virtual operator BigInt<8>() const = 0;
> - virtual operator BigInt<10>() const = 0;
> - virtual operator BigInt<16>() const = 0;

### 3. Stream I/O Support

The class provides methods for reading and writing data, including overloading stream operators:
> - virtual std::ostream& write(std::ostream&) const = 0;
> - virtual std::istream& read(std::istream&) = 0;
> - friend std::ostream& operator<<(std::ostream&, const Number&);
> - friend std::istream& operator>>(std::istream&, Number&);

### 4. Dynamic Object Creation

A static method allows creating `Number` objects dynamically, given a base and a string representation:
> - static Number* create(size_t base, const std::string& s);

### 5. Error Handling via Exceptions

A family of exceptions derived from `BigIntException` (which inherits from `std::exception`) is used to handle errors:
- `BigIntBadDigit`: Invalid digit in input.
- `BigIntDivisionByZero`: Division by zero.
- `BigIntBaseNotImplemented`: Base not supported.

## Reverse Polish Notation (RPN) Calculator

A program is developed to evaluate expressions in Reverse Polish Notation (RPN) using `Number` operands. Operands and their values are stored in a `Board` as pairs of labels and pointers to dynamically allocated `Number` objects.

#### Input Format

The input file consists of lines in the following format:
- Operand Definition: `label = base, ASCII_representation`
- Expression Evaluation: `label ? operand1 operand2 operator`

#### Example

```text
N1 = 2, 000100110110
N2 = 16, AB64
E1 ? N2 N1 +
```

The calculator reads expressions, retrieves the corresponding objects from the `Board`, and performs the necessary arithmetic operations. The result is then stored back in the `Board` with its corresponding label.

## Exception Handling in Calculator

If an exception occurs during execution (e.g., invalid input or division by zero), the program stores a `Number` object initialized to zero in the `Board` for the current label and continues to the next step.

## Implementation Notes

- Assignment Operator: If needed, the class `Number` can overload the assignment operator to allow type conversion before copying attributes:
  > - virtual Number& operator=(const Number&) = 0;
- Abstract Class Instantiation: `Number` is an abstract class, so objects must be instantiated through pointers or references to derived classes.
- Type-Specific Methods: Due to template limitations, virtual methods cannot be declared within a template, so each base conversion method must be declared separately.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

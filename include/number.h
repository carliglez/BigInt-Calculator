/**
 * @brief Fichero de cabecera de la clase Number. Clase abstracta para representar números en
 * distintas bases en tiempo de ejecución.
 *
 */

#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <string>

// forward declaration de las clases template BigInt y BigInt<2>
template <size_t Base> class BigInt;
template<> class BigInt<2>;

class Number {
 public:
  // métodos virtuales para las operaciones aritméticas
  virtual Number* add(const Number*) const = 0;
  virtual Number* subtract(const Number*) const = 0;
  virtual Number* multiply(const Number*) const = 0;
  virtual Number* divide(const Number*) const = 0;
  virtual Number* module(const Number*) const = 0;
  virtual Number* pow(const Number*) const = 0;
  virtual Number* addEqual(const Number*) const = 0;

  // asignación (copia)
  virtual Number& operator=(const Number&) = 0;

  // cambio de tipo (base)
  virtual operator BigInt<2>() const = 0;
  virtual operator BigInt<8>() const = 0;
  virtual operator BigInt<10>() const = 0;
  virtual operator BigInt<16>() const = 0;

  // entrada / salida (E/S)
  virtual std::ostream& write(std::ostream&) const = 0;
  virtual std::istream& read(std::istream&) = 0;
  friend std::ostream& operator<<(std::ostream&, const Number&);
  friend std::istream& operator>>(std::istream&, Number&);
  static Number* create(size_t base, const std::string& );

  // destructor
  virtual ~Number(){}
};

#endif  // NUMBER_H
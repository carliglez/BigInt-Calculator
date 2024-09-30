/**
 * @brief Fichero de cabecera de la clase BigInt. Clase template para representar números en
 * distintas bases (binaria, octal, decimal y hexadecimal). Se ha añadido una clase template
 * especializada para números en base 2 (binaria).
 *
 */

#ifndef BIGINT_H
#define BIGINT_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cmath>

#include "number.h"
#include "bigintexception.h"

template <size_t Base>
class BigInt : public Number {
 public:
  // constructor
  BigInt(long n = 0);
  BigInt(std::string &);
  BigInt(const char *);
  BigInt(const BigInt<Base> &);
  BigInt(const std::vector<char> &,const int & );

  // cambio de tipo
  operator BigInt<2>() const override;
  operator BigInt<8>() const override;
  operator BigInt<10>() const override;
  operator BigInt<16>() const override;

  // constructor virtual de Number con sobrecarga de operator=
  Number& operator=(const Number&) override;

  // asignación (copia)
  BigInt<Base> &operator=(const BigInt<Base> &);

  // entrada / salida (E/S)
  template <size_t Base_t>
  friend std::ostream &operator<<(std::ostream &, const BigInt<Base_t> &);
  template <size_t Base_t>
  friend std::istream& operator>>(std::istream&, BigInt<Base_t>&);

  // getters y setters
  BigInt<Base> setSign(int);
  BigInt<Base> setDigits(std::vector<char>);
  int getSign() const;
  std::vector<char> getDigits() const;

  // método to_string (to_s)
  std::string to_string() const;

  // métodos de acceso
  char operator[](size_t) const;
  size_t size() const;

  // métodos de modificación y comprobación
  BigInt<Base> FillZeros(unsigned) const ;
  bool IsZero() const;
  BigInt<Base> Abs() const;
  BigInt<Base> PushBack(char);

  // operadores de comparación
  template <size_t Base_t>
  friend bool operator==(const BigInt<Base> &, const BigInt<Base> &);
  bool operator!=(const BigInt<Base> &) const;
  template <size_t Base_t>
  friend bool operator>(const BigInt<Base> &, const BigInt<Base> &);
  bool operator>=(const BigInt<Base> &) const;
  template <size_t Base_t>
  friend bool operator<(const BigInt<Base> &, const BigInt<Base> &);
  bool operator<=(const BigInt<Base> &) const;

  // incremento y decremento
  BigInt<Base> &operator++();    // pre-incremento
  BigInt<Base> operator++(int);  // post-incremento
  BigInt<Base> &operator--();    // pre-decremento
  BigInt<Base> operator--(int);  // post-decremento

  // operadores aritméticos
  template <size_t Base_t>
  friend BigInt<Base_t> operator+(const BigInt<Base_t> &, const BigInt<Base_t> &);
  BigInt<Base> operator-(const BigInt<Base> &) const;
  BigInt<Base> operator-() const;
  BigInt<Base> operator*(const BigInt<Base> &) const;
  template <size_t Base_t>
  friend BigInt<Base> operator/(const BigInt<Base> &, const BigInt<Base> &);
  BigInt<Base> operator%(const BigInt<Base> &) const;
  template <size_t Base_t>
  friend BigInt<Base> pow(const BigInt<Base> &, const BigInt<Base> &);
  BigInt<Base> operator^(const BigInt<Base> &) const;

  // extra
  BigInt<Base> operator!() const;
  BigInt<Base> operator+=(const BigInt<Base> &) const;

  // métodos implementados por la clase BigInt declarados en la clase abstracta Number
  Number* add(const Number*) const override;
  Number* subtract(const Number*) const override;
  Number* multiply(const Number*) const override;
  Number* divide(const Number*) const override;
  Number* module(const Number*) const override;
  Number* pow(const Number*) const override;
  Number *addEqual(const Number *) const override;

  std::ostream& write(std::ostream&) const override;
  std::istream& read(std::istream&)  override;

  // destructor
  ~BigInt() override{}

 private:
  std::vector<char> digits_;  // dígitos que conforman el número
  int sign_;  // positivo: signo = 1 / negativo: signo = -1
};


/**
 * @brief Clase template para representar números BigInt en base 2 (binaria). Se trata de la
 * especialización del template de números BigInt<Base>, pero para BigInt<2>.
 *
 * @author Carlos González Mendoza - alu0101025407@ull.edu.es
 */
template <>
class BigInt<2> : public Number {
 public:
  // constructor
  BigInt(long number_x = 0);
  BigInt(const BigInt<2> &other);
  BigInt(std::vector<bool> digits);
  BigInt(const std::vector<char> &, const int &);  // necesario para BigInt<2>::operator BigInt<Base>() const
  BigInt(std::string number_x);

  // asignación (copia)
  BigInt operator=(const BigInt<2> &other);

  // cambio de tipo
  template <size_t base>
  BigInt<base> ConvertBaseT();
  operator BigInt<2>() const override;
  operator BigInt<8>() const override;
  operator BigInt<10>() const override;
  operator BigInt<16>() const override;

  // constructor virtual de Number con sobrecarga de operator=
  Number& operator=(const Number&) override;

  // getters y setters
  std::vector<bool> getDigits() const;
  BigInt<2> setDigits(std::vector<bool> digits);

  // métodos de acceso
  bool operator[](size_t) const;
  size_t size() const;
  void push_back(bool digit);

  // métodos de modificación y comprobación
  bool IsZero() const;
  BigInt<2> Abs() const;

  // operadores de comparación
  friend bool operator==(const BigInt<2> &, const BigInt<2> &);
  bool operator!=(const BigInt<2> &other) const;
  friend bool operator>(const BigInt<2> &, const BigInt<2> &);
  bool operator>=(const BigInt<2> &other) const;
  friend bool operator<(const BigInt<2> &, const BigInt<2> &);
  bool operator<=(const BigInt<2> &other) const;

  // incremento y decremento
  BigInt<2> &operator++();    // pre-incremento
  BigInt<2> operator++(int);  // post-incremento
  BigInt<2> &operator--();    // pre-decremento
  BigInt<2> operator--(int);  // post-decremento

  // operadores aritméticos
  friend BigInt<2> operator+(const BigInt<2> &first, const BigInt<2> &other);
  BigInt<2> suma_overflow(const BigInt<2> &first, const BigInt<2> &other) const;
  BigInt<2> operator-() const;
  BigInt<2> operator-(const BigInt<2> &other) const;
  BigInt<2> operator*(const BigInt<2> &other) const;
  friend BigInt<2> operator/(const BigInt<2> &first, const BigInt<2> &other);
  BigInt<2> operator%(const BigInt<2> &other) const;
  friend BigInt<2> pow(const BigInt<2> &first, const BigInt<2> &other);
  BigInt<2> operator^(const BigInt<2> &other) const;

  // operadores de desplazamiento
  void operator<<(size_t n);
  void operator>>(size_t n);

  // operadores para controlar operaciones
  BigInt<2> FillSign(size_t n) const;
  BigInt<2> ComplementoA2() const;

  // entrada / salida (E/S)
  friend std::ostream &operator<<(std::ostream &os, const BigInt<2> &number_x);

  // método to_string (to_s)
  std::string to_string() const;

  // extra
  BigInt<2> factorial() const;
  BigInt<2> operator!() const;
  BigInt<2> operator+=(const BigInt<2> &) const;

  // methods overriden from the number class
  Number *add(const Number *) const override;
  Number *subtract(const Number *) const override;
  Number *multiply(const Number *) const override;
  Number *divide(const Number *) const override;
  Number *module(const Number *) const override;
  Number *pow(const Number *) const override;
  Number *addEqual(const Number *) const override;

  std::ostream &write(std::ostream &) const override;
  std::istream &read(std::istream &)  override;

  // destructor
  ~BigInt() override{}

 private:
  void operator<<(BigInt<2> &other);
  void operator>>(BigInt<2> &other);

  std::vector<bool> digits;  // dígitos que conforman el número
};

#include "../src/bigint.cc"  // se codifica en otro fichero, aunque podría hacerse en este

#endif  // BIGINT_H
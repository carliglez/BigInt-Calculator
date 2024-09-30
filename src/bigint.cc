/**
 * @brief Código fuente de la clase BigInt declarada en el fichero bigint.h
 *
 */

#ifndef BIGINT_CC
#define BIGINT_CC

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

#include "..\include\bigint.h"

/**
 * @brief Constructor de BigInt<Base>::BigInt dado un long
 *
 * @param Base
 * @param n
 */
template <size_t Base>
BigInt<Base>::BigInt(long n) {
  if (n == 0) {
    sign_ = 1;
    digits_.push_back(0);
    return;
  }
  if (n < 0) {
    sign_ = -1;
    n = -n;
  } else {
    sign_ = 1;
  }
  while (n > 0) {
    digits_.push_back(n % Base);
    n /= Base;
  }
}

/**
 * @brief Constructor de BigInt<Base>::BigInt dado un string
 *
 * @param Base
 * @param number_str
 */
template <size_t Base>
BigInt<Base>::BigInt(std::string &number_str) {
  if (number_str.empty()) {  // si es vacío (empty)
    sign_ = 1;
    digits_.push_back(0);
    return;
  }
  std::string number_big = number_str;
  digits_.clear();
  if (number_big[0] == '-') {
    sign_ = -1;
    number_big.erase(0, 1);
  } else {
    sign_ = 1;
  }
  for (int i = number_big.size() - 1; i >= 0; i--) {
    if (isdigit(number_big[i])) {
      if (static_cast<size_t>(number_big[i] - '0') >= Base) {  // si es mayor que la base que representa
        std::string message =
            "Número mayor que la Base: " + std::to_string(Base) + " con el número " + number_big + " en el dígito " + number_big[i];
        throw BigIntBaseNotImplemented(message);
      }
      digits_.push_back(number_big[i] - '0');
    } else if (number_big[i] >= 'A' && number_big[i] <= 'F' && Base == 16) {
      digits_.push_back(number_big[i] - 'A' + 10);
    } else {
      std::string message =
          "Bad digit Base: " + std::to_string(Base) + " con el numero " + number_big + " en el digito " + number_big[i];
      throw BigIntBadDigit(message);
    }
  }
}

/**
 * @brief Constructor de BigInt<Base>::BigInt dado un const char *
 *
 * @param Base
 * @param number_ptr
 */
template <size_t Base>
BigInt<Base>::BigInt(const char *number_ptr) {
  size_t size_number = std::char_traits<char>::length(number_ptr);
  // Si es vacio
  if (size_number == 0) {
    sign_ = 1;
    digits_.push_back(0);
    return;
  }
  digits_.clear();
  if (number_ptr[0] == '-') {
    sign_ = -1;
    number_ptr++;
    size_number--;
  } else {
    sign_ = 1;
  }
  for (int i = size_number - 1; i >= 0; --i) {
    if (isdigit(number_ptr[i])) {
      digits_.push_back(number_ptr[i] - '0');
    } else if (number_ptr[i] >= 'A' && number_ptr[i] <= 'F') {
      digits_.push_back(number_ptr[i] - 'A' + 10);
    } else {
      std::cout << (int)number_ptr[i] << std::endl;
      throw std::invalid_argument("Constructor(char): Invalid character");
    }
  }
}

/**
 * @brief Constructor de BigInt<Base>::BigInt dado un vector de char y un valor entero
 *
 * @param Base
 * @param digits_aux
 * @param sign_aux
 */
template <size_t Base>
BigInt<Base>::BigInt(const std::vector<char> &digits_aux, const int &sign_aux) {
  char max_digit = static_cast<char>(Base);
  for (size_t i = 0; i < digits_aux.size(); i++) {
    if (digits_aux[i] >= max_digit) {
      throw std::invalid_argument("Constructor(vector): Invalid digit");
    }
  }
  digits_ = digits_aux;
  sign_ = sign_aux;
}

/**
 * @brief Constructor de BigInt<Base>::BigInt desde un BigInt
 *
 * @param Base
 * @param number_big
 */
template <size_t Base>
BigInt<Base>::BigInt(const BigInt<Base> &number_big) {
  sign_ = number_big.sign_;
  digits_ = number_big.digits_;
}

/**
 * @brief Sobrecarga del operator= para copiar un BigInt
 *
 * @tparam Base
 * @param number_big
 * @return BigInt<Base>&
 */
template <size_t Base>
BigInt<Base> &BigInt<Base>::operator=(const BigInt<Base> &number_big) {
  sign_ = number_big.sign_;
  digits_ = number_big.digits_;
  return *this;
}
/**
 * @brief Setter del signo del objeto
 *
 * @tparam Base
 * @param sign_aux
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::setSign(int sign_aux) {
  sign_ = sign_aux;
  return *this;
}

/**
 * @brief Setter de los dígitos del objeto
 *
 * @param Base
 * @param digits_aux
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::setDigits(std::vector<char> digits_aux) {
  digits_ = digits_aux;
  return *this;
}

/**
 * @brief Getter de los dígitos del objeto
 *
 * @param Base
 * @return std::vector<char>
 */
template <size_t Base>
std::vector<char> BigInt<Base>::getDigits() const {
  return digits_;
}

/**
 * @brief Getter del signo del objeto
 *
 * @param Base
 * @return int
 */
template <size_t Base>
int BigInt<Base>::getSign() const {
  return sign_;
}

/**
 * @brief Getter del tamaño del objeto
 *
 * @tparam Base
 * @return size_t
 */
template <size_t Base>
size_t BigInt<Base>::size() const {
  return digits_.size();
}

/**
 * @brief Método para acceder a los dígitos del número. Primero accede a la posición en caso de que sea válida
 * y retorna el valor que contenga. Si la posición es inválida lanza una out_of_range exception
 * 
 * @tparam Base
 * @param position
 * @return char
 */
template <size_t Base>
char BigInt<Base>::operator[](size_t position) const {
  if (position < 0 || position >= digits_.size()) {
    std::cout << "position: " << position << " Size " << digits_.size()
              << std::endl;
    throw std::out_of_range("operator[]: Invalid position");
  }
  return digits_[position];
}

/**
 * @brief Comprueba que 2 objetos BigInt sean equivalentes
 *
 * @tparam Base_t
 * @param number_x
 * @param number_y
 * @return true
 * @return false
 */
template <size_t Base_t>
bool operator==(const BigInt<Base_t> &number_x, const BigInt<Base_t> &number_y) {
  BigInt<Base_t> number_x_aux = number_x;
  BigInt<Base_t> number_y_aux = number_y;
  if (number_x_aux.IsZero() && number_y_aux.IsZero()) {
    return true;
  }
  if (number_x.getSign() != number_y.getSign()) {
    return false;
  }
  if (number_x.getDigits().size() != number_y.getDigits().size()) {
    // se completa con ceros
    size_t size_difference =
        std::abs(static_cast<int>(number_x.getDigits().size()) - static_cast<int>(number_y.getDigits().size()));
    if (number_x.getDigits().size() > number_y.getDigits().size()) {
      number_y_aux = number_y_aux.FillZeros(size_difference);
    } else if (number_x.getDigits().size() < number_y.getDigits().size()) {
      number_x_aux = number_x_aux.FillZeros(size_difference);
    }
  }

  for (size_t i = 0; i < number_x_aux.size(); i++) {
    if (number_x_aux[i] != number_y_aux[i]) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Comprueba que 2 objetos BigInt no sea equivalentes
 *
 * @tparam Base
 * @param number_y
 * @return true
 * @return false
 */
template <size_t Base>
bool BigInt<Base>::operator!=(const BigInt<Base> &number_y) const {
  return !(*this == number_y);
}

/**
 * @brief Comprueba que un objeto BigInt sea mayor que otro
 *
 * @tparam Base_t
 * @param number_x
 * @param number_y
 * @return true
 * @return false
 */
template <size_t Base_t>
bool operator>(const BigInt<Base_t> &number_x, const BigInt<Base_t> &number_y) {
  if (number_x.getSign() > number_y.getSign()) {
    return true;
  } else if (number_x.getSign() < number_y.getSign()) {
    return false;
  }
  size_t number_digit_different =
      abs(number_x.getDigits().size() - number_y.getDigits().size());
  BigInt<Base_t> number_y_aux;
  BigInt<Base_t> number_x_aux;
  if (number_x.getDigits().size() > number_y.getDigits().size()) {
    number_y_aux = number_y.FillZeros(number_digit_different);
    number_x_aux = number_x;
  } else if (number_x.getDigits().size() < number_y.getDigits().size()) {
    number_x_aux = number_x.FillZeros(number_digit_different);
    number_y_aux = number_y;
  } else {
    number_x_aux = number_x;
    number_y_aux = number_y;
  }

  for (int i = number_x_aux.getDigits().size() - 1; i >= 0; i--) {
    if (number_x_aux.getDigits()[i] > number_y_aux.getDigits()[i]) {
      return number_x_aux.getSign() == 1 ? true : false;
    } else if (number_x_aux.getDigits()[i] < number_y_aux.getDigits()[i]) {
      return number_x_aux.getSign() == 1 ? false : true;
    }
  }
  return false;
}

/**
 * @brief Comprueba que un objeto BigInt sea mayor o igual que otro
 *
 * @tparam Base
 * @param number_y
 * @return true
 * @return false
 */
template <size_t Base>
bool BigInt<Base>::operator>=(const BigInt<Base> &number_y) const {
  return (*this > number_y || *this == number_y);
}

/**
 * @brief Comprueba que un objeto BigInt sea menor que otro
 *
 * @tparam Base_t
 * @param number_x
 * @param number_y
 * @return true
 * @return false
 */
template <size_t Base_t>
bool operator<(const BigInt<Base_t> &number_x, const BigInt<Base_t> &number_y) {
  return !(number_x >= number_y);
}

/**
 * @brief Comprueba que un objeto BigInt sea menor o igual que otro
 *
 * @tparam Base
 * @param number_y
 * @return true
 * @return false
 */
template <size_t Base>
bool BigInt<Base>::operator<=(const BigInt<Base> &number_y) const {
  return !(*this > number_y);
}

/**
 * @brief Comprueba que un objeto BigInt sea 0
 * 
 * @tparam Base
 * @return true
 * @return false
 */
template <size_t Base>
bool BigInt<Base>::IsZero() const {
  for (size_t i = 0; i < digits_.size(); i++) {
    if (digits_[i] != 0) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Inserta ceros al comienzo del BigInt
 *
 * @tparam Base
 * @param number_zero
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::FillZeros(unsigned number_zero) const {
  std::string number_str = this->to_string();
  number_str.insert(number_str.begin(), number_zero, '0');
  return BigInt<Base>(number_str);
}

/**
 * @brief Obtiene el valor absoluto de un BigInt
 *
 * @tparam Base
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::Abs() const {
  BigInt<Base> number_aux = *this;
  number_aux.setSign(1);
  return number_aux;
}

/**
 * @brief Convierte un objeto BigInt en un string. Es utilizada para imprimir el número,
 * por ejemplo, si el número es "1357" el resultado debe ser "7531"
 *
 * @tparam Base
 * @return std::string
 */
template <size_t Base>
std::string BigInt<Base>::to_string() const {
  std::string number_str;
  if (sign_ == -1) {
    number_str += '-';
  }
  for (int i = digits_.size() - 1; i >= 0; i--) {
    if (digits_[i] < 10) {
      number_str += digits_[i] + '0';
    } else {
      number_str += digits_[i] - 10 + 'A';
    }
  }
  return number_str;
}

/**
 * @brief Niega un objeto BigInt (-BigInt)
 *
 * @tparam Base
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator-() const {
  BigInt<Base> number_aux = *this;
  number_aux.setSign(-number_aux.getSign());
  return number_aux;
}

/**
 * @brief Realiza la suma de 2 objetos BigInt
 *
 * @tparam Base_t
 * @param number_x
 * @param number_y
 * @return BigInt<Base_t>
 */
template <size_t Base_t>
BigInt<Base_t> operator+(const BigInt<Base_t> &number_x,
                         const BigInt<Base_t> &number_y) {
  int carry = 0;
  size_t number_digit_different =
      abs(number_x.getDigits().size() - number_y.getDigits().size());
  BigInt<Base_t> number_y_aux;
  BigInt<Base_t> number_x_aux;
  if (number_x.getDigits().size() > number_y.getDigits().size()) {
    number_y_aux = number_y.FillZeros(number_digit_different);
    number_x_aux = number_x;
  } else if (number_x.getDigits().size() < number_y.getDigits().size()) {
    number_x_aux = number_x.FillZeros(number_digit_different);
    number_y_aux = number_y;
  } else {
    number_x_aux = number_x;
    number_y_aux = number_y;
  }

  // se controla el signo del resultado de los operandos debido a que es definido por el mayor
  if (number_x_aux.getSign() != number_y_aux.getSign()) {
    if (number_x_aux.getSign() == -1) {
      return number_y_aux - (-number_x_aux);
    } else {
      return number_x_aux - (-number_y_aux);
    }
  }

  std::vector<char> digits_sum;
  for (size_t i = 0; i < number_x_aux.getDigits().size(); i++) {
    int sum = number_x_aux[i] + number_y_aux[i] + carry;
    digits_sum.push_back(sum % Base_t);
    carry = sum / Base_t;
  }
  if (carry != 0) {
    digits_sum.push_back(carry);
  }
  return BigInt<Base_t>(digits_sum, number_x_aux.getSign());
}

/**
 * @brief Realiza la resta de 2 objetos BigInt
 *
 * @tparam Base
 * @param number_y
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator-(const BigInt<Base> &number_y) const {
  size_t number_digit_different =
      abs(this->getDigits().size() - number_y.getDigits().size());
  BigInt<Base> number_y_aux;
  BigInt<Base> number_x_aux;
  if (this->getDigits().size() > number_y.getDigits().size()) {
    number_y_aux = number_y.FillZeros(number_digit_different);
    number_x_aux = *this;
  } else if (this->getDigits().size() < number_y.getDigits().size()) {
    number_x_aux = this->FillZeros(number_digit_different);
    number_y_aux = number_y;
  } else {
    number_x_aux = *this;
    number_y_aux = number_y;
  }
  // solo para los números positivos y number_x_aux > number_y_aux podemos controlar siempre esta situación

  if (number_x_aux < number_y_aux) {
    return BigInt<Base>(number_y_aux - number_x_aux).setSign(-1);
  }
  if (number_x_aux.getSign() == 1 && number_y_aux.getSign() == -1) {
    return BigInt<Base>(number_x_aux + (-number_y_aux));
  } else if (number_x_aux.getSign() == -1 && number_y_aux.getSign() == 1) {
    return BigInt<Base>((-number_x_aux) + number_y_aux);
  } else if (number_x_aux.getSign() == -1 && number_y_aux.getSign() == -1) {
    return BigInt<Base>(number_x_aux + (-number_y_aux));
  }

  std::vector<char> digits_sub;
  int carry = 0;
  for (size_t i = 0; i < number_x_aux.size(); i++) {
    int sub = number_x_aux[i] - number_y_aux[i] - carry;
    if (sub < 0) {
      sub += Base;
      carry = 1;
    } else {
      carry = 0;
    }
    digits_sub.push_back(sub);
  }

  return BigInt<Base>(digits_sub, number_x_aux.getSign());
}

/**
 * @brief Añade un nuevo dígito al objeto BigInt
 *
 * @tparam Base
 * @param number_aux
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::PushBack(char number_aux) {
  digits_.push_back(static_cast<char>(number_aux));
  return *this;
}

/**
 * @brief Incrementa el objeto BigInt en 1 unidad (pre-incremento)
 *
 * @tparam Base
 * @return BigInt<Base>&
 */
template <size_t Base>
BigInt<Base> &BigInt<Base>::operator++() {
  BigInt<Base> One(1);
  *this = *this + One;
  return *this;
}

/**
 * @brief Incrementa el objeto BigInt en 1 unidad (post-incremento)
 *
 * @tparam Base
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator++(int) {
  BigInt<Base> One(1);
  BigInt<Base> number_aux = *this;
  *this = *this + One;
  return number_aux;
}

/**
 * @brief Decrementa el objeto BigInt en 1 unidad (pre-decremento)
 *
 * @tparam Base
 * @return BigInt<Base>&
 */
template <size_t Base>
BigInt<Base> &BigInt<Base>::operator--() {
  BigInt<Base> One(1);
  *this = *this - One;
  return *this;
}

/**
 * @brief Decrementa el objeto BigInt en 1 unidad (post-decremento)
 *
 * @tparam Base
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator--(int) {
  BigInt<Base> number_aux = *this;
  BigInt<Base> One(1);

  *this = *this - One;
  return number_aux;
}

/**
 * @brief Multiplica 2 objetos BigInt
 *
 * @tparam Base
 * @param number_y
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator*(const BigInt<Base> &number_y) const {
  size_t n = this->getDigits().size();
  size_t m = number_y.getDigits().size();
  std::vector<char> product(n + m, 0);

  if (this->IsZero() || number_y.IsZero()) {
    BigInt<Base> zero;
    return zero;
  }
  for (size_t i = 0; i < n; i++) {
    int carry = 0;
    for (size_t j = 0; j < m; j++) {
      int tmp = digits_[i] * number_y.digits_[j] + product[i + j] + carry;
      carry = tmp / Base;
      product[i + j] = (tmp % Base);
    }
    product[i + m] = (carry);
  }
  while (product.size() > 1 && product.back() == 0) product.pop_back();
  int sign = (this->getSign() == number_y.getSign()) ? 1 : -1;
  return BigInt(product, sign);
}

/**
 * @brief Divide 2 objetos BigInt
 *
 * @tparam Base
 * @param number_x
 * @param number_y
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> operator/(const BigInt<Base> &number_x,
                       const BigInt<Base> &number_y) {
  BigInt<Base> a = number_x;
  BigInt<Base> b = number_y;
  if (b.IsZero()) {
    std::string error_message = "Division by zero";
    throw BigIntDivisionByZero(error_message);
  }

  if (a < b) {
    return BigInt<Base>();
  }
  if (a == b) {
    return BigInt<Base>(1);
  }
  long i, lgcat = 0, cc;
  long n = a.getDigits().size();
  std::vector<char> cat(n, 0);
  BigInt<Base> t;
  BigInt<Base> aux_base(Base);
  for (i = n - 1; i >= 0 && (t * aux_base) + BigInt<Base>(a[i]) < b; i--) {
    t = t * aux_base;
    t = t + BigInt<Base>((int)a[i]);
  }
  for (; i >= 0; i--) {
    t = (t * Base) + BigInt<Base>((int)a[i]);
    for (cc = Base - 1; b * cc > t; cc--)
      ;
    t = t - (b * cc);
    cat[lgcat++] = cc;
  }

  std::vector<char> result(cat.size(), 0);

  for (i = 0; i < lgcat; i++) result[i] = cat[lgcat - i - 1];
  int sign = (a.getSign() == b.getSign()) ? 1 : -1;

  // se limpia el resultado
  while (result.size() > 1 && result.back() == 0) result.pop_back();

  BigInt<Base> r(result, sign);
  return r;
}

/**
 * @brief Módulo entre 2 objetos BigInt
 *
 * @tparam Base
 * @param number_y
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator%(const BigInt<Base> &number_y) const {
  return *this - (((*this / number_y).Abs()) * number_y);
}

/**
 * @brief Función para calcular la potencia de un número
 * 
 * @tparam Base
 * @param number_x
 * @param number_y
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> pow(const BigInt<Base> &number_x, const BigInt<Base> &number_y) {
  static BigInt<Base> zero;
  static BigInt<Base> one(1);
  static BigInt<Base> two(2);
  if (number_y < zero) {
    return zero;
  }
  if (number_y == zero) {
    return one;
  } else if (number_y % two == zero) {
    BigInt<Base> half = pow(number_x, number_y / two);
    return half * half;
  } else {
    BigInt<Base> half = pow(number_x, (number_y - one) / two);
    return half * half * number_x;
  }
}

/**
 * @brief Potencia de un BigInt (Por ejemplo: 5^2)
 *
 * @tparam Base
 * @param number_y
 * @return BigInt<Base>
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator^(const BigInt<Base> &number_y) const {
  return ::pow(*this, number_y);
}

/**
 * @brief Operador de flujo de salida para BigInt
 *
 * @tparam Base_aux
 * @param os
 * @param number_aux
 * @return std::ostream&
 */
template <size_t Base_aux>
std::ostream &operator<<(std::ostream &os, const BigInt<Base_aux> &number_aux) {
  std::string number_str = number_aux.to_string();
  os << number_str;
  return os;
}

/**
 * @brief Operador de flujo de entrada para BigInt
 *
 * @tparam Base_t
 * @param number_x
 * @return std::istream&
 */
template <size_t Base_t>
std::istream &operator>>(std::istream &input, BigInt<Base_t> &number_x) {
  std::string number_str;
  input >> number_str;
  number_x = BigInt<Base_t>(number_str);
  return input;
}

/**
 * @brief Operador para calcular el factorial de un número
 * 
 * @tparam Base_t
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator!() const {
  BigInt<Base> number_aux = this->Abs();
  BigInt<Base> result("1");
  BigInt<Base> i("1");
  BigInt<Base> zero("0");
  if (number_aux == zero) {
    return result;
  }
  for (; i <= number_aux; ++i) {
    result = result * i;
  }
  return result;
}

/**
 * @brief Operador para calcular la suma acumulando el resultado a la izquierda de la igualdad
 * 
 * @tparam Base_t
 * @param number_y
 * @return BigInt<Base> 
 */
template <size_t Base>
BigInt<Base> BigInt<Base>::operator+=(const BigInt<Base> &number_y) const {
  BigInt<Base> aux = *this;
  BigInt<Base> other = number_y;
  //return *this = *this + number_y;
  return aux = aux + other;
}

/**
 * @brief Operador de cambio de tipo de BigInt a BigInt<2>
 * 
 * @tparam Base 
 * @return BigInt<2> 
 */
template <size_t Base>
BigInt<Base>::operator BigInt<2>() const {
  BigInt<Base> number_aux = this->Abs();
  BigInt<Base> zero;
  BigInt<Base> two(2);
  std::vector<bool> result;
  if (number_aux == zero) {
    result.push_back(false);
    result.push_back(0);
    return BigInt<2>(result);
  }
  while (number_aux != zero) {
    result.push_back(number_aux % two == zero ? false : true);
    number_aux = number_aux / two;
  }
  // se debe añadir el signo
  result.push_back(0);
  if (this->getSign() == -1) {
    BigInt<2> aux(result);
    return -aux;
  }

  BigInt<2> aux(result);
  return aux;
}

/**
 * @brief Operador de cambio de tipo de BigInt a BigInt<8>
 * 
 * @tparam Base 
 * @return BigInt<8> 
 */
template <size_t Base>
BigInt<Base>::operator BigInt<8>() const {
  BigInt<Base> aux = *this;
  BigInt<2> aux2 = aux;
  BigInt<8> result = aux2.ConvertBaseT<8>();
  return result;
}

/**
 * @brief Operador de cambio de tipo de BigInt a BigInt<10>
 * 
 * @tparam Base 
 * @return BigInt<10> 
 */
template <size_t Base>
BigInt<Base>::operator BigInt<10>() const {
  BigInt<Base> aux = *this;
  BigInt<2> aux2 = aux;
  BigInt<10> result = aux2.ConvertBaseT<10>();
  return result;
}

/**
 * @brief Operador de cambio de tipo de BigInt a BigInt<16>
 * 
 * @tparam Base 
 * @return BigInt<16> 
 */
template <size_t Base>
BigInt<Base>::operator BigInt<16>() const {
  BigInt<Base> aux = *this;
  BigInt<2> aux2 = aux;
  BigInt<16> result = aux2.ConvertBaseT<16>();
  return result;
}

// Methods overrided from Number

/**
 * @brief Realiza la suma de los números BigInt<Base>
 *
 * @tparam Base
 * @param otherNum
 * @return Number*
 */
template <size_t Base>
Number *BigInt<Base>::add(const Number *otherNum) const {
  const BigInt *other = dynamic_cast<const BigInt *>(otherNum);
  if (other == nullptr) {
    other = new BigInt<Base>(*otherNum);
    return new BigInt<Base>(*this + *other);
  }

  BigInt<Base> *result = new BigInt<Base>(*this + *other);
  return result;
}

/**
 * @brief Realiza la resta de los números BigInt<Base>
 *
 * @tparam Base
 * @param otherNum
 * @return Number*
 */
template <size_t Base>
Number *BigInt<Base>::subtract(const Number *otherNum) const {
  const BigInt *other = dynamic_cast<const BigInt *>(otherNum);
  if (other == nullptr) {
    other = new BigInt<Base>(*otherNum);
    return new BigInt<Base>(*this - *other);
  }

  BigInt<Base> *result = new BigInt<Base>(*this - *other);
  return result;
}

/**
 * @brief Realiza la multiplicación de los números BigInt<Base>
 *
 * @tparam Base
 * @param otherNum
 * @return Number*
 */
template <size_t Base>
Number *BigInt<Base>::multiply(const Number *otherNum) const {
  const BigInt *other = dynamic_cast<const BigInt *>(otherNum);
  if (other == nullptr) {
    other = new BigInt<Base>(*otherNum);
    return new BigInt<Base>(*this * *other);
  }

  BigInt<Base> *result = new BigInt<Base>(*this * *other);
  return result;
}

/**
 * @brief Realiza la división de los números BigInt<Base>
 *
 * @tparam Base
 * @param otherNum
 * @return Number*
 */
template <size_t Base>
Number *BigInt<Base>::divide(const Number *otherNum) const {
  const BigInt *other = dynamic_cast<const BigInt *>(otherNum);
  if (other == nullptr) {
    other = new BigInt<Base>(*otherNum);
    return new BigInt<Base>(*this / *other);
  }

  BigInt<Base> *result = new BigInt<Base>(*this / *other);
  return result;
}

/**
 * @brief Realiza el módulo de los números BigInt<Base>
 *
 * @tparam Base
 * @param otherNum
 * @return Number*
 */
template <size_t Base>
Number *BigInt<Base>::module(const Number *otherNum) const {
  const BigInt *other = dynamic_cast<const BigInt *>(otherNum);
  if (other == nullptr) {
    other = new BigInt<Base>(*otherNum);
    return new BigInt<Base>(*this % *other);
  }

  BigInt<Base> *result = new BigInt<Base>(*this % *other);
  return result;
}

/**
 * @brief Realiza la potencia de los números BigInt<Base>
 *
 * @tparam Base
 * @param otherNum
 * @return Number*
 */
template <size_t Base>
Number *BigInt<Base>::pow(const Number *otherNum) const {
  const BigInt *other = dynamic_cast<const BigInt *>(otherNum);
  if (other == nullptr) {
    other = new BigInt<Base>(*otherNum);
    return new BigInt<Base>(this->operator^(*other));
  }

  BigInt<Base> *result = new BigInt<Base>(this->operator^(*other));
  return result;
}

/**
 * @brief Realiza la suma de los números BigInt<Base> acumulando el resultado
 *
 * @tparam Base
 * @param otherNum
 * @return Number*
 */
template <size_t Base>
Number *BigInt<Base>::addEqual(const Number *otherNum) const {
  const BigInt *other = dynamic_cast<const BigInt *>(otherNum);
  if (other == nullptr) {
    other = new BigInt<Base>(*otherNum);
    return new BigInt<Base>(this->operator+=(*other));
  }

  BigInt<Base> *result = new BigInt<Base>(this->operator+=(*other));
  return result;
}

/**
 * @brief Operador de flujo de salida para BigInt (método virtual de la clase Number)
 *
 * @tparam Base
 * @param os
 * @return std::ostream&
 */
template <size_t Base>
std::ostream &BigInt<Base>::write(std::ostream &os) const {
  os << *this;
  return os;
}

/**
 * @brief Operador de flujo de entrada para BigInt (método virtual de la clase Number)
 *
 * @tparam Base
 * @param is
 * @return std::istream&
 */
template <size_t Base>
std::istream &BigInt<Base>::read(std::istream &is) {
  is >> *this;
  return is;
}

/**
 * @brief Realiza la copia haciendo uso del operador =
 *
 * @tparam Base
 * @param otherNum
 * @return Number*
 */
template <size_t Base>
Number& BigInt<Base>::operator=(const Number& otherNum) {
  const BigInt* other = dynamic_cast<const BigInt*>(&otherNum);
  if (other == nullptr) {
    other = new BigInt<Base>(otherNum);
    *this = *other;
  }
  else {
    *this = *other;
  }
  return *this;
}














/**
 * @brief Constructor de BigInt<2>::BigInt dado un long
 *
 * @param number_x
 */
BigInt<2>::BigInt(long number_x) {
  bool sign = false;  // se inicializa el signo
  if (number_x < 0) {
    sign = true;
    number_x = -number_x;
  }
  if (number_x == 0) {  // // si el número es 0, pasa a ser 00
    digits.push_back(0);
    digits.push_back(0);
  }

  while (number_x > 0) {
    digits.push_back(number_x % 2);
    number_x /= 2;
  }
  digits.push_back(0);

  if (sign) {  // si el número es negativo
    *this = -*this;  
    }
}

/**
 * @brief Constructor de new BigInt<2>::BigInt dado un vector de bool
 *
 * @param digits
 */
BigInt<2>::BigInt(std::vector<bool> digits) {
  this->digits = digits;
}

/**
 * @brief Constructor de BigInt<2>::BigInt dado otro BigInt<2>
 *
 * @param number_x
 */
BigInt<2>::BigInt(const BigInt<2> &number_x) {
  digits = number_x.digits;
}

/**
 * @brief Constructor de BigInt<2>::BigInt dado un string
 *
 * @param number_x
 */
BigInt<2>::BigInt(std::string number_x) {
  if (number_x.size() == 0) {  // si el tamaño es 0, pasa a ser 00
    digits.push_back(0);
    digits.push_back(0);
  }
  if (number_x.size() == 1) {  // si el tamaño es 1, error porque debe ser 00 o 01 como mínimo
    if (number_x[0] == '0') {
      digits.push_back(0);
      digits.push_back(0);
    } else if (number_x[0] == '1') {
      digits.push_back(1);
      digits.push_back(1);
    } else {
      std::string message = "Error bad digit: " + number_x[0];
      throw BigIntBadDigit(message);
    }
  }
  for (int i = number_x.size() - 1; i >= 0; i--) {
    if (number_x[i] != '0' && number_x[i] != '1') {  // el número debe ser 0 o 1
     std::string message = "Error bad digit: " + number_x[i];
     throw BigIntBadDigit (message);
    }
    digits.push_back(number_x[i] - '0');
  }
}

// Constructor necesario para llevar a cabo el cambio de tipo de BigInt<2> a BigInt<Base>
BigInt<2>::BigInt(const std::vector<char> &digits_aux,const int &sign ){
std::cerr << "Constructor en base 2\n";
}

/**
 * @brief Método para acceder a los dígitos de un número
 *
 * @param n
 * @return true
 * @return false
 */
bool BigInt<2>::operator[](size_t n) const {
  return digits[n];
}

/**
 * @brief Método que retorna el tamaño (size) del objeto
 *
 * @return size_t
 */
size_t BigInt<2>::size() const {
  return digits.size();
}

/**
 * @brief Sobrecarga del operator= para copiar un BigInt<2>
 *
 * @param other
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::operator=(const BigInt<2> &other) {
  digits = other.digits;
  return *this;
}

/**
 * @brief Convierte el objeto a un en formato string
 *
 * @return std::string
 */
std::string BigInt<2>::to_string() const {
  std::string number_x;
  for (int i = digits.size() - 1; i >= 0; i--) {
    number_x += digits[i] + '0';
  }
  return number_x;
}

/**
 * @brief Método para obtener los dígitos de un objeto
 *
 * @return size_t
 */
std::vector<bool> BigInt<2>::getDigits() const {
  return digits;
}

/**
 * @brief Método para asignar los dígitos de un objeto
 *
 * @param n
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::setDigits(std::vector<bool> digits) {
  this->digits = digits;
  return *this;
}

/**
 * @brief Comprueba que 2 objetos BigInt<2> sean equivalentes
 *
 * @param other
 * @return true
 * @return false
 */
bool operator==(const BigInt<2> &first, const BigInt<2> &other) {
  BigInt<2> number_x;
  BigInt<2> number_y;
  // se rellena con el signo para evitar casos como: 0000001 = 01 -> false
  if (first.size() < other.digits.size()) {
    number_x = first.FillSign(other.digits.size() - first.size());
    number_y = other;
  } else if (first.size() > other.digits.size()) {
    number_x = first;
    number_y = other.FillSign(first.size() - other.digits.size());
  }else{
    number_x = first;
    number_y = other;
  }
  for (size_t i = 0; i < number_x.digits.size(); i++) {
    if (number_x.digits[i] != number_y.digits[i]) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Comprueba que 2 objetos BigInt<2> no sean equivalentes. Devuelve true si son distintos
 *
 * @param other
 * @return true
 * @return false
 */
bool BigInt<2>::operator!=(const BigInt<2> &other) const {
  return !(*this == other);
}

/**
 * @brief Comprueba si un BigInt<2> es mayor que otro y devuelve true si es mayor
 *
 * @param other
 * @return true
 * @return false
 */
bool operator>(const BigInt<2> &first, const BigInt<2> &other) {
  // se rellena con el signo para evitar casos como: 0000001 = 01 -> false
  // caso en el que tienen signo distinto
  if (first[first.size() - 1] < other.digits[other.digits.size() - 1]) {
    return true;
  } else if (first[first.size() - 1] > other.digits[other.digits.size() - 1]) {
    return false;
  }
  // caso en el que tienen el mismo signo
  bool sign = first[first.size() - 1];
  BigInt<2> number_x;
  BigInt<2> number_y;
  if (sign) {
    number_x = first.Abs();
    number_y = other.Abs();
  } else {
    number_x = first;
    number_y = other;
  }
  if (number_x.digits.size() > number_y.digits.size()) {
    number_y =
        number_y.FillSign(number_x.digits.size() - number_y.digits.size());
  } else if (number_x.digits.size() < number_y.digits.size()) {
    number_x =
        number_x.FillSign(number_y.digits.size() - number_x.digits.size());
  }
  for (long long i = number_x.digits.size() - 1; i >= 0; i--) {
    if (number_x.digits[i] > number_y.digits[i]) {
      return sign ? false : true;
    } else if (number_x.digits[i] < number_y.digits[i]) {
      return sign ? true : false;
    }
  }
  return false;
}

/**
 * @brief Comprueba si un BigInt<2> es menor que otro y devuelve true si es menor
 *
 * @param other
 * @return true
 * @return false
 */
bool operator<(const BigInt<2> &first, const BigInt<2> &other) {
  return !(first > other || first == other);
}

/**
 * @brief Comprueba si un BigInt<2> es mayor o igual que otro y devuelve true si es mayor o igual
 *
 * @param other
 * @return true
 * @return false
 */
bool BigInt<2>::operator>=(const BigInt<2> &other) const {
  return !(*this < other);
}

/**
 * @brief Comprueba si un BigInt<2> es menor o igual que otro y devuelve true si es menor o igual
 *
 * @param other
 * @return true
 * @return false
 */
bool BigInt<2>::operator<=(const BigInt<2> &other) const {
  return !(*this > other);
}

/**
 * @brief Desplazamiento en base a n (a la izquierda)
 *
 * @param n
 */
void BigInt<2>::operator<<(size_t n) {
  std::vector<bool> aux;
  aux.insert(aux.begin(), digits.begin(), digits.end() - n);
  aux.insert(aux.end(), n, digits[digits.size() - 1]);
  digits = aux;
}

/**
 * @brief Desplazamiento en base a n (a la derecha)
 *
 * @param n
 */
void BigInt<2>::operator>>(size_t n) {
  if (n > digits.size()) {
    digits.clear();
    digits.push_back(0);
    return;
  }
  std::vector<bool> aux;
  aux.insert(aux.begin(), n, digits[digits.size() - 1]);
  aux.insert(aux.end(), digits.begin() + n, digits.end());
  digits = aux;
}

/**
 * @brief Realiza la suma de 2 objetos BigInt<2>
 *
 * @param first
 * @param other
 * @return BigInt<2>
 */
BigInt<2> operator+(const BigInt<2> &first, const BigInt<2> &other) {
  std::vector<bool> number_x = first.digits;
  std::vector<bool> number_y = other.digits;
  bool carry = false;
  bool sum;
  
  // se añaden ceros al número más pequeño (por la izquierda) por posibles overflows
  if (number_x.size() > number_y.size()) {
    number_y = other.FillSign(number_x.size() - number_y.size()).digits;
  } else if (number_x.size() < number_y.size()) {
    number_x = first.FillSign(number_y.size() - number_x.size()).digits;
  }
  std::vector<bool> aux;
  for (size_t i = 0; i < number_x.size(); i++) {
    sum = number_x[i] ^ number_y[i] ^ carry;
    carry = (number_x[i] & number_y[i]) | (number_x[i] & carry) |
            (number_y[i] & carry);
    aux.push_back(sum);
  }
  
  // posible caso de overflow si el signo es igual
  if (!(first[first.size() - 1] != other[other.size() - 1])) {
    if (aux[aux.size() - 1] != first[first.size() - 1]) {  // overflow
      aux.push_back(first[first.size() - 1]);
    }
  }

  BigInt<2> result(aux);
  return result;
}

/**
 * @brief Realiza la suma de 2 objetos BigInt<2> con overflow
 *
 * @param first
 * @param other
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::suma_overflow(const BigInt<2> &first, const BigInt<2> &other) const {
  std::vector<bool> number_x = first.digits;
  std::vector<bool> number_y = other.digits;
  bool carry = false;
  bool sum;
  
  // se añaden ceros al número más pequeño (por la izquierda) por posibles overflows
  if (number_x.size() > number_y.size()) {
    number_y = other.FillSign(number_x.size() - number_y.size()).digits;
  } else if (number_x.size() < number_y.size()) {
    number_x = first.FillSign(number_y.size() - number_x.size()).digits;
  }

  std::vector<bool> aux;
  for (size_t i = 0; i < number_x.size(); i++) {
    sum = number_x[i] ^ number_y[i] ^ carry;
    carry = (number_x[i] & number_y[i]) | (number_x[i] & carry) |
            (number_y[i] & carry);
    aux.push_back(sum);
  }
  BigInt<2> result(aux);
  return result;
}

/**
 * @brief Realiza la resta de 2 objetos BigInt<2>
 *
 * @param other
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::operator-(const BigInt<2> &other) const {
  BigInt<2> number_y = other.ComplementoA2();
  BigInt<2> result = *this + number_y;
  return result;
}

/**
 * @brief Sobrecarga el operator>> para cambiar la posición hacia la derecha a BigInt<2> 
 *
 * @param other
 */
void BigInt<2>::operator>>(BigInt<2> &other) {
  // Example 0001 >> 1001 = 0100 1100
  std::vector<bool> aux;
  aux.insert(aux.end(), digits.begin(), digits.end() - 1);
  aux.insert(aux.begin(), digits[0]);
  std::vector<bool> aux2;
  aux2.insert(aux2.end(), other.digits.begin(), other.digits.end() - 1);
  aux2.insert(aux2.begin(), digits[digits.size() - 1]);
  this->setDigits(aux);
  other.setDigits(aux2);
}

/**
 * @brief Sobrecarga el operator<< para cambiar la posición hacia la izquierda a BigInt<2>
 *
 * @param other
 */
void BigInt<2>::operator<<(BigInt<2> &other) {
  // Example 0110 << 0100 = 1100 1000
  std::vector<bool> aux;
  aux.insert(aux.end(), digits.begin() + 1, digits.end());
  aux.push_back(other.digits[0]);
  std::vector<bool> aux2;
  aux2.insert(aux2.end(), other.digits.begin() + 1, other.digits.end());
  aux2.push_back(other.digits[other.digits.size() - 1]);
  this->setDigits(aux);
  other.setDigits(aux2);
}

/**
 * @brief Inserta un dígito al comienzo de un BigInt<2>
 *
 * @param digit
 */
void BigInt<2>::push_back(bool digit) {
  digits.push_back(digit);  // por ejemplo: example 011.push_back(1) = 1011
}

/**
 * @brief Multiplica 2 objetos BigInt<2>. Se utiliza el algoritmo de Robertson
 *
 * @param other
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::operator*(const BigInt<2> &other) const {
  // se deben añadir ceros al número más pequeño
  BigInt<2> number_M = *this;
  BigInt<2> number_Q = other;

  if (number_M.digits.size() > number_Q.digits.size()) {
    number_Q = other.FillSign(number_M.digits.size() - number_Q.digits.size());
  } else if (number_M.digits.size() < number_Q.digits.size()) {
    number_M = this->FillSign(number_Q.digits.size() - number_M.digits.size());
  }
  number_M.push_back(number_M.digits[number_M.digits.size() - 1]);
  size_t n = number_M.digits.size();
  std::vector<bool> aux(n, false);
  BigInt<2> number_A(aux);
  for (size_t i = 0; i < number_Q.digits.size() - 1; i++) {
    if (number_Q.digits[0]) {
      number_A = suma_overflow(number_A, number_M);
    }
    number_Q << number_A;
  }
  if (number_Q.digits[0]) {
    number_A = number_A - number_M;
  }
  number_Q << number_A;
  std::vector<bool> result;
  result.insert(result.begin(), number_Q.digits.begin(), number_Q.digits.end());
  result.insert(result.end(), number_A.digits.begin(), number_A.digits.end() - 1);

  // se limpia el bit de signo
  while (result.size() > 2 && (result.back() == *(result.end() - 2)) ) {
    result.erase(result.end() - 1);
  }

  return BigInt<2>(result);
}

/**
 * @brief Se comprueba que un número sea igual a 0
 *
 * @return true
 * @return false
 */
bool BigInt<2>::IsZero() const {
  for (size_t i = 0; i < digits.size(); i++) {
    if (digits[i]) {
      return false;
    }
  }
  return true;
}

/**
 * @brief Divide 2 objetos BigInt<2>
 *
 * @param other
 * @return BigInt<2>
 */
BigInt<2> operator/(const BigInt<2> &first, const BigInt<2> &other) {
  if(other.IsZero()) {  // se comprueba que other no sea 0
    std::string message = "Division by zero";
    throw BigIntDivisionByZero( message );
  }

  // deben tener el mismo tamaño
  BigInt<2> number_f = first;
  BigInt<2> number_s = other;
  if (number_f.digits.size() > number_s.digits.size()) {
    number_s = other.FillSign(number_f.digits.size() - number_s.digits.size());
  } else if (number_f.digits.size() < number_s.digits.size()) {
    number_f = first.FillSign(number_s.digits.size() - number_f.digits.size());
  }
  
  BigInt<2> number_M = number_s.Abs();
  std::vector<bool> aux_Q = number_f.Abs().digits;
  aux_Q.erase(aux_Q.end() - 1);
  BigInt<2> number_Q(aux_Q);
  std::vector<bool> aux_A(number_M.digits.size(), false);
  BigInt<2> number_A(aux_A);

  for (size_t i = 0; i < number_Q.digits.size(); i++) {
    number_Q >> number_A;
    number_A = number_A.suma_overflow(number_A, -number_M);
    if (number_A.digits[number_A.size() - 1]) {
      number_Q.digits[0] = false;
      number_A = number_A + number_M;
    } else {
      number_Q.digits[0] = true;
    }
  }
  
  // solo el cociente
  std::vector<bool> result;
  result.insert(result.begin(), number_Q.digits.begin(), number_Q.digits.end());
  
  // se limpia el bit de signo
  while ( result.size() > 2 && (result.back() == *(result.end() - 2)) && result.back() == 0) {
    result.erase(result.end() - 1);
  }
  
  // cambia el signo si el primero y el segundo son distintos
  BigInt<2> number_Q_r(result);
  if (first.digits[first.digits.size() - 1] !=
      other.digits[other.digits.size() - 1]) {
    number_Q_r = number_Q_r.ComplementoA2();
  }
  return number_Q_r;
}

/**
 * @brief Incrementa el objeto BigInt<2> en 1 unidad (pre-incremento)
 *
 * @return BigInt<2>&
 */
BigInt<2> &BigInt<2>::operator++() {
  *this = *this + BigInt<2>("01");
  return *this;
}

/**
 * @brief Incrementa el objeto BigInt<2> en 1 unidad (post-incremento)
 *
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::operator++(int) {
  BigInt<2> aux = *this;
  (*this) = (*this) + BigInt<2>("01");
  return aux;
}

/**
 * @brief Decrementa el objeto BigInt<2> en 1 unidad (pre-decremento)
 *
 * @return BigInt<2>&
 */
BigInt<2> &BigInt<2>::operator--() {
  *this = *this - BigInt<2>("01");
  return *this;
}

/**
 * @brief Decrementa el objeto BigInt<2> en 1 unidad (post-decremento)
 *
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::operator--(int) {
  BigInt<2> aux = *this;
  (*this) = (*this) - BigInt<2>("01");
  return aux;
}

/**
 * @brief Rellena el número con ceros a la izquierda
 *
 * @param n
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::FillSign(size_t n) const {
  std::string aux = this->to_string();
  char sign = aux[0];
  aux.insert(0, n, sign);
  BigInt<2> result(aux);
  return result;
}

/**
 * @brief Devuelve el valor absoluto de un BigInt<2>
 *
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::Abs() const {
  if (digits[digits.size() - 1]) {
    return this->ComplementoA2();
  }
  return *this;
}

/**
 * @brief Pasa un número en binario a complemento a 2
 *
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::ComplementoA2() const {
  std::vector<bool> aux;
  bool flag = false;
  // se debe añadir un cero por la izquierda para que el algoritmo funcione correctamente para, por ejemplo,
  // hacer que 100 sea 0100 y no salga de rango
  bool number_exceptional = true;
  if (digits[digits.size() - 1]) {
    for (size_t i = 0; i < digits.size() - 1; i++) {
      if (digits[i] == 1) {
        number_exceptional = false;
        break;
      }
    }
  } else {
    number_exceptional = false;
  }
  BigInt<2> number = *this;
  if (number_exceptional) {
    number.push_back(1);
  }
  for (size_t i = 0; i < number.size(); i++) {
    if (number[i] == 1 && !flag) {
      flag = true;
      aux.push_back(number[i]);
    } else if (flag) {
      aux.push_back(!number[i]);
    } else {
      aux.push_back(number[i]);
    }
  }
  BigInt<2> result(aux);
  return result;
}

/**
 * @brief Módulo entre 2 números BigInt<2>
 *
 * @param other
 * @return BigInt<2>
 */
BigInt<2> BigInt<2>::operator%(const BigInt<2> &other) const {
  BigInt<2> number_f = *this;
  BigInt<2> number_s = other;
  if (number_f.digits.size() > number_s.digits.size()) {
    number_s = other.FillSign(number_f.digits.size() - number_s.digits.size());
  } else if (number_f.digits.size() < number_s.digits.size()) {
    number_f = this->FillSign(number_s.digits.size() - number_f.digits.size());
  }
  //
  BigInt<2> number_M = number_s.Abs();
  std::vector<bool> aux_Q = number_f.Abs().digits;
  aux_Q.erase(aux_Q.end() - 1);
  BigInt<2> number_Q(aux_Q);
  std::vector<bool> aux_A(number_M.digits.size(), false);
  BigInt<2> number_A(aux_A);

  for (size_t i = 0; i < number_Q.digits.size(); i++) {
    number_Q >> number_A;
    number_A = number_A - number_M;
    if (number_A.digits[number_A.size() - 1]) {
      number_Q.digits[0] = false;
      number_A = number_A + number_M;
    } else {
      number_Q.digits[0] = true;
    }
  }

  std::vector<bool> result;
  result.insert(result.begin(), number_A.digits.begin(),
                number_A.digits.end() - 1);
  BigInt<2> number_Q_r(result);
  return number_Q_r;
}

/**
 * @brief Función para calcular la potencia de un BigInt<2>
 *
 * @param first 
 * @param other 
 * @return BigInt<2> 
 */
BigInt<2> pow(const BigInt<2> &first, const BigInt<2> &other) {
  static  BigInt<2> zero ("00");
  static  BigInt<2> one ("01");
  static  BigInt<2> two ("010");
  if (other < zero) {
    return zero;
  }
  if (other == zero) {
    return one;
  } else if (other % two == zero) {
    BigInt<2> half = pow(first, other / two);
    return half * half;
  } else {
    BigInt<2> half = pow(first, (other - one) / two);
    return half * half * first;
  }
}

/**
 * @brief Potencia de un BigInt<2> (Por ejemplo: 5^2)
 * 
 * @param other 
 * @return BigInt<2> 
 */
BigInt<2> BigInt<2>::operator^(const BigInt<2> &other) const {
  return ::pow(*this, other);
}

/**
 * @brief  Función para calcular el factorial de un BigInt<2>
 * 
 * @return BigInt<2> 
 */
BigInt<2> BigInt<2>::factorial() const {
  BigInt<2> result("01");
  BigInt<2> one("01");
  BigInt<2> zero("00");
  BigInt<2> i("01");
  while (i <= *this) {
    result = result * i;
    i = i + one;
  }
  return result;
}

/**
 * @brief Operador para calcular el factorial de un número BigInt<2>
 * 
 * @return BigInt<2> 
 */
BigInt<2> BigInt<2>::operator!() const{
  return this->factorial();
}

/**
 * @brief Operador para calcular la suma acumulando el resultado a la izquierda de la igualdad
 * 
 * @param number_y
 * @return BigInt<2> 
 */
BigInt<2> BigInt<2>::operator+=(const BigInt<2> &number_y) const {
  BigInt<2> aux = *this;
  BigInt<2> other = number_y;
  //return *this = *this + number_y;
  return aux = aux + other;
}

/**
 * @brief Devuelve el complemento a 2 de un número
 * 
 * @return BigInt<2> 
 */
BigInt<2> BigInt<2>::operator-() const{
  return this->ComplementoA2();
}

/**
 * @brief Devuelve el mismo número en base 2
 * 
 * @return BigInt<2>
*/
 BigInt<2>::operator BigInt<2>() const {
  return *this;
 }

/**
 * @brief Convierte un número BigInt<2> en un BigInt<Base>
 * 
 * @tparam base 
 * @return BigInt<base> 
 */
template <size_t base>
BigInt<base> BigInt<2>::ConvertBaseT(){
  BigInt<base> result("0");
  BigInt<2> number = this->Abs();
  BigInt<2> zero2("00");
  if (number == zero2) {
    return result;
  }
  BigInt<base> expo("0");
  BigInt<base> one("1");
  BigInt<base> two(2);
  for (size_t i = 0; i < number.size(); i++) {
    if (number[i]) {
      result = result + two.operator^(expo);  // forzar pow de BigInt<Base> para evitar llamadas a sí mismo
    }
    expo++;
  }
  
  // divide el resultado entre la base para guardar el número en un vector
  BigInt<base> aux = result;
  BigInt<base> zero("0");
  BigInt<base> base_number(base);
  std::vector<char> digits_aux;
  while (aux != zero) {
    BigInt<base> mod = aux % base_number;
    digits_aux.push_back(mod[0]);
    aux = aux / base_number;
  } 
  int sign = this->digits[this->digits.size() - 1] ? -1 : 1;
  BigInt<base> result_final(digits_aux, sign);
  return result_final;
}

/**
 * @brief Operador de cambio de tipo de BigInt a BigInt<8>
 * 
 * @tparam Base 
 * @return BigInt<8> 
 */
BigInt<2>::operator BigInt<8>()const{
  BigInt<2> aux = *this;
  return aux.ConvertBaseT<8>();
}

/**
 * @brief Operador de cambio de tipo de BigInt a BigInt<10>
 * 
 * @tparam Base 
 * @return BigInt<10> 
 */
BigInt<2>::operator BigInt<10>()const{
  BigInt<2> aux = *this;
  return aux.ConvertBaseT<10>();
}

/**
 * @brief Operador de cambio de tipo de BigInt a BigInt<16>
 * 
 * @tparam Base 
 * @return BigInt<16> 
 */
BigInt<2>::operator BigInt<16>()const{
  BigInt<2> aux = *this;
  return aux.ConvertBaseT<16>();
}

/**
 * @brief Operador de flujo de salida para BigInt<2>
 *
 * @param os
 * @param number_x
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &os, const BigInt<2> &number_x) {

  for (int i = number_x.digits.size() - 1; i >= 0; i--) {
    os << number_x.digits[i];
  }
  return os;
}

/**
 * @brief Operador de flujo de entrada para BigInt<2>
 *
 * @param is
 * @param number_x
 * @return std::istream&
 */
std::istream &operator>>(std::istream &is, BigInt<2> &number_x) {
  std::string number;
  is >> number;
  number_x = BigInt<2>(number);
  return is;
}

/**
 * @brief Realiza la suma de los números BigInt<Base>
 * 
 * @param otherNum 
 * @return Number* 
 */
Number* BigInt<2>::add(const Number* otherNum) const {
 const BigInt* other = dynamic_cast<const BigInt*>(otherNum);
   if(other == nullptr){
  other = new BigInt<2>(*otherNum);
    return new BigInt<2>(*this + *other);
   }
    BigInt<2>* result = new BigInt<2>(*this + *other);
    return result;
 }

 /**
  * @brief Realiza la resta de los números BigInt<Base>
  * 
  * @param otherNum 
  * @return Number* 
  */
 Number* BigInt<2>::subtract(const Number* otherNum) const {
  const BigInt* other = dynamic_cast<const BigInt*>(otherNum);
   if(other == nullptr){
  other = new BigInt<2>(*otherNum);
    return new BigInt<2>(*this - *other);
   }
    BigInt<2>* result = new BigInt<2>(*this - *other);
    return result;
 }

 /**
  * @brief Realiza la multiplicación de los números BigInt<Base>
  * 
  * @param otherNum 
  * @return Number* 
  */
 Number* BigInt<2>::multiply(const Number* otherNum) const {
  const BigInt* other = dynamic_cast<const BigInt*>(otherNum);
   if(other == nullptr){
  other = new BigInt<2>(*otherNum);
    return new BigInt<2>(*this * *other);
   }
    BigInt<2>* result = new BigInt<2>(*this * *other);
    return result;
 }

/**
 * @brief Realiza la división de los números BigInt<Base>
 * 
 * @param otherNum 
 * @return Number* 
 */
 Number* BigInt<2>::divide(const Number* otherNum) const {
  const BigInt* other = dynamic_cast<const BigInt*>(otherNum);
   if(other == nullptr){
  other = new BigInt<2>(*otherNum);
    return new BigInt<2>(*this / *other);
   }
    BigInt<2>* result = new BigInt<2>(*this / *other);
    return result;
 }

/**
 * @brief Realiza el módulo de los números BigInt<Base>
 * 
 * @param otherNum 
 * @return Number* 
 */
 Number* BigInt<2>::module(const Number* otherNum) const {
  const BigInt* other = dynamic_cast<const BigInt*>(otherNum);
   if(other == nullptr){
  other = new BigInt<2>(*otherNum);
    return new BigInt<2>(*this % *other);
   }
    BigInt<2>* result = new BigInt<2>(*this % *other);
    return result;
 }

/**
 * @brief Realiza la potencia de los números BigInt<Base>
 * 
 * @param otherNum 
 * @return Number* 
 */
 Number* BigInt<2>::pow(const Number* otherNum) const {
  const BigInt* other = dynamic_cast<const BigInt*>(otherNum);
   if (other == nullptr) {
  other = new BigInt<2>(*otherNum);
    return new BigInt<2>(this->operator^(*other));
   }
    BigInt<2>* result = new BigInt<2>(this->operator^(*other));
    return result;
 }

/**
 * @brief Realiza la suma de los números BigInt<2> acumulando el resultado
 *
 * @param otherNum
 * @return Number*
 */
Number* BigInt<2>::addEqual(const Number* otherNum) const {
  const BigInt* other = dynamic_cast<const BigInt*>(otherNum);
  if (other == nullptr) {
    other = new BigInt<2>(*otherNum);
    return new BigInt<2>(this->operator+=(*other));
  }

  BigInt<2> *result = new BigInt<2>(this->operator+=(*other));
  return result;
}

/**
 * @brief Operador de flujo de salida para BigInt (método virtual de la clase Number)
 * 
 * @param os
 * @return std::ostream& 
 */
 std::ostream& BigInt<2>::write(std::ostream& os) const {
  os << *this;
  return os;
 }



/**
 * @brief Operador de flujo de entrada para BigInt (método virtual de la clase Number)
 * 
 * @param is
 * @return std::istream& 
*/
 
std::istream& BigInt<2>::read(std::istream& is) {
  is >> *this;
  return is;
}

/**
 * @brief Realiza la copia haciendo uso del operador =
 * 
 * @param other 
 * @return Number* 
 */
 
Number& BigInt<2>::operator=(const Number& otherNum) {
  const BigInt<2>* other = dynamic_cast<const BigInt<2>*>(&otherNum);
  if (other == nullptr) {
    other = new BigInt<2>(otherNum);
    *this = *other;
  }
  else {
    *this = *other;
  }
  return *this;
}

#endif  // BIGINT_CC
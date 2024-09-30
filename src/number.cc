/**
 * @brief Código fuente de la clase Number declarada en el fichero number.h
 *
 */

#ifndef NUMBER_CC
#define NUMBER_CC

#include "..\include\number.h"
#include "..\include\bigint.h"

std::ostream& operator<<(std::ostream& os, const Number& number) {
  return number.write(os);
}

std::istream& operator>>(std::istream& is, Number& number) {
  return number.read(is);
}

 Number* Number::create(size_t base, const std::string& s) {
    std::string s1 = s;
     switch (base) {
    case 2:
      return new BigInt<2>(s1);
    case 8:
      return new BigInt<8>(s1);
    case 10:
      return new BigInt<10>(s1);
    case 16:
      return new BigInt<16>(s1);
    default:
    std::string s2 = "Base " + std::to_string(base) + " not implemented";
      throw BigIntBaseNotImplemented(s2);
  }
}

#endif // NUMBER_CC
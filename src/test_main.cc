/**
 * @brief Fichero que contiene el código fuente correspondiente al programa principal. Versión de prueba.
 *
 */

#include <iostream>

#include "..\include\number.h"
#include "..\include\bigint.h"
#include "number.cc"

int main() {
 // probar suma de números en distintas bases
  Number* n = Number::create(8, "12");
  Number* n2 = Number::create(10, "10");
  Number* n3 = Number::create(16, "A");
  Number* n4 = Number::create(2, "01010");

  // se llama add para cada base y su combinación
  std::cout << "Suma de 12 en base 8 y 10 en base 10: " << *(n->pow(n2)) << std::endl;
  std::cout << "Suma de 12 en base 8 y 10 en base 16: " << *(n->pow(n3)) << std::endl;
  std::cout << "Suma de 12 en base 8 y 10 en base 2: " << *(n->pow(n4)) << std::endl;
  std::cout << "Suma de 12 en base 8 y 10 en base 12: " << *(n->pow(n)) << std::endl;

  std::cout << "Suma de 10 en base 10 y A en base 16: " << *(n2->pow(n3)) << std::endl;
  std::cout << "Suma de 10 en base 10 y 01010 en base 2: " << *(n2->pow(n4)) << std::endl;
  std::cout << "Suma de 10 en base 10 y 12 en base 8: " << *(n2->pow(n)) << std::endl;
  std::cout << "Suma de 10 en base 10 y 10 en base 10: " << *(n2->pow(n2)) << std::endl;

  std::cout << "Suma de A en base 16 y 01010 en base 2: " << *(n3->pow(n4)) << std::endl;
  std::cout << "Suma de A en base 16 y 12 en base 8: " << *(n3->pow(n)) << std::endl;
  std::cout << "Suma de A en base 16 y 10 en base 10: " << *(n3->pow(n2)) << std::endl;
  std::cout << "Suma de A en base 16 y A en base 16: " << *(n3->pow(n3)) << std::endl;

  std::cout << "Suma de 01010 en base 2 y 12 en base 8: " << *(n4->pow(n)) << std::endl;
  std::cout << "Suma de 01010 en base 2 y 10 en base 10: " << *(n4->pow(n2)) << std::endl;
  std::cout << "Suma de 01010 en base 2 y A en base 16: " << *(n4->pow(n3)) << std::endl;
  std::cout << "Suma de 01010 en base 2 y 01010 en base 2: " << *(n4->pow(n4)) << std::endl;

  // probamos la excepción de constructor genérico del tipo baddigit
  try {
    Number* n5 = Number::create(8, "12A");
    std::cout << *n5 << std::endl;
  }catch (BigIntBadDigit &e) {
    std::cout << "Error: " << e.what() << std::endl;
    std::cout << "Error: " << e.message() << std::endl;
  }

  delete n;
  delete n2;
  delete n3;
  delete n4;
  return 0;
}
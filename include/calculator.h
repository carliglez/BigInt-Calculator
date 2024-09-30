/**
 * @brief Fichero de cabecera de la clase Calculator. Clase template con notación polaca inversa.
 *
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <functional>
#include <typeinfo>

#include "number.h"
#include "bigint.h"
#include "..\src\number.cc"
#include "bigintexception.h"

template <class T>
class Calculator {
 public:
  Calculator();
  void InitOperations();
  void SetTokens(const std::vector<std::vector<std::string>>& tokens);
  T Operate(std::vector<std::string> tokens_line);
  void Process();
  bool CheckStackEmpty();
  bool CheckIsOperands(const std::string&, const std::string&);

  template <class U>
  friend std::ostream& operator<<(std::ostream& os, const Calculator<U>& c);

 private:
  std::vector<std::vector<std::string>> tokens;
  std::stack<T> stack;
  std::map<std::string, T> variables;
  std::map<std::string, std::function<T(T, T)>> operations;
  std::map<std::string, std::function<T(T)>> unary_operations;

};

#include "../src/calculator.cc"  // se codifica en otro fichero, aunque podría hacerse en este

#endif  // CALCULATOR_H
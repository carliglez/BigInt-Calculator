/**
 * @brief Código fuente de la clase Calculator declarada en el fichero calculator.h
 *
 */

#include "..\include\calculator.h"

/**
 * @brief Constructor de Calculator<T>::Calculator
 *
 * @tparam T
 */
template <class T>
Calculator<T>::Calculator() {
  InitOperations();
}

/**
 * @brief Setter de los tokens
 *
 * @tparam T
 * @param tokens
 */
template <class T>
void Calculator<T>::SetTokens(const std::vector<std::vector<std::string>>& tokens) {
  this->tokens = tokens;
}

/**
 * @brief Inicializa las operaciones que es capaz de realizar la calculadora de BigInt
 *
 * @tparam T
 */
template <class T>
void Calculator<T>::InitOperations() {
  // Operaciones de la clase Number
  operations["+"] = [](T a, T b) { return a->add(b); };
  operations["-"] = [](T a, T b) { return a->subtract(b); };
  operations["*"] = [](T a, T b) { return a->multiply(b); };
  operations["/"] = [](T a, T b) { return a->divide(b); };
  operations["%"] = [](T a, T b) { return a->module(b); };
  operations["^"] = [](T a, T b) { return a->pow(b); };

  // Extra
  operations["+="] = [](T a, T b) { return a->addEqual(b); };
  unary_operations["+=u"] = [](T a) { return a->addEqual(a); }; // versión unaria
}

/**
 * @brief Opera los tokens de una línea y retorna el resultado obtenido de la operación realizada
 *
 * @tparam T
 * @param tokens_line
 * @return T
 */
template <class T>
T Calculator<T>::Operate(std::vector<std::string> tokens_line) {
  while (!stack.empty()) {
    std::cout << *(stack.top()) << std::endl;
      stack.pop();
    }
  try {
    for (auto& token : tokens_line) {
      if (operations.count(token) == 1 && stack.size() >= 2) {
        T a = stack.top();
        stack.pop();
        T b = stack.top();
        stack.pop();
        stack.push(operations[token](b, a));
      } else if (unary_operations.count(token) == 1 && stack.size() >= 1) {
        T a = stack.top();
        stack.pop();
        stack.push(unary_operations[token](a));
      } else if (variables.count(token) == 1) {
        stack.push(variables[token]);
      } else {
        while (!stack.empty()) {
          stack.pop();
        }
        std::cerr << "Error Operation not found: ";
        for (auto& token : tokens_line) {
          std::cerr << token << " ";
        }
        std::cerr << std::endl;
        return Number::create(10, "0");
      }
    }
  } catch (BigIntBadDigit& e) {
    std::cerr << e.what() << std::endl;
    while (!stack.empty()) {
      stack.pop();
    }
    return Number::create(10, "0");
  } catch (BigIntBaseNotImplemented& e) {
    std::cerr << e.what() << std::endl;
    while (!stack.empty()) {
      stack.pop();
    }
    return Number::create(10, "0");
  } catch (BigIntDivisionByZero& e) {
    std::cerr << e.what() << std::endl;
    while (!stack.empty()) {
      stack.pop();
    }
    return Number::create(10, "0");
  }

  if (stack.size() != 1) {
    std::cerr << "Error in line: Stack size != 1 :";
    for (auto& token : tokens_line) {
      std::cerr << token << " ";
    }
    std::cerr << std::endl;
    while (!stack.empty()) {
      std::cerr << *(stack.top()) << " \n";
      stack.pop();
    }
    return Number::create(10, "0");
  }
  T result = stack.top();
  stack.pop();
  return result;
}

/**
 * @brief Método procesar llamado desde el método main del programa
 *
 * @tparam T
 */
template <class T>
void Calculator<T>::Process() {
  // Ejemplo:
  // N1 = 2 10100
  // N2 = 10 24770
  // E1 ? N1 N2 +
  for (auto& line : tokens) {
    if (line.size() == 4 && line[1] == "=") {
      // se comprueba si se trata de un número o una variable
      if (variables.count(line[2]) == 1) {
        variables[line[0]] = variables[line[2]];
      } else {
        try {
          // se crea un nuevo número
          size_t base = std::stoi(line[2]);
          std::string number = line[3];
          variables[line[0]] = Number::create(base, number);
        } catch (std::invalid_argument& e) {
          std::cout << "Error in line: ";
          for (auto& token : line) {
            std::cout << token << " ";
          }
          continue;
        } catch (BigIntBadDigit& e) {
          std::cerr << e.what() << std::endl;
          variables[line[0]] = Number::create(10, "0");
        } catch (BigIntBaseNotImplemented& e) {
          std::cerr << e.what() << std::endl;
          variables[line[0]] = Number::create(10, "0");
        }
      }

    } else if (line.size() > 3) {
      // E1 ? N1 N2 +  ==>  E1 ? Operate(N1, N2, +)
      // se crea un vector con N1, N2 y + y se le pasa al método Operate()
      if (line[1] != "?") {
        std::cout << "Error in line: ";
        for (auto& token : line) {
          std::cout << token << " ";
        }
        continue;
      }
      std::vector<std::string> tokens_line(line.begin() + 2, line.end());
      variables[line[0]] = Operate(tokens_line);
    } else {
      std::cout << "Error in line: ";
      for (auto& token : line) {
        std::cout << token << " ";
      }
    }
  }
}

/**
 * @brief Sobrecarga el operador de salida para imprimir las variables
 *
 * @tparam U
 * @param os
 * @param c
 * @return std::ostream&
 */
template <class H>
std::ostream& operator<<(std::ostream& os, const Calculator<H>& c) {
  for (auto& var : c.variables) {
    os << var.first << " = " << *(var.second) << std::endl;
  }
  return os;
}
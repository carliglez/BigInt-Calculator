/**
 * @brief Fichero que contiene el código fuente correspondiente al programa principal. Versión correspondiente
 * a la práctica 3 de representación de números grandes haciendo uso de BigInt<Base>.
 *
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "..\include\bigint.h"
#include "..\include\calculator.h"
#include "number.cc"
#include "..\include\number.h"

/*
  - El programa se encarga de leer un fichero de entrada y de escribir en otro de salida.
  - Una vez comienza a leer el fichero, es capaz de reconocer la base del número que está leyendo uso
    para después proceder a evaluar y realizar las operaciones correspondientes con los números leídos.

  - Ejemplo de ejecución: ./main resource/input.txt resource/salida.txt
*/

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Modo de uso: " << argv[0] << " <entrada> <salida>" << std::endl;
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open()) {
    std::cerr << "Error al abrir el fichero " << argv[1] << std::endl;
    return 1;
  }
  std::ofstream output(argv[2]);
  if (!output.is_open()) {
    std::cerr << "Error al abrir el fichero " << argv[2] << std::endl;
    return 1;
  }
  std::string line;
  std::vector<std::vector<std::string>> tokens;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::vector<std::string> line_tokens;
    std::string token;
    while (iss >> token) {
      line_tokens.push_back(token);
    }
    tokens.push_back(line_tokens);
  }

  // gestión de excepciones
  try {
    Calculator<Number*> calc;  // calculadora de Number* en lugar de BigInt<Base>
    calc.SetTokens(tokens);  // se asignan los tokens para la calculadora
    calc.Process();  // se evalúan las operaciones
    output << calc;  // se escriben los resultados en el fichero de salida
  } catch (const std::invalid_argument& ia) {
    std::cerr << "Argumento inválido: " << ia.what() << '\n';
  } catch (const std::out_of_range& oor) {
    std::cerr << "Error por fuera de rango: " << oor.what() << '\n';
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
  } catch (std::string& e) {
    std::cerr << "Error: " << e << '\n';
  } catch (...) {
    std::cerr << "Error: " << "Error desconocido" << '\n';
  }
  
  // mensaje indicando resultados en el fichero seleccionado como salida
  std::cout << "\nResultados disponibles en el fichero de salida..." << std::endl;

  return 0;
}
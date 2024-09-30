/**
 * @brief Fichero de cabecera de la clase BigIntDivisionByZero que hereda de BigIntException.
 *
 */

#ifndef BIGINTDIVISIONBYZERO_H
#define BIGINTDIVISIONBYZERO_H

#include "bigintexception.h"

class BigIntDivisionByZero : public BigIntException
{
public:
    BigIntDivisionByZero(const std::string& message) : BigIntException(message) {}
    const char* what() const throw() { return "Division by zero"; }
};

#endif // BIGINTDIVISIONBYZERO_H
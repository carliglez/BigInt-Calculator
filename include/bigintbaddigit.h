/**
 * @brief Fichero de cabecera de la clase BigIntBadDigit que hereda de BigIntException.
 *
 */

#ifndef BIGINTBADDIGIT_H
#define BIGINTBADDIGIT_H

#include "bigintexception.h"

class BigIntBadDigit : public BigIntException
{
public:
    BigIntBadDigit(const std::string& message) : BigIntException(message) {}
    const char* what() const throw() { return "Bad digit"; }
};

#endif // BIGINTBADDIGIT_H
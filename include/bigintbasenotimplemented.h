/**
 * @brief Fichero de cabecera de la clase BigIntBaseNotImplemented que hereda de BigIntException.
 *
 */

#ifndef BIGINTBASENOTIMPLEMENTED_H
#define BIGINTBASENOTIMPLEMENTED_H

#include "bigintexception.h"

class BigIntBaseNotImplemented : public BigIntException
{
public:
    BigIntBaseNotImplemented(const std::string& message) : BigIntException(message) {}
    const char* what() const throw() { return "Base not implemented"; }
};

#endif // BIGINTBASENOTIMPLEMENTED_H
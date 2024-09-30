/**
 * @brief Fichero de cabecera de la clase BigIntException que hereda de std::exception.
 *
 */

#ifndef BIGINTEXCEPTION_H
#define BIGINTEXCEPTION_H

#include <exception>
#include <string>

class BigIntException : public std::exception
{
public:
    BigIntException(const std::string& message) : message_(message) {}
    virtual const char* what() const throw() { return message_.c_str(); }
    std::string message() const { return message_; }
private:
    std::string message_;
};  

#include "bigintbaddigit.h"
#include "bigintbasenotimplemented.h"
#include "bigintdivisionbyzero.h"

#endif // BIGINTEXCEPTION_H
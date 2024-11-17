#pragma once

#include <stdexcept>

class FigureErrorCheck: public std::domain_error
{
    public:
    explicit FigureErrorCheck(const std::string& msg)
    : std::domain_error(msg) {}
};
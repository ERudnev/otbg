#pragma once

#include <format>
#include <stdexcept>

//#define _INCOMPLETE_ do {} while (false)
#define _INCOMPLETE_ throw std::logic_error(std::format("{}:{}: INCOMPLETE", __FILE__, __LINE__));

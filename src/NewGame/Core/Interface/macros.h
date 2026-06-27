#pragma once

#include <format>
#include <stdexcept>

//#define _INCOMPLETE_ do {} while (false)
#define _INCOMPLETE_ throw std::logic_error(std::format("{}:{}: INCOMPLETE implementation", __FILE__, __LINE__));

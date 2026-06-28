#pragma once

#include <format>
#include <iostream>
#include <stdexcept>
#include <string>


#define _INCOMPLETE_ throw std::logic_error(std::format("{}:{}: INCOMPLETE implementation", __FILE__, __LINE__));

namespace swexp::detail {
    inline void logDebug(const std::string& message)
    {
        std::cout << message << std::endl;
    }
}

#define _LOG_DEBUG_(message) ::swexp::detail::logDebug(message)

#pragma once

#include "../scenarios.h"

#include <iostream>
#include <sstream>
#include <string>

namespace tests::internals
{

    class CoutCapture
    {
    public:
        CoutCapture()
            : _oldBuffer(std::cout.rdbuf(_buffer.rdbuf()))
        {
        }

        ~CoutCapture() { std::cout.rdbuf(_oldBuffer); }

        tests::Strings lines() const
        {
            tests::Strings result;
            std::istringstream input(_buffer.str());
            for (std::string line; std::getline(input, line);)
            {
                if (!line.empty() && line.back() == '\r')
                {
                    line.pop_back();
                }
                result.push_back(line);
            }
            return result;
        }

    private:
        std::ostringstream _buffer;
        std::streambuf* _oldBuffer;
    };

    inline std::istringstream serialise(const tests::Strings& commands)
    {
        std::ostringstream output;
        for (const auto& command : commands)
        {
            output << command << '\n';
        }
        return std::istringstream(output.str());
    }

}

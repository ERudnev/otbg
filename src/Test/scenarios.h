#pragma once

#include <unordered_map>
#include <vector>
#include <string>

namespace tests {

    using Strings = std::vector<std::string>;

    struct Scenario;
    using Bucket = std::unordered_map<std::string, Scenario>;

    struct Scenario {
        using Id = std::string;
        Strings commands;
        Strings expectations;
    };

    struct Usage {
        static Bucket generateScenarios();
        static Strings checkEqual(const Strings& reports, const Strings& expectations);

    };
}
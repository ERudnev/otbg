#pragma once

#include <unordered_map>
#include <vector>
#include <string>

namespace tests {

    using Strings = std::vector<std::string>;

    struct Scenario;
    struct CheckReport;
    using Bucket = std::unordered_map<std::string, Scenario>;

    struct Scenario {
        using Id = std::string;
        Strings commands;
        Strings expectations;
    };

    struct CheckReport {
        Strings matched;
        Strings mismatches;
    };

    struct Usage {
        static Bucket generateScenarios();
        static CheckReport checkEqual(const Strings& reports, const Strings& expectations);

    };
}
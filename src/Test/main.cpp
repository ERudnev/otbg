#include "NewGame/interface.include.h"
#include "IO/interface.include.h"
#include "scenarios.h"

#include <format>
#include <iostream>
#include <sstream>

namespace
{
    class CoutCapture
    {
    public:
        CoutCapture() :
                _oldBuffer(std::cout.rdbuf(_buffer.rdbuf()))
        {}

        ~CoutCapture()
        {
            std::cout.rdbuf(_oldBuffer);
        }

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

    std::istringstream serialise(const tests::Strings& commands)
    {
        std::ostringstream output;
        for (const auto& command : commands)
        {
            output << command << '\n';
        }
        return std::istringstream(output.str());
    }
}

int main(int, char**)
{
    using namespace sw;

    const tests::Bucket bucket = tests::Usage::generateScenarios();
    int failedCount = 0;

    for (const auto& [name, scenario] : bucket)
    {
        game::InjectedRandomDevice::init(0);
        EventSystem events;
        game::World world(events);

        io::CommandParser parser;
        parser.add<io::CreateMap>([&world](auto command) { world.createMap(command.width, command.height); });
        parser.add<io::SpawnSwordsman>(
                [&world](auto command)
                {
                    world.spawnUnit(
                            command.unitId,
                            {command.x, command.y},
                            command.hp,
                            command.strength,
                            command.chance,
                            command.rending);
                });
        parser.add<io::SpawnHunter>(
                [](auto command)
                {
                    //TODO
                });
        parser.add<io::March>([&world](auto command) { world.march(command.unitId, {command.targetX, command.targetY}); });

        tests::Strings grabbed;
        {
            CoutCapture capture;
            auto input = serialise(scenario.commands);

            parser.parse(input);

            while (!world.isGameOver())
            {
                world.step();
            }

            grabbed = capture.lines();
        }

        const auto reports = tests::Usage::checkEqual(grabbed, scenario.expectations);

        if (reports.empty())
        {
            std::cout << std::format(R"(OK: Scenario "{}")", name) << std::endl;
        }
        else
        {
            ++failedCount;
            std::cout << std::format(R"(FAIL: Scenario "{}")", name) << std::endl;
            for (const auto& report : reports)
            {
                std::cout << std::format("  {}", report) << std::endl;
            }
        }
    }

    return failedCount == 0 ? 0 : 1;
}

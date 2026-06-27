#include "NewGame/interface.include.h"
#include "IO/interface.include.h"
#include "internals/Capture.h"
#include "scenarios.h"

#include <format>
#include <iostream>
#include <sstream>

int main(int, char**)
{
    using namespace swexp;

    const tests::Bucket bucket = tests::Usage::generateScenarios();
    int failedCount = 0;

    for (const auto& [name, scenario] : bucket)
    {
        try
        {
            using namespace sw;

            swexp::core::interface::InjectedRandomDevice::init(0);
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
                tests::internals::CoutCapture capture;
                auto input = tests::internals::serialise(scenario.commands);

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
        catch (std::exception& e)
        {
            std::cout << std::format(R"(CRITICAL: Scenario "{}": {})", name, e.what()) << std::endl;
            ++failedCount;
        }
    }

    std::cout << std::format("finished {} tests with {}/{} good/failed", bucket.size(), bucket.size() - failedCount, failedCount);

    return failedCount == 0 ? 0 : 1;
}

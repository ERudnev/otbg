#include "NewGame/interface.include.h"
#include "IO/interface.include.h"
#include "internals/Capture.h"
#include "scenarios.h"

#include <format>
#include <iostream>
#include <optional>
#include <sstream>

int main(int, char**)
{
    using namespace swexp;

    // const tests::Bucket bucket = tests::Usage::generateScenarios();
    const tests::Bucket bucket = tests::Usage::generateNewScenarios();
    int failedCount = 0;

    for (const auto& [name, scenario] : bucket)
    {
        std::optional<tests::internals::CoutCapture> capture;
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
                        world.spawnSwordsman(
                                command.unitId,
                                game::composition::Swordsman::Actions::SpawnParameters{
                                        .externalId = command.unitId,
                                        .position = {command.x, command.y},
                                        .hitPoints = command.hp,
                                        .melee = {.strength = command.strength},
                                        .rending = {.chance = command.chance, .damage = command.rending},
                                });
                    });
            parser.add<io::SpawnHunter>(
                    [&world](auto command)
                    {
                        world.spawnHunter(
                                command.unitId,
                                game::composition::Hunter::Actions::SpawnParameters{
                                        .externalId = command.unitId,
                                        .position = {command.x, command.y},
                                        .hitPoints = command.hp,
                                        .ranged = {.minRange = 2, .maxRange = command.range, .damage = command.agility},
                                        .melee = {.strength = command.strength},
                                        .poisonArrows
                                        = {.chance = command.chance, .damage = command.poison, .duration = 5},
                                });
                    });
            parser.add<io::March>([&world](auto command)
                                  { world.march(command.unitId, {command.targetX, command.targetY}); });

            capture.emplace();
            auto input = tests::internals::serialise(scenario.commands);

            parser.parse(input);

            while (!world.isGameOver())
            {
                world.step();
            }

            const tests::Strings grabbed = capture->lines();
            capture.reset();

            const auto report = tests::Usage::checkEqual(grabbed, scenario);

            if (report.mismatches.empty())
            {
                std::cout << std::format(R"(OK: Scenario "{}")", name) << std::endl;
            }
            else
            {
                ++failedCount;
                std::cout << std::format(R"(FAIL: Scenario "{}")", name) << std::endl;

                if (not report.matched.empty())
                {
                    std::cout << "  matched events:" << std::endl;
                    for (const auto& matched : report.matched)
                    {
                        std::cout << std::format("    {}", matched) << std::endl;
                    }
                }

                for (const auto& mismatch : report.mismatches)
                {
                    std::cout << std::format("  {}", mismatch) << std::endl;
                }
            }
        }
        catch (std::exception& e)
        {
            tests::Strings captured;
            if (capture)
            {
                captured = capture->lines();
                capture.reset(); // вернуть cout из buffer
            }
            std::cout << std::format(R"(CRITICAL: Scenario "{}": {})", name, e.what()) << '\n';
            for (const auto& line : captured)
            {
                std::cout << "  " << line << '\n';
            }
            ++failedCount;
        }
    }

    std::cout << std::format(
            "finished {} tests with {}/{} good/failed", bucket.size(), bucket.size() - failedCount, failedCount);

    return failedCount == 0 ? 0 : 1;
}

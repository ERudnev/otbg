#include "scenarios.h"

// Baseline scenarios are embedded directly into the test binary on purpose.
// At this stage they act as a small self-contained regression harness, not as
// editable test fixtures, so avoiding extra file/path dependencies is useful.

#include <algorithm>
#include <sstream>

namespace tests
{
    Bucket Usage::generateScenarios()
    {
        return {
            {"scenario_1", Scenario{
                .commands = {
                    "CREATE_MAP 10 10",
                    "SPAWN_SWORDSMAN 1 5 2 10 1 100 5",
                    "MARCH 1 5 7",
                    "SPAWN_SWORDSMAN 2 7 5 10 1 100 5",
                    "MARCH 2 2 5",
                },
                .expectations = {
                    "[0] MAP_CREATED width=10 height=10 ",
                    "[0] UNIT_SPAWNED unitId=1 unitType=swordsman x=5 y=2 ",
                    "[0] MARCH_STARTED unitId=1 x=5 y=2 targetX=5 targetY=7 ",
                    "[0] UNIT_SPAWNED unitId=2 unitType=swordsman x=7 y=5 ",
                    "[0] MARCH_STARTED unitId=2 x=7 y=5 targetX=2 targetY=5 ",
                    "[1] UNIT_MOVED unitId=1 x=5 y=3 ",
                    "[1] UNIT_MOVED unitId=2 x=6 y=5 ",
                    "[2] UNIT_MOVED unitId=1 x=5 y=4 ",
                    "[2] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=9 ",
                    "[3] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=9 ",
                    "[3] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=8 ",
                    "[4] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=8 ",
                    "[4] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=7 ",
                    "[5] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=7 ",
                    "[5] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=6 ",
                    "[6] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=6 ",
                    "[6] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=5 ",
                    "[7] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=5 ",
                    "[7] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=4 ",
                    "[8] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=4 ",
                    "[8] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=3 ",
                    "[9] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=3 ",
                    "[9] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=2 ",
                    "[10] UNIT_ABILITY_USED abilityUnitId=1 abilityName=rending ",
                    "[10] UNIT_DIED unitId=2 ",
                    "[11] UNIT_MOVED unitId=1 x=5 y=5 ",
                    "[12] UNIT_MOVED unitId=1 x=5 y=6 ",
                    "[13] UNIT_MOVED unitId=1 x=5 y=7 ",
                    "[13] MARCH_ENDED unitId=1 x=5 y=7 ",
                },
            }},
            {"scenario_2", Scenario{
                 .commands = {
                     "CREATE_MAP 10 10",
                     "SPAWN_SWORDSMAN 1 5 2 10 1 100 5",
                     "MARCH 1 5 4",
                     "SPAWN_SWORDSMAN 2 5 7 10 1 100 5",
                     "MARCH 2 5 5",
                 },
                 .expectations = {
                    "[0] MAP_CREATED width=10 height=10 ",
                    "[0] UNIT_SPAWNED unitId=1 unitType=swordsman x=5 y=2 ",
                    "[0] MARCH_STARTED unitId=1 x=5 y=2 targetX=5 targetY=4 ",
                    "[0] UNIT_SPAWNED unitId=2 unitType=swordsman x=5 y=7 ",
                    "[0] MARCH_STARTED unitId=2 x=5 y=7 targetX=5 targetY=5 ",
                    "[1] UNIT_MOVED unitId=1 x=5 y=3 ",
                    "[1] UNIT_MOVED unitId=2 x=5 y=6 ",
                    "[2] UNIT_MOVED unitId=1 x=5 y=4 ",
                    "[2] MARCH_ENDED unitId=1 x=5 y=4 ",
                    "[2] UNIT_MOVED unitId=2 x=5 y=5 ",
                    "[2] MARCH_ENDED unitId=2 x=5 y=5 ",
                    "[3] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=9 ",
                    "[3] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=9 ",
                    "[4] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=8 ",
                    "[4] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=8 ",
                    "[5] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=7 ",
                    "[5] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=7 ",
                    "[6] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=6 ",
                    "[6] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=6 ",
                    "[7] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=5 ",
                    "[7] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=5 ",
                    "[8] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=4 ",
                    "[8] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=4 ",
                    "[9] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=3 ",
                    "[9] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=3 ",
                    "[10] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=2 ",
                    "[10] UNIT_ABILITY_USED abilityUnitId=2 abilityName=rending ",
                    "[10] UNIT_DIED unitId=1 ",
                 },
             }},
            {"scenario_3", Scenario{
                 .commands = {
                    "CREATE_MAP 10 10",
                    "SPAWN_SWORDSMAN 1 5 5 10 1 0 5",
                    "SPAWN_SWORDSMAN 2 5 7 10 1 100 5",
                    "MARCH 2 5 2",
                 },
                 .expectations = {
                     "[0] MAP_CREATED width=10 height=10 ",
                     "[0] UNIT_SPAWNED unitId=1 unitType=swordsman x=5 y=5 ",
                     "[0] UNIT_SPAWNED unitId=2 unitType=swordsman x=5 y=7 ",
                     "[0] MARCH_STARTED unitId=2 x=5 y=7 targetX=5 targetY=2 ",
                     "[1] UNIT_MOVED unitId=2 x=5 y=6 ",
                     "[2] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=9 ",
                     "[2] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=9 ",
                     "[3] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=8 ",
                     "[3] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=8 ",
                     "[4] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=7 ",
                     "[4] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=7 ",
                     "[5] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=6 ",
                     "[5] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=6 ",
                     "[6] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=5 ",
                     "[6] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=5 ",
                     "[7] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=4 ",
                     "[7] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=4 ",
                     "[8] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=3 ",
                     "[8] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=3 ",
                     "[9] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=2 ",
                     "[9] UNIT_ABILITY_USED abilityUnitId=2 abilityName=rending ",
                     "[9] UNIT_DIED unitId=1 ",
                     "[10] UNIT_MOVED unitId=2 x=5 y=5 ",
                     "[11] UNIT_MOVED unitId=2 x=5 y=4 ",
                     "[12] UNIT_MOVED unitId=2 x=5 y=3 ",
                     "[13] UNIT_MOVED unitId=2 x=5 y=2 ",
                     "[13] MARCH_ENDED unitId=2 x=5 y=2 ",
                 },
             }},
            {"scenario_4", Scenario{
                 .commands = {
                    "CREATE_MAP 10 10",
                    "SPAWN_SWORDSMAN 1 5 1 5 2 100 4",
                    "SPAWN_HUNTER 2 2 2 10 1 1 3 100 5",
                    "MARCH 1 5 8",
                    "MARCH 2 6 6",
                    "SPAWN_SWORDSMAN 3 8 4 10 1 100 2",
                    "MARCH 3 1 4",
                 },
                 .expectations = {
                    "[0] MAP_CREATED width=10 height=10 ",
                    "[0] UNIT_SPAWNED unitId=1 unitType=swordsman x=5 y=1 ",
                    "[0] MARCH_STARTED unitId=1 x=5 y=1 targetX=5 targetY=8 ",
                    "[0] UNIT_SPAWNED unitId=3 unitType=swordsman x=8 y=4 ",
                    "[0] MARCH_STARTED unitId=3 x=8 y=4 targetX=1 targetY=4 ",
                    "[1] UNIT_MOVED unitId=1 x=5 y=2 ",
                    "[1] UNIT_MOVED unitId=3 x=7 y=4 ",
                    "[2] UNIT_MOVED unitId=1 x=5 y=3 ",
                    "[2] UNIT_MOVED unitId=3 x=6 y=4 ",
                    "[3] UNIT_ATTACKED attackerUnitId=1 targetUnitId=3 damage=2 targetHp=8 ",
                    "[3] UNIT_ATTACKED attackerUnitId=3 targetUnitId=1 damage=1 targetHp=4 ",
                    "[4] UNIT_ATTACKED attackerUnitId=1 targetUnitId=3 damage=2 targetHp=6 ",
                    "[4] UNIT_ATTACKED attackerUnitId=3 targetUnitId=1 damage=1 targetHp=3 ",
                    "[5] UNIT_ATTACKED attackerUnitId=1 targetUnitId=3 damage=2 targetHp=4 ",
                    "[5] UNIT_ATTACKED attackerUnitId=3 targetUnitId=1 damage=1 targetHp=2 ",
                    "[6] UNIT_ATTACKED attackerUnitId=1 targetUnitId=3 damage=2 targetHp=2 ",
                    "[6] UNIT_ATTACKED attackerUnitId=3 targetUnitId=1 damage=1 targetHp=1 ",
                    "[7] UNIT_ATTACKED attackerUnitId=1 targetUnitId=3 damage=2 targetHp=0 ",
                    "[7] UNIT_DIED unitId=3 ",
                    "[8] UNIT_MOVED unitId=1 x=5 y=4 ",
                    "[9] UNIT_MOVED unitId=1 x=5 y=5 ",
                    "[10] UNIT_MOVED unitId=1 x=5 y=6 ",
                    "[11] UNIT_MOVED unitId=1 x=5 y=7 ",
                    "[12] UNIT_MOVED unitId=1 x=5 y=8 ",
                    "[12] MARCH_ENDED unitId=1 x=5 y=8 ",
                },
            }},
        };
    }

    Strings Usage::checkEqual(const Strings& reports, const Strings& expectations)
    {
        Strings mismatches;

        std::vector<bool> matchedReports(reports.size(), false);

        for (const auto& expected : expectations)
        {
            const auto match = std::ranges::find_if(
                    reports,
                    [&expected, &matchedReports, &reports](const std::string& actual)
                    {
                        const size_t index = static_cast<size_t>(&actual - reports.data());
                        return !matchedReports[index] && actual == expected;
                    });

            if (match == reports.end())
            {
                std::ostringstream message;
                message << "missing expected event [" << expected << "]";
                mismatches.push_back(message.str());
                continue;
            }

            const size_t matchedIndex = static_cast<size_t>(&(*match) - reports.data());
            matchedReports[matchedIndex] = true;
        }

        for (size_t index = 0; index < reports.size(); ++index)
        {
            if (!matchedReports[index])
            {
                std::ostringstream message;
                message << "unexpected actual event [" << reports[index] << "]";
                mismatches.push_back(message.str());
            }
        }

        return mismatches;
    }
}

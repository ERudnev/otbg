#include "scenarios.h"

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
                    R"([0] MAP_CREATED width=10 height=10 )",
                    R"([0] UNIT_SPAWNED unitId=1 unitType=swordsman x=5 y=2 )",
                    R"([0] MARCH_STARTED unitId=1 x=5 y=2 targetX=5 targetY=7 )",
                    R"([0] UNIT_SPAWNED unitId=2 unitType=swordsman x=7 y=5 )",
                    R"([0] MARCH_STARTED unitId=2 x=7 y=5 targetX=2 targetY=5 )",
                    R"([1] UNIT_MOVED unitId=1 x=5 y=3 )",
                    R"([1] UNIT_MOVED unitId=2 x=6 y=5 )",
                    R"([2] UNIT_MOVED unitId=1 x=5 y=4 )",
                    R"([2] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=9 )",
                    R"([3] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=9 )",
                    R"([3] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=8 )",
                    R"([4] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=8 )",
                    R"([4] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=7 )",
                    R"([5] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=7 )",
                    R"([5] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=6 )",
                    R"([6] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=6 )",
                    R"([6] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=5 )",
                    R"([7] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=5 )",
                    R"([7] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=4 )",
                    R"([8] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=4 )",
                    R"([8] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=3 )",
                    R"([9] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=3 )",
                    R"([9] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=2 )",
                    R"([10] UNIT_ABILITY_USED abilityUnitId=1 abilityName=rending )",
                    R"([10] UNIT_DIED unitId=2 )",
                    R"([11] UNIT_MOVED unitId=1 x=5 y=5 )",
                    R"([12] UNIT_MOVED unitId=1 x=5 y=6 )",
                    R"([13] UNIT_MOVED unitId=1 x=5 y=7 )",
                    R"([13] MARCH_ENDED unitId=1 x=5 y=7 )",
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
                    R"([0] MAP_CREATED width=10 height=10 )",
                    R"([0] UNIT_SPAWNED unitId=1 unitType=swordsman x=5 y=2 )",
                    R"([0] MARCH_STARTED unitId=1 x=5 y=2 targetX=5 targetY=4 )",
                    R"([0] UNIT_SPAWNED unitId=2 unitType=swordsman x=5 y=7 )",
                    R"([0] MARCH_STARTED unitId=2 x=5 y=7 targetX=5 targetY=5 )",
                    R"([1] UNIT_MOVED unitId=1 x=5 y=3 )",
                    R"([1] UNIT_MOVED unitId=2 x=5 y=6 )",
                    R"([2] UNIT_MOVED unitId=1 x=5 y=4 )",
                    R"([2] MARCH_ENDED unitId=1 x=5 y=4 )",
                    R"([2] UNIT_MOVED unitId=2 x=5 y=5 )",
                    R"([2] MARCH_ENDED unitId=2 x=5 y=5 )",
                    R"([3] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=9 )",
                    R"([3] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=9 )",
                    R"([4] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=8 )",
                    R"([4] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=8 )",
                    R"([5] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=7 )",
                    R"([5] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=7 )",
                    R"([6] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=6 )",
                    R"([6] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=6 )",
                    R"([7] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=5 )",
                    R"([7] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=5 )",
                    R"([8] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=4 )",
                    R"([8] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=4 )",
                    R"([9] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=3 )",
                    R"([9] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=3 )",
                    R"([10] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=2 )",
                    R"([10] UNIT_ABILITY_USED abilityUnitId=2 abilityName=rending )",
                    R"([10] UNIT_DIED unitId=1 )",
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
                     R"([0] MAP_CREATED width=10 height=10 )",
                     R"([0] UNIT_SPAWNED unitId=1 unitType=swordsman x=5 y=5 )",
                     R"([0] UNIT_SPAWNED unitId=2 unitType=swordsman x=5 y=7 )",
                     R"([0] MARCH_STARTED unitId=2 x=5 y=7 targetX=5 targetY=2 )",
                     R"([1] UNIT_MOVED unitId=2 x=5 y=6 )",
                     R"([2] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=9 )",
                     R"([2] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=9 )",
                     R"([3] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=8 )",
                     R"([3] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=8 )",
                     R"([4] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=7 )",
                     R"([4] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=7 )",
                     R"([5] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=6 )",
                     R"([5] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=6 )",
                     R"([6] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=5 )",
                     R"([6] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=5 )",
                     R"([7] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=4 )",
                     R"([7] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=4 )",
                     R"([8] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=3 )",
                     R"([8] UNIT_ATTACKED attackerUnitId=2 targetUnitId=1 damage=1 targetHp=3 )",
                     R"([9] UNIT_ATTACKED attackerUnitId=1 targetUnitId=2 damage=1 targetHp=2 )",
                     R"([9] UNIT_ABILITY_USED abilityUnitId=2 abilityName=rending )",
                     R"([9] UNIT_DIED unitId=1 )",
                     R"([10] UNIT_MOVED unitId=2 x=5 y=5 )",
                     R"([11] UNIT_MOVED unitId=2 x=5 y=4 )",
                     R"([12] UNIT_MOVED unitId=2 x=5 y=3 )",
                     R"([13] UNIT_MOVED unitId=2 x=5 y=2 )",
                     R"([13] MARCH_ENDED unitId=2 x=5 y=2 )",
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
                    R"([0] MAP_CREATED width=10 height=10 )",
                    R"([0] UNIT_SPAWNED unitId=1 unitType=swordsman x=5 y=1 )",
                    R"([0] MARCH_STARTED unitId=1 x=5 y=1 targetX=5 targetY=8 )",
                    R"([0] UNIT_SPAWNED unitId=3 unitType=swordsman x=8 y=4 )",
                    R"([0] MARCH_STARTED unitId=3 x=8 y=4 targetX=1 targetY=4 )",
                    R"([1] UNIT_MOVED unitId=1 x=5 y=2 )",
                    R"([1] UNIT_MOVED unitId=3 x=7 y=4 )",
                    R"([2] UNIT_MOVED unitId=1 x=5 y=3 )",
                    R"([2] UNIT_MOVED unitId=3 x=6 y=4 )",
                    R"([3] UNIT_ATTACKED attackerUnitId=1 targetUnitId=3 damage=2 targetHp=8 )",
                    R"([3] UNIT_ATTACKED attackerUnitId=3 targetUnitId=1 damage=1 targetHp=4 )",
                    R"([4] UNIT_ATTACKED attackerUnitId=1 targetUnitId=3 damage=2 targetHp=6 )",
                    R"([4] UNIT_ATTACKED attackerUnitId=3 targetUnitId=1 damage=1 targetHp=3 )",
                    R"([5] UNIT_ATTACKED attackerUnitId=1 targetUnitId=3 damage=2 targetHp=4 )",
                    R"([5] UNIT_ATTACKED attackerUnitId=3 targetUnitId=1 damage=1 targetHp=2 )",
                    R"([6] UNIT_ATTACKED attackerUnitId=1 targetUnitId=3 damage=2 targetHp=2 )",
                    R"([6] UNIT_ATTACKED attackerUnitId=3 targetUnitId=1 damage=1 targetHp=1 )",
                    R"([7] UNIT_ATTACKED attackerUnitId=1 targetUnitId=3 damage=2 targetHp=0 )",
                    R"([7] UNIT_DIED unitId=3 )",
                    R"([8] UNIT_MOVED unitId=1 x=5 y=4 )",
                    R"([9] UNIT_MOVED unitId=1 x=5 y=5 )",
                    R"([10] UNIT_MOVED unitId=1 x=5 y=6 )",
                    R"([11] UNIT_MOVED unitId=1 x=5 y=7 )",
                    R"([12] UNIT_MOVED unitId=1 x=5 y=8 )",
                    R"([12] MARCH_ENDED unitId=1 x=5 y=8 )",
                },
            }},
        };
    }

    Strings Usage::checkEqual(const Strings& reports, const Strings& expectations)
    {
        Strings mismatches;

        const size_t maxCount = std::max(reports.size(), expectations.size());
        for (size_t index = 0; index < maxCount; ++index)
        {
            const std::string actual = index < reports.size() ? reports[index] : "<missing>";
            const std::string expected = index < expectations.size() ? expectations[index] : "<missing>";

            if (actual != expected)
            {
                std::ostringstream message;
                message << "line " << index << ": expected [" << expected << "], got [" << actual << "]";
                mismatches.push_back(message.str());
            }
        }

        return mismatches;
    }
}

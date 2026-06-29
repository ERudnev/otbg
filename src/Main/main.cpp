#include "NewGame/interface.include.h"
#include "IO/interface.include.h"

#include <fstream>
#include <stdexcept>

int main(int argc, char** argv)
{
    using namespace sw;
    using namespace swexp;

    swexp::core::interface::InjectedRandomDevice::init();

    if (argc != 2)
    {
        throw std::runtime_error("Error: No file specified in command line argument");
    }

    std::ifstream file(argv[1]);
    if (!file)
    {
        throw std::runtime_error("Error: File not found - " + std::string(argv[1]));
    }

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
                                .poisonArrows = {.chance = command.chance, .damage = command.poison, .duration = 5},
                        });
            });
    parser.add<io::March>([&world](auto command) { world.march(command.unitId, {command.targetX, command.targetY}); });

    parser.parse(file);

    while (!world.isGameOver())
    {
        world.step();
    }

    return 0;
}

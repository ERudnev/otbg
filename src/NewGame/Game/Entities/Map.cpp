#include "NewGame/Game/Entities/Map.h"

#include "IO/interface.include.h"
#include "NewGame/Core/Mechanism/Helpers.h"
#include "NewGame/Game/Entities/Unit.h"

#include <cstdlib>

namespace swexp::game::entity
{
    namespace ask = ::swexp::core::manipulation;

    auto Map::Actions::spawn(Writing writing, const State& state) -> Id
    {
        return writing.state.line<Map>().createEntity(Map::State{state});
    }

    bool Map::Actions::isPositionFree(Reading reading, Id mapId, Position position)
    {
        const auto& map = Get(reading, mapId);
        if (position.x >= map.width || position.y >= map.height)
            return false;

        const auto& units = reading.state.line<Unit>().elements;
        for (const auto& [_, unit] : units)
        {
            if (unit.position == position)
                return false;
        }

        return true;
    }

    void Map::Actions::findTargets(
        Reading reading,
        Id,
        uint32_t currentUnitId,
        Position currentPosition,
        std::vector<uint32_t>& outUnitIds)
    {
        const auto& units = reading.state.line<Unit>().elements;
        for (const auto& [unitId, unit] : units)
        {
            if (unitId == currentUnitId)
                continue;

            const auto dx = std::abs(static_cast<int64_t>(currentPosition.x) - static_cast<int64_t>(unit.position.x));
            const auto dy = std::abs(static_cast<int64_t>(currentPosition.y) - static_cast<int64_t>(unit.position.y));
            if (dx <= 1 && dy <= 1)
                outUnitIds.push_back(unitId);
        }
    }

    bool Map::Actions::tryGetNextPosition(
        Reading reading,
        Id mapId,
        Position currentPosition,
        Position targetPosition,
        Position& outPosition)
    {
        Position nextPosition = currentPosition;
        if (targetPosition.x < currentPosition.x)
            nextPosition.x -= 1;
        else if (targetPosition.x > currentPosition.x)
            nextPosition.x += 1;

        if (targetPosition.y < currentPosition.y)
            nextPosition.y -= 1;
        else if (targetPosition.y > currentPosition.y)
            nextPosition.y += 1;

        if (not isPositionFree(reading, mapId, nextPosition))
            return false;

        outPosition = nextPosition;
        return true;
    }

    void Map::Emitters::_generated_call_all(Emitting emitting)
    {
        mapCreated(emitting);
    }

    void Map::Emitters::mapCreated(Emitting emitting)
    {
        const auto& initial = emitting.initial.state;
        const auto& updated = emitting.updated.state;

        for (const auto id : swexp::core::mechanism::helpers::findAddedOrUpdated<Map>(initial, updated))
        {
            const auto& mapState = ask::get<Map>(emitting.updated, id);

            _LOG_DEBUG_("Emitting Map Created");
            emitting.listener.event(0, sw::io::MapCreated{
                .width = mapState.width,
                .height = mapState.height,
            });
        }
    }
}

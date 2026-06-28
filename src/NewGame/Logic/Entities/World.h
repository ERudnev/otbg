#pragma once

#include "NewGame/Core/Interface/features.api.h"


// world knows this entity/composition types to be able to create em:
// TODO: make swexp::meta::Dependency<typename ...Types> to make this explicit
// yep. World is still God-object, to have better interface, expose Entity::Logic manually
#include "NewGame/Logic/Entities/Map.h"
#include "NewGame/Logic/Compositions/Swordsman.h"
#include "NewGame/Logic/Compositions/Hunter.h"

namespace swexp::game::entity
{
    // standard api mapping
    //namespace core = swexp::core::api;
    using namespace swexp::core::api;

    struct World : Entity<World> {
        using Turn = uint32_t;
        struct State {
            Turn currentTurn;

            // to get rid of optional, make World == Map existence binded
            std::optional<Map::Id> map;

            // TODO: add this to manage friend/foe and other Unit Sorting
            //std::vector<Unit::Id> unitsTracked;
        };
        struct Logic final : BaseLogic {
            static void createMap(Writing, Id, const Map::Position& size);
        };

        struct Emitters final : BaseEmitters {
            static void mapIsCreated(Analysis);
        };
    };
}
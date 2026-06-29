#include "NewGame/Game/Effects/OrderedToMove.h"

#include "IO/interface.include.h"
#include "NewGame/Core/Mechanism/Helpers.h"

namespace swexp::game::effect
{
    void OrderedToMove::Actions::order(Writing writing, entity::Unit::Id unitId, entity::Map::Position target)
    {
        writing.state.line<OrderedToMove>().createOrUpdateComponent<entity::Unit>(
            unitId, State{.targetPosition = target});
    }

    void OrderedToMove::Emitters::_generated_call_all(Emitting emitting)
    {
        marchStarted(emitting);
    }

    void OrderedToMove::Emitters::marchStarted(Emitting emitting)
    {
        const auto& initial = emitting.initial.state;
        const auto& updated = emitting.updated.state;

        for (const auto id : swexp::core::mechanism::helpers::findAddedOrUpdated<OrderedToMove>(initial, updated))
        {
            const auto& unitState = updated.line<entity::Unit>().elements.at(id);
            const auto& orderState = updated.line<OrderedToMove>().elements.at(id);

            emitting.listener.event(0, sw::io::MarchStarted{
                .unitId = unitState.publicUnitId_placeholder,
                .x = unitState.position.x,
                .y = unitState.position.y,
                .targetX = orderState.targetPosition.x,
                .targetY = orderState.targetPosition.y,
            });
        }
    }
}

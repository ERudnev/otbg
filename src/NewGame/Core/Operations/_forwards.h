#pragma once

namespace swexp::core::operations
{
    struct ContextReadingData;
    struct ContextWritingData;
    struct ContextReactionsData;
    struct ContextEmittersData;

    // TODO: this is a direction of development of "swexp". Make Normalization as separate Entity Axis
    // will look as:
    // void Foo::Normalization::clamp_value(Normalization context, Foo::Id id, ...);
}

// Public names for Transaction Context types:
namespace swexp::core::api::context
{
    using Reading = core::operations::ContextReadingData;
    using Writing = core::operations::ContextWritingData;
    using Reacting = core::operations::ContextReactionsData;
    using Emitting = core::operations::ContextEmittersData;
}

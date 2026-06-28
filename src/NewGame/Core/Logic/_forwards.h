#pragma once

namespace swexp::core::operations
{
    struct ContextData;
    struct ContextUpdatesData;

    // This is placeholder for Operational semantics, working with Val&/const Val&
    using WritingContext = ContextData&;
    using ReadingContext = const ContextData&;
    using AnalyticContext = const ContextUpdatesData&;

    // TODO: this is a direction of development of "swexp". Make Normalization as separate Entity Axis
    // will look as:
    // void Foo::Normalization::clamp_value(Normalization context, Foo::Id id, ...);
}
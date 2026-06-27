#pragma once

namespace swexp::core::operations
{
    struct ContextData;

    // This works very well for operators semantics, but still discussable
    using Context = ContextData&;

    // TODO: make "ReadingContext/WritingContext" or just "Reading/Writing" to
    // separate const-like operations from mutations
}
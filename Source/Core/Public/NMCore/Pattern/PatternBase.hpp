#pragma once

#include "NMCore/Color.hpp"
#include "NMM/Point.hpp"

class NMPatternBase
{
public:

    virtual ~NMPatternBase() = default;

    virtual NMColor ColorAt(const NMPoint& point) const = 0;
};

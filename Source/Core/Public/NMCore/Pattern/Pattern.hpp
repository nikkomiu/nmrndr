#pragma once

#include "NMCore/Color.hpp"
#include "NMM/Point.hpp"

class NMPattern
{
public:

    virtual NMColor ColorAt(const NMPoint& point) const = 0;
};

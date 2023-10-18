#pragma once

#include "NMCore/Color.hpp"
#include "NMM/Matrix.hpp"
#include "NMM/Point.hpp"

class NMPrimitiveBase;

class NMPatternBase
{
public:

    NMPatternBase(const NMMatrix& transform = NMMatrix::Identity4x4()) : transform(transform){};
    virtual ~NMPatternBase() = default;

    virtual NMColor ColorAt(const NMPoint& point) const = 0;
    NMColor ColorAtShapePoint(const NMPrimitiveBase& shape, const NMPoint& point) const;

    inline const NMMatrix& GetTransform() const { return transform; }
    inline virtual void SetTransform(const NMMatrix& newTransform) { transform = newTransform; }

protected:

    NMMatrix transform;
};

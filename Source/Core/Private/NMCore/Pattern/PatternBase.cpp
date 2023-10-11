#include "NMCore/Pattern/PatternBase.hpp"

#include "NMCore/Primitive/PrimitiveBase.hpp"

NMColor NMPatternBase::ColorAtShapePoint(const NMPrimitiveBase &shape, const NMPoint &point) const
{
    NMPoint objectPoint = shape.GetTransform().Inverse() * point;
    NMPoint patternPoint = transform.Inverse() * objectPoint;

    return ColorAt(patternPoint);
}

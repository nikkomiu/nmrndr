#pragma once

#include <algorithm>
#include <vector>

#include "NMCore/Primitive/PrimitiveBase.hpp"
#include "NMCore/RT/IntersectionList.hpp"
#include "NMCore/RT/Intersection.hpp"
#include "NMCore/RT/Ray.hpp"
#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"

struct SNMIntersectionState
{
public:

    SNMIntersectionState() = default;

    SNMIntersectionState(const SNMIntersection& intersection, const NMRay& ray)
        : SNMIntersectionState(intersection, ray, SNMIntersectionList({ intersection })) {}

    SNMIntersectionState(const SNMIntersection& intersection, const NMRay& ray, SNMIntersectionList xs)
        : t(intersection.t),
          object(intersection.object),
          point(ray.Position(t)),
          eyeVector(-ray.GetDirection()),
          normalVector(object->NormalAt(point))
    {
        overPoint = point + (normalVector * nmmath::rayEpsilon);
        reflectVector = ray.GetDirection().Reflect(normalVector);

        if (normalVector.DotProduct(eyeVector) < 0.0f)
        {
            isInside = true;
            normalVector = -normalVector;
        }

        std::vector<const NMPrimitiveBase*> containers = {};
        for (const SNMIntersection& i : xs)
        {
            if (i == intersection)
            {
                if (containers.empty())
                {
                    n1 = 1.0f;
                }
                else
                {
                    n1 = containers.back()->GetMaterial().GetRefractiveIndex();
                }
            }

            if (std::find(containers.begin(), containers.end(), i.object) != containers.end())
            {
                containers.erase(std::remove(containers.begin(), containers.end(), i.object), containers.end());
            }
            else
            {
                containers.push_back(i.object);
            }

            if (i == intersection)
            {
                if (containers.empty())
                {
                    n2 = 1.0f;
                }
                else
                {
                    n2 = containers.back()->GetMaterial().GetRefractiveIndex();
                }

                break;
            }
        }
    }

    float t = 0.0f;
    const NMPrimitiveBase* object = nullptr;
    NMPoint point = NMPoint();
    NMPoint overPoint = NMPoint();
    NMVector eyeVector = NMVector();
    NMVector normalVector = NMVector();
    NMVector reflectVector = NMVector();
    bool isInside = false;

    float n1;
    float n2;

    friend std::ostream& operator<<(std::ostream& os, const SNMIntersectionState& state)
    {
        os << "IntersectionState(" << std::endl;
        os << "\tt: " << state.t << std::endl;
        os << "\tobject: " << state.object << std::endl;
        os << "\tpoint: " << state.point << std::endl;
        os << "\toverPoint: " << state.overPoint << std::endl;
        os << "\teyeVector: " << state.eyeVector << std::endl;
        os << "\tnormalVector: " << state.normalVector << std::endl;
        os << "\treflectVector: " << state.reflectVector << std::endl;
        os << "\tisInside: " << state.isInside << std::endl;
        os << ")" << std::endl;

        return os;
    }
};

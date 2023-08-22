#pragma once

#include <memory>
#include <vector>

#include "Color.hpp"
#include "Light/Point.hpp"
#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "Primitive/Sphere.hpp"
#include "RT/IIntersectionObject.hpp"
#include "RT/IntersectionList.hpp"
#include "RT/IntersectionState.hpp"

class NMWorld
{
public:

    NMWorld() = default;

    static NMWorld Default()
    {
        NMWorld world;

        world.pointLights.push_back(NMPointLight(NMPoint(-10.0f, 10.0f, -10.0f), NMColor(1.0f, 1.0f, 1.0f)));

        // Create a unit sphere
        std::shared_ptr<NMSphere> outerSphere = std::make_shared<NMSphere>();
        outerSphere->SetMaterial(NMMaterial(NMColor(0.8f, 1.0f, 0.6f), 0.1f, 0.7f, 0.2f, 200.0f));
        world.objects.push_back(outerSphere);

        // Create an inner sphere
        std::shared_ptr<NMSphere> innerSphere = std::make_shared<NMSphere>();
        innerSphere->SetTransform(NMMatrix::Scaling(0.5f, 0.5f, 0.5f));
        world.objects.push_back(innerSphere);

        return world;
    }

    inline NMPointLight GetPointLight(std::size_t index) const { return pointLights[index]; }

    inline std::size_t GetPointLightCount() const { return pointLights.size(); }

    inline void AddLight(const NMPointLight& light) { pointLights.push_back(light); }

    inline void SetLight(std::size_t index, const NMPointLight& light) { pointLights[index] = light; }

    inline std::shared_ptr<INMIntersectionObject> GetObject(std::size_t index) const { return objects[index]; }

    inline std::size_t GetObjectCount() const { return objects.size(); }

    inline void AddObject(std::shared_ptr<INMIntersectionObject> object) { objects.push_back(object); }

    SNMIntersectionList Intersect(const NMRay& ray) const
    {
        SNMIntersectionList intersections;

        for (std::shared_ptr<INMIntersectionObject> object : objects)
        {
            intersections.Append(object->Intersect(ray));
        }

        intersections.Sort();

        return intersections;
    }

    SNMIntersectionState PrepareState(const SNMIntersection& intersection, const NMRay& ray) const
    {
        SNMIntersectionState state(intersection);

        // Precompute some useful values
        state.point = ray.Position(state.t);
        state.eyeVector = -ray.GetDirection();
        state.normalVector = state.object->NormalAt(state.point);

        if (state.normalVector.DotProduct(state.eyeVector) < 0.0f)
        {
            state.isInside = true;
            state.normalVector = -state.normalVector;
        }

        return state;
    }

    NMColor ShadeHit(const SNMIntersectionState& state) const
    {
        NMColor color = NMColor(0.0f, 0.0f, 0.0f);

        for (NMPointLight light : pointLights)
        {
            color += state.object->GetMaterial().Lighting(light, state.point, state.eyeVector, state.normalVector);
        }

        return color;
    }

    NMColor ColorAt(const NMRay& ray) const
    {
        SNMIntersectionList intersections = Intersect(ray);
        SNMIntersection* intersection = intersections.Hit();

        if (intersection == nullptr || intersection->object == nullptr)
        {
            return NMColor(0.0f, 0.0f, 0.0f);
        }

        SNMIntersectionState state = PrepareState(*intersection, ray);

        return ShadeHit(state);
    }

protected:

    std::vector<NMPointLight> pointLights;
    std::vector<std::shared_ptr<INMIntersectionObject>> objects;
};

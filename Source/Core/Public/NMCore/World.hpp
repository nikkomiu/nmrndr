#pragma once

#include <memory>
#include <vector>

#include "Color.hpp"
#include "Light/Point.hpp"
#include "NMM/Point.hpp"
#include "NMM/Vector.hpp"
#include "Primitive/Sphere.hpp"
#include "RT/IntersectionList.hpp"
#include "RT/IntersectionState.hpp"

struct SNMWorldSettings
{
public:

    /**
     * @brief The maximum number of reflections to trace per ray.
     * This value is used to prevent infinite recursion when tracing reflections.
     */
    uint8_t ReflectionTraceDepth = 5;

    /**
     * @brief
     */
    uint8_t X = 1;
};

class NMWorld
{
public:

    NMWorld(SNMWorldSettings worldSettings = SNMWorldSettings()) : worldSettings(worldSettings) {}

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

    inline void SetLight(std::size_t index, const NMPointLight& light)
    {
        if (index >= pointLights.size())
        {
            return;
        }

        pointLights[index] = light;
    }

    inline std::shared_ptr<NMPrimitiveBase> GetObject(std::size_t index) const { return objects[index]; }

    inline std::size_t GetObjectCount() const { return objects.size(); }

    inline void AddObject(std::shared_ptr<NMPrimitiveBase> object) { objects.push_back(object); }

    SNMIntersectionList Intersect(const NMRay& ray) const
    {
        SNMIntersectionList intersections;

        for (std::shared_ptr<NMPrimitiveBase> object : objects)
        {
            intersections.Add(object->Intersect(ray));
        }

        intersections.Sort();

        return intersections;
    }

    bool IsShadowed(const NMPoint& point) const
    {
        // TODO: support multiple lights (pass the light in as a reference)
        NMVector vector = pointLights[0].GetPosition() - point;
        float distance = vector.Magnitude();
        NMVector direction = vector.Normalized();

        NMRay ray(point, direction);
        SNMIntersectionList intersections = Intersect(ray);

        SNMIntersection* intersection = intersections.Hit();

        if (intersection == nullptr || intersection->t >= distance)
        {
            return false;
        }

        return true;
    }

    NMColor ShadeHit(const SNMIntersectionState& state, uint8_t remainingReflections) const
    {
        NMColor surfaceColor = NMColor(0.0f, 0.0f, 0.0f);

        bool isShadowed = IsShadowed(state.overPoint);
        for (NMPointLight light : pointLights)
        {
            surfaceColor += state.object->GetMaterial().Lighting(*state.object, light, state.point, state.eyeVector,
                                                                 state.normalVector, isShadowed);
        }

        NMColor reflectedColor = ReflectedColor(state, remainingReflections);

        return surfaceColor + reflectedColor;
    }

    NMColor ReflectedColor(const SNMIntersectionState& state, uint8_t remainingReflections) const
    {
        if (remainingReflections == 0)
        {
            return NMColor(0.0f, 0.0f, 0.0f);
        }

        float reflectiveValue = state.object->GetMaterial().GetReflective();
        if (reflectiveValue == 0.0f)
        {
            return NMColor(0.0f, 0.0f, 0.0f);
        }

        NMRay ray(state.overPoint, state.reflectVector);
        NMColor color = ColorAt(ray, remainingReflections - 1);

        return color * reflectiveValue;
    }

    inline NMColor ColorAt(const NMRay& ray) const { return ColorAt(ray, worldSettings.ReflectionTraceDepth); }

protected:

    SNMWorldSettings worldSettings;

    std::vector<NMPointLight> pointLights;
    std::vector<std::shared_ptr<NMPrimitiveBase>> objects;

    NMColor ColorAt(const NMRay& ray, uint8_t remainingReflections) const
    {
        SNMIntersectionList intersections = Intersect(ray);
        SNMIntersection* intersection = intersections.Hit();

        if (intersection == nullptr)
        {
            return NMColor(0.0f, 0.0f, 0.0f);
        }

        SNMIntersectionState state = SNMIntersectionState(*intersection, ray);

        return ShadeHit(state, remainingReflections);
    }
};

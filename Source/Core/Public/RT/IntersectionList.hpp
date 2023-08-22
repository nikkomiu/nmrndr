#pragma once

#include <algorithm>
#include <set>
#include <vector>

#include "RT/Intersection.hpp"

class SNMIntersectionList
{
public:

    SNMIntersectionList() = default;
    SNMIntersectionList(const std::vector<SNMIntersection>& initialIntersections) : intersections(initialIntersections)
    {
    }

    inline bool IsSorted() const { return isSorted; }
    inline std::size_t Size() const { return intersections.size(); }

    inline const SNMIntersection& operator[](std::size_t index) const { return intersections[index]; }

    inline void Add(const SNMIntersection& intersection)
    {
        intersections.push_back(intersection);
        isSorted = false;
    }

    inline void Add(std::vector<SNMIntersection> newIntersections)
    {
        intersections.insert(intersections.end(), newIntersections.begin(), newIntersections.end());
        isSorted = false;
    }

    SNMIntersection* Hit()
    {
        if (!isSorted)
        {
            Sort();
        }

        if (intersections.empty() || intersections[0].t < 0)
        {
            return nullptr;
        }

        return &intersections[0];
    }

    void Sort()
    {
        if (isSorted)
        {
            return;
        }

        std::sort(intersections.begin(), intersections.end(),
                  [](const SNMIntersection& a, const SNMIntersection& b)
                  {
                      if (a.t >= 0 && b.t >= 0)
                      {
                          return a.t < b.t;
                      }
                      else if (a.t >= 0 && b.t < 0)
                      {
                          return true;
                      }
                      else
                      {
                          return false;
                      }
                  });
        isSorted = true;
    }

protected:

    bool isSorted = false;
    std::vector<SNMIntersection> intersections;
};

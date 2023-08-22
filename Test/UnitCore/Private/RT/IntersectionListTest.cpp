#include <gtest/gtest.h>

#include "Primitive/Sphere.hpp"
#include "RT/Intersection.hpp"
#include "RT/IntersectionList.hpp"

class IntersectionListTest : public ::testing::Test
{
};

// Scenario: Intersect sets the object on the intersection
TEST_F(IntersectionListTest, IntersectionListCreation)
{
    // Given
    NMSphere sphere1 = NMSphere();
    NMSphere sphere2 = NMSphere();
    SNMIntersection intersection1 = SNMIntersection(1.0f, &sphere1);
    SNMIntersection intersection2 = SNMIntersection(2.0f, &sphere2);

    // When
    SNMIntersectionList intersectionList = SNMIntersectionList({ intersection1, intersection2 });

    // Then
    EXPECT_EQ(intersectionList.Size(), 2);
    EXPECT_EQ(intersectionList[0].t, 1.0f);
    EXPECT_EQ(intersectionList[0].object, (void*)&sphere1);
    EXPECT_EQ(intersectionList[1].t, 2.0f);
    EXPECT_EQ(intersectionList[1].object, (void*)&sphere2);
}

// Scenario: The hit, when all intersections have positive t
TEST_F(IntersectionListTest, Hit_PositiveT)
{
    // Given
    NMSphere sphere1 = NMSphere();
    NMSphere sphere2 = NMSphere();
    SNMIntersection intersection1 = SNMIntersection(1.0f, &sphere1);
    SNMIntersection intersection2 = SNMIntersection(2.0f, &sphere2);
    SNMIntersectionList intersectionList = SNMIntersectionList({ intersection1, intersection2 });

    // When
    SNMIntersection* hit = intersectionList.Hit();

    // Then
    EXPECT_EQ(*hit, intersection1);
}

// Scenario: The hit, when some intersections have negative t
TEST_F(IntersectionListTest, Hit_NegativeT)
{
    // Given
    NMSphere sphere1 = NMSphere();
    NMSphere sphere2 = NMSphere();
    SNMIntersection intersection1 = SNMIntersection(-1.0f, &sphere1);
    SNMIntersection intersection2 = SNMIntersection(1.0f, &sphere2);
    SNMIntersectionList intersectionList = SNMIntersectionList({ intersection1, intersection2 });

    // When
    SNMIntersection* hit = intersectionList.Hit();

    // Then
    EXPECT_EQ(*hit, intersection2);
}

// Scenario: The hit, when all intersections have negative t
TEST_F(IntersectionListTest, Hit_AllNegativeT)
{
    // Given
    NMSphere sphere1 = NMSphere();
    NMSphere sphere2 = NMSphere();
    SNMIntersection intersection1 = SNMIntersection(-2.0f, &sphere1);
    SNMIntersection intersection2 = SNMIntersection(-1.0f, &sphere2);
    SNMIntersectionList intersectionList = SNMIntersectionList({ intersection1, intersection2 });

    // When
    SNMIntersection* hit = intersectionList.Hit();

    // Then
    EXPECT_EQ(hit, nullptr);
}

// Scenario: The hit is always the lowest nonnegative intersection
TEST_F(IntersectionListTest, Hit_LowestNonnegativeT)
{
    // Given
    NMSphere sphere1 = NMSphere();
    NMSphere sphere2 = NMSphere();
    NMSphere sphere3 = NMSphere();
    SNMIntersection intersection1 = SNMIntersection(5.0f, &sphere1);
    SNMIntersection intersection2 = SNMIntersection(7.0f, &sphere2);
    SNMIntersection intersection3 = SNMIntersection(-3.0f, &sphere3);
    SNMIntersection intersection4 = SNMIntersection(2.0f, &sphere3);
    SNMIntersectionList intersectionList = SNMIntersectionList({ intersection1, intersection2, intersection3, intersection4 });

    // When
    SNMIntersection* hit = intersectionList.Hit();

    // Then
    EXPECT_EQ(*hit, intersection4);
}

TEST_F(IntersectionListTest, Add)
{
    // Given
    NMSphere sphere1 = NMSphere();
    NMSphere sphere2 = NMSphere();
    SNMIntersection intersection1 = SNMIntersection(1.0f, &sphere1);
    SNMIntersection intersection2 = SNMIntersection(2.0f, &sphere2);
    SNMIntersectionList intersectionList = SNMIntersectionList({ intersection1 });

    // When
    intersectionList.Add(intersection2);

    // Then
    EXPECT_EQ(intersectionList.Size(), 2);
    EXPECT_EQ(intersectionList[0].t, 1.0f);
    EXPECT_EQ(intersectionList[0].object, (void*)&sphere1);
    EXPECT_EQ(intersectionList[1].t, 2.0f);
    EXPECT_EQ(intersectionList[1].object, (void*)&sphere2);
}

TEST_F(IntersectionListTest, Append)
{
    // Given
    NMSphere sphere1 = NMSphere();
    NMSphere sphere2 = NMSphere();
    NMSphere sphere3 = NMSphere();
    SNMIntersection intersection1 = SNMIntersection(1.0f, &sphere1);
    SNMIntersection intersection2 = SNMIntersection(2.0f, &sphere2);
    SNMIntersection intersection3 = SNMIntersection(3.0f, &sphere3);
    SNMIntersectionList intersectionList = SNMIntersectionList({ intersection1 });

    // When
    intersectionList.Add({ intersection2, intersection3 });

    // Then
    EXPECT_EQ(intersectionList.Size(), 3);
    EXPECT_EQ(intersectionList[0].t, 1.0f);
    EXPECT_EQ(intersectionList[0].object, (void*)&sphere1);
    EXPECT_EQ(intersectionList[1].t, 2.0f);
    EXPECT_EQ(intersectionList[1].object, (void*)&sphere2);
    EXPECT_EQ(intersectionList[2].t, 3.0f);
    EXPECT_EQ(intersectionList[2].object, (void*)&sphere3);
}

TEST_F(IntersectionListTest, Sort)
{
    // Given
    NMSphere sphere1 = NMSphere();
    NMSphere sphere2 = NMSphere();
    NMSphere sphere3 = NMSphere();
    SNMIntersection intersection1 = SNMIntersection(5.0f, &sphere1);
    SNMIntersection intersection2 = SNMIntersection(7.0f, &sphere2);
    SNMIntersection intersection3 = SNMIntersection(-3.0f, &sphere3);
    SNMIntersection intersection4 = SNMIntersection(2.0f, &sphere3);
    SNMIntersectionList intersectionList = SNMIntersectionList({ intersection1, intersection2, intersection3, intersection4 });

    // When
    intersectionList.Sort();

    // Then
    EXPECT_EQ(intersectionList.IsSorted(), true);
    EXPECT_EQ(intersectionList.Size(), 4);
    EXPECT_EQ(intersectionList[0].t, 2.0f);
    EXPECT_EQ(intersectionList[0].object, (void*)&sphere3);
    EXPECT_EQ(intersectionList[1].t, 5.0f);
    EXPECT_EQ(intersectionList[1].object, (void*)&sphere1);
    EXPECT_EQ(intersectionList[2].t, 7.0f);
    EXPECT_EQ(intersectionList[2].object, (void*)&sphere2);
    EXPECT_EQ(intersectionList[3].t, -3.0f);
}

TEST_F(IntersectionListTest, Sort_Sorted)
{
    // Given
    NMSphere sphere1 = NMSphere();
    NMSphere sphere2 = NMSphere();
    NMSphere sphere3 = NMSphere();
    SNMIntersection intersection1 = SNMIntersection(5.0f, &sphere1);
    SNMIntersection intersection2 = SNMIntersection(7.0f, &sphere2);
    SNMIntersection intersection3 = SNMIntersection(2.0f, &sphere3);
    SNMIntersection intersection4 = SNMIntersection(-3.0f, &sphere3);
    SNMIntersectionList intersectionList = SNMIntersectionList({ intersection1, intersection2, intersection3, intersection4 });

    // When
    intersectionList.Sort();
    EXPECT_EQ(intersectionList.IsSorted(), true);
    intersectionList.Sort();
    EXPECT_EQ(intersectionList.IsSorted(), true);

    // Then
    EXPECT_EQ(intersectionList.Size(), 4);
    EXPECT_EQ(intersectionList[0].t, 2.0f);
    EXPECT_EQ(intersectionList[0].object, (void*)&sphere3);
    EXPECT_EQ(intersectionList[1].t, 5.0f);
    EXPECT_EQ(intersectionList[1].object, (void*)&sphere1);
    EXPECT_EQ(intersectionList[2].t, 7.0f);
    EXPECT_EQ(intersectionList[2].object, (void*)&sphere2);
    EXPECT_EQ(intersectionList[3].t, -3.0f);
}

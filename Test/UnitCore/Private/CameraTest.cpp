#include <gtest/gtest.h>

#include <math.h>

#include "NMCore/Camera.hpp"
#include "NMCore/World.hpp"

class NMCameraTest : public ::testing::Test
{
};

// Scenario: Constructing a camera
TEST_F(NMCameraTest, Construct)
{
    // Given
    int hSize = 160;
    int vSize = 120;
    float fov = M_PI / 2.0f;

    // When
    NMCamera camera(hSize, vSize, fov);

    // Then
    EXPECT_EQ(camera.GetHSize(), hSize);
    EXPECT_EQ(camera.GetVSize(), vSize);
    EXPECT_EQ(camera.GetFOV(), fov);
    EXPECT_EQ(camera.GetTransform(), NMMatrix::Identity4x4());
}

// Scenario: The pixel size for a horizontal canvas
TEST_F(NMCameraTest, PixelSizeHorizontal)
{
    // Given
    NMCamera camera(200, 125, M_PI / 2.0f);

    // Then
    EXPECT_FLOAT_EQ(camera.GetPixelSize(), 0.01f);
}

// Scenario: The pixel size for a vertical canvas
TEST_F(NMCameraTest, PixelSizeVertical)
{
    // Given
    NMCamera camera(125, 200, M_PI / 2.0f);

    // Then
    EXPECT_FLOAT_EQ(camera.GetPixelSize(), 0.01f);
}

// Scenario: Constructing a ray through the center of the canvas
TEST_F(NMCameraTest, RayThroughCenter)
{
    // Given
    NMCamera camera(201, 101, M_PI / 2.0f);

    // When
    NMRay ray = camera.RayForPixel(100, 50);

    // Then
    EXPECT_EQ(ray.GetOrigin(), NMPoint(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(ray.GetDirection(), NMVector(0.0f, 0.0f, -1.0f));
}

// Scenario: Constructing a ray through a corner of the canvas
TEST_F(NMCameraTest, RayThroughCorner)
{
    // Given
    NMCamera camera(201, 101, M_PI / 2.0f);

    // When
    NMRay ray = camera.RayForPixel(0, 0);

    // Then
    EXPECT_EQ(ray.GetOrigin(), NMPoint(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(ray.GetDirection(), NMVector(0.665186f, 0.332593f, -0.668512f));
}

// Scenario: Constructing a ray when the camera is transformed
TEST_F(NMCameraTest, RayWhenTransformed)
{
    // Given
    NMCamera camera(201, 101, M_PI / 2.0f);
    camera.SetTransform(NMMatrix::RotationY(M_PI / 4.0f) * NMMatrix::Translation(0.0f, -2.0f, 5.0f));

    // When
    NMRay ray = camera.RayForPixel(100, 50);

    // Then
    EXPECT_EQ(ray.GetOrigin(), NMPoint(0.0f, 2.0f, -5.0f));
    EXPECT_EQ(ray.GetDirection(), NMVector(sqrtf(2.0f) / 2.0f, 0.0f, -sqrtf(2.0f) / 2.0f));
}

// Scenario: Rendering a world with a camera
TEST_F(NMCameraTest, Render)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMCamera camera(11, 11, M_PI / 2.0f);
    NMPoint from(0.0f, 0.0f, -5.0f);
    NMPoint to(0.0f, 0.0f, 0.0f);
    NMVector up(0.0f, 1.0f, 0.0f);
    camera.SetTransform(NMMatrix::ViewTransform(from, to, up));

    // When
    NMCanvas canvas = camera.Render(world);
    NMColor pixelColor = canvas.ReadPixel(5, 5);

    // Then
    EXPECT_EQ(canvas.ReadPixel(5, 5), NMColor(0.380661f, 0.475827f, 0.285496f));
}

// Scenario: Render uses multiple threads
TEST_F(NMCameraTest, RenderMultiThreaded)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMCamera camera(11, 11, M_PI / 2.0f);
    NMPoint from(0.0f, 0.0f, -5.0f);
    NMPoint to(0.0f, 0.0f, 0.0f);
    NMVector up(0.0f, 1.0f, 0.0f);
    camera.SetTransform(NMMatrix::ViewTransform(from, to, up));

    // When
    NMCanvas canvas = camera.Render(world, 4);
    NMColor pixelColor = canvas.ReadPixel(5, 5);

    // Then
    EXPECT_EQ(canvas.ReadPixel(5, 5), NMColor(0.380661f, 0.475827f, 0.285496f));
}

// Scenario: Render throws an error if already rendering
TEST_F(NMCameraTest, Render_WhenAlreadyRendering)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMCamera camera(11, 11, M_PI / 2.0f);
    NMPoint from(0.0f, 0.0f, -5.0f);
    NMPoint to(0.0f, 0.0f, 0.0f);
    NMVector up(0.0f, 1.0f, 0.0f);
    camera.SetTransform(NMMatrix::ViewTransform(from, to, up));

    // When
    std::thread renderThread([&camera, &world]
    {
        camera.Render(world);
    });

    try
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        camera.Render(world);
        FAIL() << "Expected std::runtime_error, but no exception was thrown";
    }
    catch (const std::runtime_error& err)
    {
        EXPECT_EQ(err.what(), std::string("Camera is already rendering"));
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error, but a different exception was thrown";
    }

    renderThread.join();

    // Then
    EXPECT_TRUE(true);
}

// Scenario: Render can be canceled
TEST_F(NMCameraTest, RenderCancel)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMCamera camera(11, 11, M_PI / 2.0f);
    NMPoint from(0.0f, 0.0f, -5.0f);
    NMPoint to(0.0f, 0.0f, 0.0f);
    NMVector up(0.0f, 1.0f, 0.0f);
    camera.SetTransform(NMMatrix::ViewTransform(from, to, up));

    // When
    std::thread renderThread([&camera, &world]
    {
        camera.Render(world);
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    camera.StopRender();
    renderThread.join();

    // Then
    EXPECT_TRUE(true);
}

// Scenario: StopRender can be called even when not rendering
TEST_F(NMCameraTest, RenderCancel_WhenNotRendering)
{
    // Given
    NMWorld world = NMWorld::Default();
    NMCamera camera(11, 11, M_PI / 2.0f);
    NMPoint from(0.0f, 0.0f, -5.0f);
    NMPoint to(0.0f, 0.0f, 0.0f);
    NMVector up(0.0f, 1.0f, 0.0f);
    camera.SetTransform(NMMatrix::ViewTransform(from, to, up));

    // When
    camera.StopRender();

    // Then
    EXPECT_TRUE(true);
}

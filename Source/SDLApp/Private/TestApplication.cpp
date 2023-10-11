#include "TestApplication.hpp"

#include <NMCore/Light/Point.hpp>
#include <NMCore/Primitive/Plane.hpp>
#include <NMCore/Primitive/Sphere.hpp>

TestApplication::TestApplication(std::size_t width, std::size_t height) : Application(width, height) {}

NMWorld TestApplication::LoadWorld()
{
    NMWorld world = NMWorld();

    // Floor
    std::shared_ptr<NMSphere> floor = std::make_shared<NMSphere>();
    floor->SetTransform(NMMatrix::Scaling(10.0f, 0.01f, 10.0f));
    NMMaterial floorMat = NMMaterial();
    floorMat.SetColor(NMColor(1.0f, 0.9f, 0.9f));
    floorMat.SetSpecular(0.0f);
    floor->SetMaterial(floorMat);
    world.AddObject(floor);

    float halfPi = static_cast<float>(M_PI / 2.0f);
    float quarterPi = static_cast<float>(M_PI / 4.0f);

    // Left wall
    std::shared_ptr<NMPlane> leftWall = std::make_shared<NMPlane>();
    leftWall->SetTransform(NMMatrix::Translation(0.0f, 0.0f, 5.0f) * NMMatrix::RotationY(-quarterPi)
                           * NMMatrix::RotationX(halfPi));
    leftWall->SetMaterial(floorMat);
    world.AddObject(leftWall);

    // Right wall
    std::shared_ptr<NMPlane> rightWall = std::make_shared<NMPlane>();
    rightWall->SetTransform(NMMatrix::Translation(0.0f, 0.0f, 5.0f) * NMMatrix::RotationY(quarterPi)
                            * NMMatrix::RotationX(halfPi));
    rightWall->SetMaterial(floorMat);
    world.AddObject(rightWall);

    // Middle Sphere
    std::shared_ptr<NMSphere> middle = std::make_shared<NMSphere>();
    middle->SetTransform(NMMatrix::Translation(-0.5f, 1.0f, 0.5f));
    NMMaterial middleMat = NMMaterial();
    middleMat.SetColor(NMColor(0.1f, 1.0f, 0.5f));
    middleMat.SetDiffuse(0.7f);
    middleMat.SetSpecular(0.3f);
    middle->SetMaterial(middleMat);
    world.AddObject(middle);

    // Right Sphere
    std::shared_ptr<NMSphere> right = std::make_shared<NMSphere>();
    right->SetTransform(NMMatrix::Translation(1.5f, 0.5f, -0.5f) * NMMatrix::Scaling(0.5f, 0.5f, 0.5f));
    NMMaterial rightMat = NMMaterial();
    rightMat.SetColor(NMColor(0.5f, 1.0f, 0.1f));
    rightMat.SetDiffuse(0.7f);
    rightMat.SetSpecular(0.3f);
    right->SetMaterial(rightMat);
    world.AddObject(right);

    // Left Sphere
    std::shared_ptr<NMSphere> left = std::make_shared<NMSphere>();
    left->SetTransform(NMMatrix::Translation(-1.5f, 0.33f, -0.75f) * NMMatrix::Scaling(0.33f, 0.33f, 0.33f));
    NMMaterial leftMat = NMMaterial();
    leftMat.SetColor(NMColor(1.0f, 0.8f, 0.1f));
    leftMat.SetDiffuse(0.7f);
    leftMat.SetSpecular(0.3f);
    left->SetMaterial(leftMat);
    world.AddObject(left);

    // Light
    NMPointLight light = NMPointLight(NMPoint(-10.0f, 10.0f, -10.0f), NMColor(1.0f, 1.0f, 1.0f));
    world.AddLight(light);

    return world;
}

NMCamera TestApplication::LoadScene()
{
    NMCamera camera = NMCamera(windowWidth, windowHeight, static_cast<float>(M_PI / 3.0f));
    camera.SetTransform(
        NMMatrix::ViewTransform(NMPoint(0.0f, 1.5f, -5.0f), NMPoint(0.0f, 1.0f, 0.0f), NMVector(0.0f, 1.0f, 0.0f)));

    return camera;
}

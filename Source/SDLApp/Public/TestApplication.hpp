#pragma once

#include <NMCore/Application.hpp>

class TestApplication : public Application
{
public:

    TestApplication(std::size_t width, std::size_t height);

    virtual NMWorld LoadWorld();
    virtual NMCamera LoadScene();
};

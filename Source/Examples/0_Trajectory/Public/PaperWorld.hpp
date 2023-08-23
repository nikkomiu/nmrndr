#pragma once

#include "NMCore/Canvas.hpp"
#include "World.hpp"

class NMPaperWorld : public NMWorld
{
public:

    NMPaperWorld(const NMEnvironment& environment, NMCanvas canvas) : NMWorld(environment), canvas(canvas) {}

    virtual bool ShouldEndPlay() override;

    virtual void OnBeginPlay() override;

    virtual void Draw() override;

    virtual void OnEndPlay() override;

protected:

    NMCanvas canvas;
};

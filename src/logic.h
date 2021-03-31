#pragma once
#include "yoshix_fix_function.h"
using namespace gfx;

struct SEntity
{
    BHandle pMesh;
    float aPosition[3];
    float aScale[3];
    float aRotation[3];
    float aWorldMatrix[16];
};

// -----------------------------------------------------------------------------
// Individual functions for this applications game logic
// -----------------------------------------------------------------------------
//IApplication SetupGame(SEntity aBorders[4], SEntity sSnakeHead);
void EnlargeSnake();
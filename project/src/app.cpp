#pragma once
#include "yoshix_fix_function.h"
#include "app.h"

CApplication::CApplication()
{
}

// -----------------------------------------------------------------------------

CApplication::~CApplication()
{
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnStartup()
{
    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnShutdown()
{
    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateMeshes()
{
    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseMeshes()
{
    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnResize(int _Width, int _Height)
{
    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnUpdate()
{
    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnFrame()
{
    return true;
}
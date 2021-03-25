#pragma once
#include "yoshix_fix_function.h"
using namespace gfx;

class CApplication : public IApplication
{
public:

    CApplication();
    virtual ~CApplication();

private:

    //float fieldOfViewY;					// Vertical view angle of the camera


private:
    // -----------------------------------------------------------------------------
    /*
        individual functions for this application
    */

    //          [ ... ]


    // -----------------------------------------------------------------------------
    /*
        yoshix functions
    */
    virtual bool InternOnStartup();
    virtual bool InternOnShutdown();
    virtual bool InternOnCreateMeshes();
    virtual bool InternOnReleaseMeshes();
    virtual bool InternOnResize(int _Width, int _Height);
    virtual bool InternOnUpdate();
    virtual bool InternOnFrame();
};

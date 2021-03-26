#pragma once
#include "yoshix_fix_function.h"
#include <vector>
using namespace gfx;

struct SEntity
{
    BHandle* m_pMesh;
    float m_PositionX;
    float m_PositionY;
    float m_Rotation;
    // float worldMatrix[16];
};


class CApplication : public IApplication
{
public:

    CApplication();
    virtual ~CApplication();

private:

    float m_FieldOfViewY;					// Vertical view angle of the camera

    BHandle m_pCubeMesh;
    BHandle m_pCubeTexture;

    // entities
    std::vector<SEntity> vSnake;	// for dynamic saving of cube entities 
    SEntity BorderBox[4];           // array for 

    // -----------------------------------------------------------------------------
    // camera perspective variables
    // -----------------------------------------------------------------------------
    float m_CameraPosition[3];
    float m_CameraTarget[3];
    float m_CameraUp[3];

private:
    // -----------------------------------------------------------------------------
    // individual functions for this application
    // -----------------------------------------------------------------------------
    void EnlargeSnake();

    // -----------------------------------------------------------------------------
    //  yoshix functions
    // -----------------------------------------------------------------------------
    virtual bool InternOnStartup();
    virtual bool InternOnShutdown();
    virtual bool InternOnCreateMeshes();
    virtual bool InternOnReleaseMeshes();
    virtual bool InternOnResize(int _Width, int _Height);
    virtual bool InternOnUpdate();
    virtual bool InternOnFrame();
};

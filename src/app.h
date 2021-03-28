#pragma once
#include "yoshix_fix_function.h"
#include <vector>
using namespace gfx;

struct SEntity
{
    BHandle* m_pMesh;
    float m_Position[3];
    float m_Scale[3];
    float m_Rotation[3];
    float WorldMatrix[16];
};


class CApplication : public IApplication
{
public:

    CApplication();
    virtual ~CApplication();

private:

    float m_FieldOfViewY;			// Vertical view angle of the camera

    BHandle m_pCubeTexture;         // A pointer to a YoshiX texture, which is part of the material covering the cube.

    // meshes
    BHandle m_pCubeMesh;        // A pointer to a YoshiX mesh, which represents a single cube.
    BHandle m_pCubeMeshSnake;
    BHandle m_pCubeMeshBorders;

    /*
    // entities
    SEntity pSnakeHead;             // cube entity as head of the snake
    std::vector<SEntity> vSnake;	// for dynamic saving of cube entities 
    SEntity Borders;
    */

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
    
    void CreateCube(BHandle* _ppMesh, BHandle _pTexture, float _EdgeLength);
    void EnlargeSnake();

    // -----------------------------------------------------------------------------
    //  yoshix functions
    // -----------------------------------------------------------------------------
    virtual bool InternOnStartup();
    virtual bool InternOnShutdown();
    virtual bool InternOnCreateTextures();
    virtual bool InternOnReleaseTextures();
    virtual bool InternOnCreateMeshes();
    virtual bool InternOnReleaseMeshes();
    virtual bool InternOnResize(int _Width, int _Height);
    virtual bool InternOnUpdate();
    virtual bool InternOnFrame();
};

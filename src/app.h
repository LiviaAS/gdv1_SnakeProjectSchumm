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

    //textures
    BHandle m_pCubeTextureWhite;    // A pointer to a white YoshiX texture
    BHandle m_pCubeTextureCyan;     // A pointer to a cyan YoshiX texture

    // meshes
    BHandle m_pCubeMesh;            // A pointer to a YoshiX mesh, which represents a single cube.
    //BHandle m_pCubeMeshSnake;
    //BHandle m_pCubeMeshBorders;
    
    // entities
    SEntity pSnakeHead;             // A cube entity as head of the snake
    std::vector<SEntity> vSnake;	// A vector for dynamic saving of cube entities as snake-body
    SEntity Borders[4];             // An array for the game area's borders
    

    /* -----------------------------------------------------------------------------
    // camera perspective variables
    // -----------------------------------------------------------------------------
    float m_CameraPosition[3];
    float m_CameraTarget[3];
    float m_CameraUp[3];
    */

private:
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

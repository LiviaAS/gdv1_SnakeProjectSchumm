#pragma once
#include "yoshix_fix_function.h"
#include "logic.h"
#include <vector>
using namespace gfx;

const float FIELD_SIZE = 100.0f;            // Size for width AND height
const float BLOCK_SIZE = 1.0f;              // Size for one block of 100x100 grid

class CApplication : public IApplication
{
public:

    CApplication();
    virtual ~CApplication();

private:

    float m_FieldOfViewY;			// Vertical view angle of the camera

    // Textures
    BHandle m_pCubeTextureWhite;    // A pointer to a white YoshiX texture
    BHandle m_pCubeTextureCyan;     // A pointer to a cyan YoshiX texture

    // Meshes
    BHandle m_pCubeMeshWhite;       // A pointer to a YoshiX mesh, which represents a single cube in white
    BHandle m_pCubeMeshCyan;        // A pointer to a YoshiX mesh, which represents a single cube in cyan
    
    // Entities
    SEntity m_sSnakeHead;           // A cube entity as head of the snake
    std::vector<SEntity> m_vSnake;	// A vector for dynamic saving of cube entities as snake-body
    SEntity m_aBorders[4];          // An array for the game area's borders

    // Ascii keys
    const unsigned int UP_KEY = 38;
    const unsigned int DOWN_KEY = 40;
    const unsigned int LEFT_KEY = 37;
    const unsigned int RIGHT_KEY = 39;
    const unsigned int W_KEY = 87;
    const unsigned int A_KEY = 65;
    const unsigned int S_KEY = 83;
    const unsigned int D_KEY = 68;

private:
    // -----------------------------------------------------------------------------
    // Individual functions for this application
    // -----------------------------------------------------------------------------
    void SetupGame();

    // -----------------------------------------------------------------------------
    //  YoshiX functions
    // -----------------------------------------------------------------------------
    virtual bool InternOnStartup();                         // Setting up light and area
    virtual bool InternOnShutdown();                       
    virtual bool InternOnCreateTextures();
    virtual bool InternOnReleaseTextures();
    virtual bool InternOnCreateMeshes();
    virtual bool InternOnReleaseMeshes();                   
    virtual bool InternOnResize(int _Width, int _Height);   // Setting up the projection matrix
    virtual bool InternOnUpdate();                          // Setting up camera and view matrix
    virtual bool InternOnFrame();                           // Setting up meshes in the world and drawing them

    virtual bool InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown);
};

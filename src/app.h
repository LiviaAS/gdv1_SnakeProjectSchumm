#pragma once
#include "yoshix_fix_function.h"
#include <iostream>
#include <vector>
using namespace gfx;

const float BLOCK_SIZE = 1;         // Size for one block in grid
const int FIELD_SIZE = 30;          // Size for width AND height
const int MAX_SNAKELENGTH = FIELD_SIZE * FIELD_SIZE;

// Constant variables for direction adjustment
const unsigned int DIR_UP       = 1;
const unsigned int DIR_DOWN     = 2;
const unsigned int DIR_LEFT     = 3;
const unsigned int DIR_RIGHT    = 4;

// Ascii keys
const unsigned int UP_KEY       = 38;
const unsigned int DOWN_KEY     = 40;
const unsigned int LEFT_KEY     = 37;
const unsigned int RIGHT_KEY    = 39;
const unsigned int W_KEY        = 87;
const unsigned int A_KEY        = 65;
const unsigned int S_KEY        = 83;
const unsigned int D_KEY        = 68;

struct SEntity
{
    float aPosition[3];
    float aScale[3];
};

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
    BHandle m_pCubeTextureGreen;    // A pointer to a green YoshiX texture

    // Meshes
    BHandle m_pCubeMeshWhite;       // A pointer to a YoshiX mesh, which represents a single cube in white
    BHandle m_pCubeMeshCyan;        // A pointer to a YoshiX mesh, which represents a single cube in cyan
    BHandle m_pCubeMeshGreen;       // A pointer to a YoshiX mesh, which represents a single cube in green

    // Game Variables
    bool m_GameOver;                
    bool m_FoodHit;                 // Boolean needed for activation of new food block
    bool m_Collision;               // Boolean needed for collision detection
    int m_Direction;                // Variable needed for storing information about current snake direction 
    int m_MoveIterator;             // Iterator needed for adjusting the snake movements speed
    int m_BodyLength;               // Variable needed

    // Entities
    SEntity m_sSnakeHead;                                   // A cube entity as head of the snake
    SEntity m_aSnakeBody[MAX_SNAKELENGTH];                  // An array for storing the snakes body cube entities
    SEntity m_aSnakeBodyOld[MAX_SNAKELENGTH];               // An array to transfer old entities positions
    SEntity m_aBorders[4];                                  // An array for the game area's borders
    SEntity m_sFood;                                        // A cube entity as food block

private:
    // -----------------------------------------------------------------------------
    // Individual functions for this application
    // -----------------------------------------------------------------------------
    void SetupGame();                                       // General setup 
    void RandomFoodPosition();                              // Changing the food blocks position randomly
    void NavigateSnake();                                   // General navigation of the snake head, needs to be called every frame
    bool CheckCollision(SEntity _Entity1, SEntity _Entity2);// Function to check collision between 2 entities

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

#pragma once
#include "app.h"
#include "meshes.h"

CApplication::CApplication()
    : m_FieldOfViewY(60.0f)
    , m_pCubeMesh(nullptr)
    , m_pCubeTexture(nullptr)

    , m_CameraPosition()
    , m_CameraTarget()
{
    // camera perspective variables
    this->m_CameraUp[0] = 0.0f;
    this->m_CameraUp[1] = 1.0f;
    this->m_CameraUp[2] = 0.0f;
}

// -----------------------------------------------------------------------------

CApplication::~CApplication()
{
}


// -----------------------------------------------------------------------------
// individual functions for this application
// -----------------------------------------------------------------------------

void CApplication::EnlargeSnake()
{
    /*
* // save current cube in vector to be drawn
SEntity drawedCube = {
    &this->cubeMeshes[colorsIterator],
    this->cubePtr.position[0], this->cubePtr.position[1], this->cubePtr.position[2],
    this->cubePtr.scale[0], this->cubePtr.scale[1], this->cubePtr.scale[2],
    this->cubePtr.rotation[0], this->cubePtr.rotation[1], this->cubePtr.rotation[2]
};

this->cubeVector.push_back(drawedCube);
*/

}

// -----------------------------------------------------------------------------
//  yoshix functions
// -----------------------------------------------------------------------------

bool CApplication::InternOnStartup()
{
    // -----------------------------------------------------------------------------
    // Define the background color of the window. Colors are always 4D tuples,
    // whereas the components of the tuple represent the red, green, blue, and alpha 
    // channel. The alpha channel indicates the transparency of the color. A value
    // of 1 means the color is completely opaque. A value of 0 means the color is
    // completely transparent. The channels red, green, and blue also are values
    // 0..1 with 0 indicating the minimum intensity and 1 the maximum intensity.
    // -----------------------------------------------------------------------------
    float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f, };

    SetClearColor(ClearColor);

    /* -----------------------------------------------------------------------------
    // Define the position of the light source in 3D space. The fixed function 
    // pipeline of YoshiX only supports one light source.
    // -----------------------------------------------------------------------------
    float LightPosition[3] = { 0.0f, 0.0f, -1.0f, };

    SetLightPosition(LightPosition);

    */

    // -----------------------------------------------------------------------------
    // Define the ambient, diffuse, and specular color of the light source. 
    // -----------------------------------------------------------------------------
    float LightAmbientColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f, };
    float LightDiffuseColor[4] = { 0.6f, 0.6f, 0.6f, 1.0f, };
    float LightSpecularColor[4] = { 0.9f, 0.9f, 0.9f, 1.0f, };

    SetLightColor(LightAmbientColor, LightDiffuseColor, LightSpecularColor, 127);

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
    float ViewMatrix[16];

    GetViewMatrix(this->m_CameraPosition, this->m_CameraTarget, this->m_CameraUp, ViewMatrix);
    SetViewMatrix(ViewMatrix);

    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnFrame()
{
    return true;
}
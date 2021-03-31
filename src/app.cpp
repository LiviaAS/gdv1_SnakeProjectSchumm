#pragma once
#include "app.h"
#include "meshes.h"

CApplication::CApplication()
    : m_FieldOfViewY(60.0f)

	, m_pCubeMeshWhite(nullptr)
	, m_pCubeMeshCyan(nullptr)

	, m_pCubeTextureWhite(nullptr)
	, m_pCubeTextureCyan(nullptr)
{
	// -----------------------------------------------------------------------------
	// Initialize member variable entities
	// -----------------------------------------------------------------------------
	for (int i = 0; i < 4; i++)
	{
		this->m_aBorders[i] = {
		};
	};

	this->m_sSnakeHead = {
	};
}

// -----------------------------------------------------------------------------

CApplication::~CApplication()
{
}

// -----------------------------------------------------------------------------
// Individual functions for this application
// -----------------------------------------------------------------------------

void CApplication::SetupGame()
{

	// -----------------------------------------------------------------------------
	// Setting up game border boxes
	// -----------------------------------------------------------------------------
	this->m_aBorders[0] = {		// top border
		&this->m_pCubeMeshCyan,		// needed?
			0.0f				, FIELD_SIZE / 2	, 0.0f	,	// X- , Y- , Z- coordinates in the world
			FIELD_SIZE + 1.0f	, BLOCK_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
			0.0f				, 0.0f				, 0.0f	,	// X- , Y- , Z- rotation	
	};
	this->m_aBorders[1] = {		// right border
		&this->m_pCubeMeshCyan,		// needed?
			FIELD_SIZE / 2		, 0.0f				, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE			, FIELD_SIZE + 1.0f	, 0.01f	,	// X- , Y- , Z- coordinates for scaling
			0.0f				, 0.0f				, 0.0f	,	// X- , Y- , Z- rotation
	};
	this->m_aBorders[2] = {		// bottom border
		&this->m_pCubeMeshCyan,		// needed?
			0.0f				, -(FIELD_SIZE / 2)	, 0.0f	,	// X- , Y- , Z- coordinates in the world
			FIELD_SIZE + 1.0f	, BLOCK_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
			0.0f				, 0.0f				, 0.0f	,	// X- , Y- , Z- rotation
	};
	this->m_aBorders[3] = {		// left border
		&this->m_pCubeMeshCyan,		// needed?					
			-(FIELD_SIZE / 2)	, 0.0f				, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE			, FIELD_SIZE + 1.0f	, 0.01f	,	// X- , Y- , Z- coordinates for scaling
			0.0f				, 0.0f				, 0.0f	,	// X- , Y- , Z- rotation		
	};

	// -----------------------------------------------------------------------------
	// Setting up snake head entity
	// -----------------------------------------------------------------------------
	this->m_sSnakeHead = {
		&this->m_pCubeMeshWhite,	// needed?
			0.0f				, 0.0f				, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE			, BLOCK_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
			0.0f				, 0.0f				, 0.0f	,	// X- , Y- , Z- rotation		
	};
}

/* -----------------------------------------------------------------------------
// Individual functions for this applications game logic --> right now in logic.h
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


}

*/

// -----------------------------------------------------------------------------
//  YoshiX functions
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

	// -----------------------------------------------------------------------------
	// Define the position of the light source in 3D space. The fixed function 
	// pipeline of YoshiX only supports one light source.
	// -----------------------------------------------------------------------------
	float LightPosition[3] = { 0.0f, 0.0f, -100.0f, };

	SetLightPosition(LightPosition);

    // -----------------------------------------------------------------------------
    // Define the ambient, diffuse, and specular color of the light source. 
    // -----------------------------------------------------------------------------
    float LightAmbientColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f, };
    float LightDiffuseColor[4] = { 2.0f, 2.0f, 2.0f, 1.0f, };
    float LightSpecularColor[4] = { 0.9f, 0.9f, 0.9f, 1.0f, };

    SetLightColor(LightAmbientColor, LightDiffuseColor, LightSpecularColor, 127);

	// -----------------------------------------------------------------------------
	// Setup the game with border boxes and snake head
	// -----------------------------------------------------------------------------
	SetupGame();

    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnShutdown()
{
    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateTextures()
{
	// -----------------------------------------------------------------------------
	// Load an image from the given path and create a YoshiX texture representing
	// the image.
	// -----------------------------------------------------------------------------
	CreateTexture("..\\data\\color_weiﬂ.jpg", &m_pCubeTextureWhite);
	CreateTexture("..\\data\\rgb_cyan.png", &m_pCubeTextureCyan);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseTextures()
{
	// -----------------------------------------------------------------------------
	// Important to release the texture again when the application is shut down.
	// -----------------------------------------------------------------------------
	ReleaseTexture(m_pCubeTextureWhite);
	ReleaseTexture(m_pCubeTextureCyan);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateMeshes()
{
	CreateCube(&m_pCubeMeshWhite, m_pCubeTextureWhite, BLOCK_SIZE);
	CreateCube(&m_pCubeMeshCyan, m_pCubeTextureCyan, BLOCK_SIZE);

    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseMeshes()
{
	ReleaseMesh(m_pCubeMeshWhite);
	ReleaseMesh(m_pCubeMeshCyan);

    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnResize(int _Width, int _Height)
{
	float ProjectionMatrix[16];

	// -----------------------------------------------------------------------------
	// The projection matrix defines the size of the camera frustum. The YoshiX
	// camera has the shape of a pyramid with the eye position at the top of the
	// pyramid. The horizontal view angle is defined by the vertical view angle
	// and the ratio between window width and window height.
	// -----------------------------------------------------------------------------
	GetProjectionMatrix(m_FieldOfViewY, static_cast<float>(_Width) / static_cast<float>(_Height), 0.1f, 100.0f, ProjectionMatrix);

	SetProjectionMatrix(ProjectionMatrix);

    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnUpdate()
{
	float Eye[3];
	float At[3];
	float Up[3];

	float ViewMatrix[16];

	// -----------------------------------------------------------------------------
	// Define position and orientation of the camera in the world.
	// -----------------------------------------------------------------------------
	Eye[0] = this->m_sSnakeHead.aPosition[0];	At[0] = this->m_sSnakeHead.aPosition[0];	Up[0] = 0.0f;
	Eye[1] = this->m_sSnakeHead.aPosition[1];	At[1] = this->m_sSnakeHead.aPosition[1];	Up[1] = 1.0f;
	Eye[2] = -100.0f;							At[2] = this->m_sSnakeHead.aPosition[2];	Up[2] = 0.0f;

	GetViewMatrix(Eye, At, Up, ViewMatrix);

	SetViewMatrix(ViewMatrix);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnFrame()	
{
	/* -----------------------------------------------------------------------------
	*  LONG VERSION
	*  -----------------------------------------------------------------------------
	* 
	* float TranslationMatrix[16];
	* float RotationXMatrix[16];
	* float RotationYMatrix[16];
	* float RotationZMatrix[16];
	* float WorldMatrix[16];
	* 
	* // -----------------------------------------------------------------------------
	* // Set the position of the mesh in the world and draw it.
	* // -----------------------------------------------------------------------------
	* GetTranslationMatrix(0.0f, 0.0f, 0.0f, TranslationMatrix);
	* 
	* float m_AngleX = 0.0f;
	* float m_AngleY = 0.0f;
	* float m_AngleZ = 0.0f;
	* 
	* GetRotationXMatrix(m_AngleX, RotationXMatrix);
	* GetRotationYMatrix(m_AngleY, RotationYMatrix);
	* GetRotationZMatrix(m_AngleZ, RotationZMatrix);
	* 
	* m_AngleX = ::fmodf(m_AngleX + 0.002f, 360.0f);
	* m_AngleY = ::fmodf(m_AngleY + 0.002f, 360.0f);
	* m_AngleZ = ::fmodf(m_AngleZ + 0.002f, 360.0f);
	* 
	* MulMatrix(RotationZMatrix, RotationYMatrix, WorldMatrix);
	* MulMatrix(WorldMatrix, RotationXMatrix, WorldMatrix);
	* MulMatrix(WorldMatrix, TranslationMatrix, WorldMatrix);
	* 
	* SetWorldMatrix(WorldMatrix);
	* 
	* DrawMesh(m_pCubeMesh);
	* 
	* -----------------------------------------------------------------------------
    */
    
	//float PositionMatrix[16];
	float RoationMatrix[16];
	float ScaleMatrix[16];
    float WorldMatrix[16];

	// -----------------------------------------------------------------------------
	// Set snake head mesh in the world and draw in white
	// -----------------------------------------------------------------------------
	GetTranslationMatrix(m_sSnakeHead.aPosition[0], m_sSnakeHead.aPosition[1], m_sSnakeHead.aPosition[2], WorldMatrix);
	GetScaleMatrix(m_sSnakeHead.aScale[0], m_sSnakeHead.aScale[1], m_sSnakeHead.aScale[2], ScaleMatrix);
	MulMatrix(ScaleMatrix, WorldMatrix, WorldMatrix);
	SetWorldMatrix(WorldMatrix);

	DrawMesh(m_pCubeMeshWhite);
	
	// -----------------------------------------------------------------------------
	// Set border box meshes in the world and draw in cyan
	// -----------------------------------------------------------------------------
	for (int i = 0; i < 4; i++)
	{
		GetTranslationMatrix(m_aBorders[i].aPosition[0], m_aBorders[i].aPosition[1], m_aBorders[i].aPosition[2], WorldMatrix);
		GetScaleMatrix(m_aBorders[i].aScale[0], m_aBorders[i].aScale[1], m_aBorders[i].aScale[2], ScaleMatrix);
		MulMatrix(ScaleMatrix, WorldMatrix, WorldMatrix);
		SetWorldMatrix(WorldMatrix);
		
		DrawMesh(m_pCubeMeshCyan);
	}	

    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown)
{
	float CollisionDetectionBorder = FIELD_SIZE / 2 - 1.0f;

	// -----------------------------------------------------------------------------
	// Navigating the snake
	// -----------------------------------------------------------------------------
	if ((_Key == W_KEY || _Key == UP_KEY)		&& _IsKeyDown
												&& this->m_sSnakeHead.aPosition[1] < CollisionDetectionBorder	)
	{
		this->m_sSnakeHead.aPosition[1] += 1.0f;
	}

	if ((_Key == A_KEY || _Key == LEFT_KEY)		&& _IsKeyDown
												&& this->m_sSnakeHead.aPosition[0] > -CollisionDetectionBorder	)
	{
		this->m_sSnakeHead.aPosition[0] -= 1.0f;
	}

	if ((_Key == S_KEY || _Key == DOWN_KEY)		&& _IsKeyDown
												&& this->m_sSnakeHead.aPosition[1] > -CollisionDetectionBorder	)
	{
		this->m_sSnakeHead.aPosition[1] -= 1.0f;
	}

	if ((_Key == D_KEY || _Key == RIGHT_KEY)	&& _IsKeyDown
												&& this->m_sSnakeHead.aPosition[0] < CollisionDetectionBorder	)
	{
		this->m_sSnakeHead.aPosition[0] += 1.0f;
	}

	return true;
}
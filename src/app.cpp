#pragma once
#include "app.h"
#include "meshes.h"

CApplication::CApplication()
    : m_FieldOfViewY(60.0f)

	, m_GameOver(false)
	, m_FoodHit(false)
	, m_Collision(false)
	, m_Direction(0)
	, m_MoveIterator(0)
	, m_BodyLength(0)

	, m_pCubeMeshWhite(nullptr)
	, m_pCubeMeshCyan(nullptr)
	, m_pCubeMeshGreen(nullptr)

	, m_pCubeTextureWhite(nullptr)
	, m_pCubeTextureCyan(nullptr)
	, m_pCubeTextureGreen(nullptr)
{
	// -----------------------------------------------------------------------------
	// Initialize member variable entities.
	// -----------------------------------------------------------------------------
	for (int i = 0; i < 4; i++)
	{
		this->m_aBorders[i] = {
		};
	};

	this->m_sSnakeHead = {
	};

	for (int i = 0; i < (FIELD_SIZE*FIELD_SIZE); i++)
	{
		this->m_aSnakeBody[i] = {
		};
	};

	this->m_sFood = {
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
	// Setting up game border boxes.
	// -----------------------------------------------------------------------------
	// Top border
	this->m_aBorders[0] = {		
			FIELD_SIZE / 2		, FIELD_SIZE		, 0.0f	,	// X- , Y- , Z- coordinates in the world
			FIELD_SIZE			, BLOCK_SIZE / 2	, 0.01f	,	// X- , Y- , Z- coordinates for scaling
		//	0.0f				, 0.0f				, 0.0f	,	// X- , Y- , Z- rotation	
	};

	// Right border
	this->m_aBorders[1] = {		
			FIELD_SIZE			, FIELD_SIZE / 2	, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE / 2		, FIELD_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
		//	0.0f				, 0.0f				, 0.0f	,	// X- , Y- , Z- rotation
	};

	// Bottom border
	this->m_aBorders[2] = {		
			FIELD_SIZE / 2		, 0.0f				, 0.0f	,	// X- , Y- , Z- coordinates in the world
			FIELD_SIZE			, BLOCK_SIZE / 2	, 0.01f	,	// X- , Y- , Z- coordinates for scaling
		//	0.0f				, 0.0f				, 0.0f	,	// X- , Y- , Z- rotation
	};

	// Left border
	this->m_aBorders[3] = {		
			0.0f				, FIELD_SIZE / 2	, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE / 2		, FIELD_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
		//	0.0f				, 0.0f				, 0.0f	,	// X- , Y- , Z- rotation		
	};

	// -----------------------------------------------------------------------------
	// Setting up snake head entity.
	// -----------------------------------------------------------------------------
	this->m_sSnakeHead = {
			FIELD_SIZE / 2		, FIELD_SIZE / 2	, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE			, BLOCK_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
			//true				,								// Visibility	
	};

	// -----------------------------------------------------------------------------
	// Setting up first random food block.
	// -----------------------------------------------------------------------------
	RandomFoodPosition();
}

// -----------------------------------------------------------------------------

void CApplication::RandomFoodPosition()
{
	// -----------------------------------------------------------------------------
	// Generating random position for food block.
	// -----------------------------------------------------------------------------
	float X, Y;
	srand(time(0));
	/*
	if (this->m_sFood.aPosition[0] < 30)
	{
		X = 1 + (rand() % (FIELD_SIZE / 2));
	}
	else {
		X = (FIELD_SIZE / 2) + (rand() % (FIELD_SIZE - 1));
	}

	if (this->m_sFood.aPosition[1] < 30)
	{
		Y = 1 + (rand() % (FIELD_SIZE / 2));
	}
	else {
		Y = (FIELD_SIZE / 2) + (rand() % (FIELD_SIZE - 1));
	}
	*/

	int Range = FIELD_SIZE - 2;

	X = 1 + (rand() % Range);
	Y = 1 + (rand() % Range);

	// -----------------------------------------------------------------------------
	// Set food block coordinates.
	// -----------------------------------------------------------------------------
	this->m_sFood = {
			X					, Y					, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE			, BLOCK_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
	};
}

// -----------------------------------------------------------------------------

void CApplication::NavigateSnake(SEntity _CurrentPosition)
{
	// -----------------------------------------------------------------------------
	// Change snake head position according to the currently given direction 
	// on key event. Also check for collision with border boxes.
	// -----------------------------------------------------------------------------
	if (m_MoveIterator == 5)
	{
		if (m_Direction == DIR_UP)
		{
			if (this->m_sSnakeHead.aPosition[1] < (this->m_aBorders[0].aPosition[1] - BLOCK_SIZE))
			{
				this->m_sSnakeHead.aPosition[1] += BLOCK_SIZE;
			}
			else
			{
				m_Collision = true;
			}
		}

		else if (m_Direction == DIR_RIGHT)
		{
			if (this->m_sSnakeHead.aPosition[0] < (this->m_aBorders[1].aPosition[0] - BLOCK_SIZE))
			{
				this->m_sSnakeHead.aPosition[0] += BLOCK_SIZE;
			}
			else
			{
				m_Collision = true;
			}
		}

		else if (m_Direction == DIR_DOWN)
		{
			if (this->m_sSnakeHead.aPosition[1] > (this->m_aBorders[2].aPosition[1] + BLOCK_SIZE))
			{
				this->m_sSnakeHead.aPosition[1] -= BLOCK_SIZE;
			}
			else
			{
				m_Collision = true;
			}
		}

		else if (m_Direction == DIR_LEFT)
		{
			if (this->m_sSnakeHead.aPosition[0] > (this->m_aBorders[3].aPosition[0] + BLOCK_SIZE))
			{
				this->m_sSnakeHead.aPosition[0] -= BLOCK_SIZE;
			}
			else
			{
				m_Collision = true;
			}
		}

		m_MoveIterator = 0;
	}
	else
	{
		m_MoveIterator++;
	}

	// -----------------------------------------------------------------------------
	// Iterating through the snakes body array to follow its head. 
	// -----------------------------------------------------------------------------
	// This should assign the previous in chain cubes position values to the
	// the next cube but unfortunately doesn't work rather than keeps the arrays
	// entities in position 0.
	// -----------------------------------------------------------------------------
	if (m_BodyLength > 0)
	{
	// -----------------------------------------------------------------------------
	// Save snake head information in local Entity.
	// -----------------------------------------------------------------------------
		SEntity CurrentEntity = this->m_sSnakeHead;

		for (int i = 0; i < m_BodyLength; i++)
		{
			//std::cout << Entity.aPosition[0] << std::endl;
			this->m_aSnakeBody[i+1] = CurrentEntity;
			std::cout << "CurrentEntitiy position X is: " << CurrentEntity.aPosition[0] << std::endl;

			//CurrentEntity = this->m_aSnakeBody[i];
			std::cout << "CurrentEntitiy position Y is: " << CurrentEntity.aPosition[1] << std::endl;
			//std::cout << m_BodyLength;
		}

		//this->m_aSnakeBody[0] = this->m_sSnakeHead;
	}
	
	

	std::cout << std::endl;
}

// -----------------------------------------------------------------------------

bool CApplication::CheckCollision(SEntity _Entity1, SEntity _Entity2)
{
	// -----------------------------------------------------------------------------
	// Checking Collision between given 2 entities.
	// -----------------------------------------------------------------------------
	bool Collision = false;

	if (_Entity1.aPosition[0] == _Entity2.aPosition[0] && _Entity1.aPosition[1] == _Entity2.aPosition[1])
	{
		Collision = true;
	}
	
	return Collision;
}

// -----------------------------------------------------------------------------

void CApplication::EnlargeSnake()
{
	// -----------------------------------------------------------------------------
	// Adding 1 cube to the visible chain of the snakes body.
	// -----------------------------------------------------------------------------
	int i = 0;
	/*
	do 
	{

	} while (this->m_aSnakeBody->Visibility)
	
	for (int i = 0; i < (FIELD_SIZE * FIELD_SIZE); i++)
	{
		if
	}
	*/
}

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
	float LightPosition[3] = { 0.0f, 0.0f, -FIELD_SIZE, };

	SetLightPosition(LightPosition);

    // -----------------------------------------------------------------------------
    // Define the ambient, diffuse, and specular color of the light source. 
    // -----------------------------------------------------------------------------
    float LightAmbientColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f, };
    float LightDiffuseColor[4] = { 2.0f, 2.0f, 2.0f, 1.0f, };
    float LightSpecularColor[4] = { 0.9f, 0.9f, 0.9f, 1.0f, };

    SetLightColor(LightAmbientColor, LightDiffuseColor, LightSpecularColor, 127);

	// -----------------------------------------------------------------------------
	// Setup the game with border boxes and snake head.
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
	CreateTexture("..\\data\\color_weiß.jpg", &m_pCubeTextureWhite);
	CreateTexture("..\\data\\rgb_cyan.png", &m_pCubeTextureCyan);
	CreateTexture("..\\data\\rgb_green.png", &m_pCubeTextureGreen);

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
	ReleaseTexture(m_pCubeTextureGreen);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateMeshes()
{
	CreateCube(&m_pCubeMeshWhite, m_pCubeTextureWhite, BLOCK_SIZE);
	CreateCube(&m_pCubeMeshCyan, m_pCubeTextureCyan, BLOCK_SIZE);
	CreateCube(&m_pCubeMeshGreen, m_pCubeTextureGreen, BLOCK_SIZE);

    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseMeshes()
{
	ReleaseMesh(m_pCubeMeshWhite);
	ReleaseMesh(m_pCubeMeshCyan);
	ReleaseMesh(m_pCubeMeshGreen);

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
	Eye[0] = FIELD_SIZE / 2;	At[0] = FIELD_SIZE / 2;		Up[0] = 0.0f;
	Eye[1] = FIELD_SIZE / 2;	At[1] = FIELD_SIZE / 2;		Up[1] = 1.0f;
	Eye[2] = -FIELD_SIZE;		At[2] = 0.0f;				Up[2] = 0.0f;

	/* -----------------------------------------------------------------------------
	// Define position and orientation of the camera in the world.				 
	// -----------------------------------------------------------------------------
	Eye[0] = this->m_sSnakeHead.aPosition[0];	At[0] = this->m_sSnakeHead.aPosition[0];	Up[0] = 0.0f;
	Eye[1] = this->m_sSnakeHead.aPosition[1];	At[1] = this->m_sSnakeHead.aPosition[1];	Up[1] = 1.0f;
	Eye[2] = -FIELD_SIZE;						At[2] = this->m_sSnakeHead.aPosition[2];	Up[2] = 0.0f;
	// -----------------------------------------------------------------------------
	// NOTE: Is Working but very uneasy to watch because of the jumpy player movement 
	// -----------------------------------------------------------------------------
	*/

	GetViewMatrix(Eye, At, Up, ViewMatrix);

	SetViewMatrix(ViewMatrix);

	// -----------------------------------------------------------------------------
	// Change position of food block when hit and lengthen the snakes body.
	// -----------------------------------------------------------------------------
	m_FoodHit = CheckCollision(this->m_sSnakeHead, this->m_sFood);

	if (m_FoodHit)
	{
		RandomFoodPosition();
		m_BodyLength++;
		//std::cout << "m_BodyLength is: " << m_BodyLength << std::endl;
		//std::cout << "X position of last cube in array is: " << m_aSnakeBody[m_BodyLength-1].aPosition[0] << std::endl;
		//std::cout << std::endl;
		//EnlargeSnake();
		m_FoodHit = false;
	}

	// -----------------------------------------------------------------------------
	// Change snake position depending on direction.
	// -----------------------------------------------------------------------------
	NavigateSnake(this->m_sSnakeHead);

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
	// Set border box meshes in the world and draw in cyan.
	// -----------------------------------------------------------------------------
	for (int i = 0; i < 4; i++)
	{
		GetTranslationMatrix(m_aBorders[i].aPosition[0], m_aBorders[i].aPosition[1], m_aBorders[i].aPosition[2], WorldMatrix);
		GetScaleMatrix(m_aBorders[i].aScale[0], m_aBorders[i].aScale[1], m_aBorders[i].aScale[2], ScaleMatrix);
		MulMatrix(ScaleMatrix, WorldMatrix, WorldMatrix);
		SetWorldMatrix(WorldMatrix);

		DrawMesh(m_pCubeMeshCyan);
	}

	// -----------------------------------------------------------------------------
	// Set snake head mesh in the world and draw in white.
	// -----------------------------------------------------------------------------
	GetTranslationMatrix(m_sSnakeHead.aPosition[0], m_sSnakeHead.aPosition[1], m_sSnakeHead.aPosition[2], WorldMatrix);
	GetScaleMatrix(m_sSnakeHead.aScale[0], m_sSnakeHead.aScale[1], m_sSnakeHead.aScale[2], ScaleMatrix);
	MulMatrix(ScaleMatrix, WorldMatrix, WorldMatrix);
	SetWorldMatrix(WorldMatrix);

	DrawMesh(m_pCubeMeshWhite);

	// -----------------------------------------------------------------------------
	// Set snake body meshes in the world and draw in white.
	// -----------------------------------------------------------------------------
	for (int i = 0; i < m_BodyLength; i++)
	{
		GetTranslationMatrix(m_aSnakeBody[i].aPosition[0], m_aSnakeBody[i].aPosition[1], m_aSnakeBody[i].aPosition[2], WorldMatrix);
		GetScaleMatrix(m_aSnakeBody[i].aScale[0], m_aSnakeBody[i].aScale[1], m_aSnakeBody[i].aScale[2], ScaleMatrix);
		MulMatrix(ScaleMatrix, WorldMatrix, WorldMatrix);
		SetWorldMatrix(WorldMatrix);

		DrawMesh(m_pCubeMeshWhite);
		//std::cout << "Snake body cube should be drawn." << std::endl;
	}

	// -----------------------------------------------------------------------------
	// Set food block mesh in the world and draw in green.
	// -----------------------------------------------------------------------------
	GetTranslationMatrix(m_sFood.aPosition[0], m_sFood.aPosition[1], m_sFood.aPosition[2], WorldMatrix);
	GetScaleMatrix(m_sFood.aScale[0], m_sFood.aScale[1], m_sFood.aScale[2], ScaleMatrix);
	MulMatrix(ScaleMatrix, WorldMatrix, WorldMatrix);
	SetWorldMatrix(WorldMatrix);

	DrawMesh(m_pCubeMeshGreen);

    return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnKeyEvent(unsigned int _Key, bool _IsKeyDown, bool _IsAltDown)
{
	// -----------------------------------------------------------------------------
	// Processing of different key inputs.
	// -----------------------------------------------------------------------------
	if ((_Key == W_KEY || _Key == UP_KEY) && m_Direction != DIR_DOWN)
	{
		this->m_Direction = DIR_UP;
	}

	if ((_Key == A_KEY || _Key == LEFT_KEY)	&& m_Direction != DIR_RIGHT)
	{
		this->m_Direction = DIR_LEFT;
	}

	if ((_Key == S_KEY || _Key == DOWN_KEY)	&& m_Direction != DIR_UP)
	{
		this->m_Direction = DIR_DOWN;
	}

	if ((_Key == D_KEY || _Key == RIGHT_KEY) && m_Direction != DIR_LEFT)
	{
		this->m_Direction = DIR_RIGHT;
	}

	return true;
}
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

	for (int i = 0; i < (MAX_SNAKELENGTH); i++)
	{
		this->m_aSnakeBody[i] = {
		};
		this->m_aSnakeBodyOld[i] = {
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
	};

	// Right border
	this->m_aBorders[1] = {		
			FIELD_SIZE			, FIELD_SIZE / 2	, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE / 2		, FIELD_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
	};

	// Bottom border
	this->m_aBorders[2] = {		
			FIELD_SIZE / 2		, 0.0f				, 0.0f	,	// X- , Y- , Z- coordinates in the world
			FIELD_SIZE			, BLOCK_SIZE / 2	, 0.01f	,	// X- , Y- , Z- coordinates for scaling
	};

	// Left border
	this->m_aBorders[3] = {		
			0.0f				, FIELD_SIZE / 2	, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE / 2		, FIELD_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
	};

	// -----------------------------------------------------------------------------
	// Setting up snake head entity.
	// -----------------------------------------------------------------------------
	this->m_sSnakeHead = {
			FIELD_SIZE / 2		, FIELD_SIZE / 2	, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE			, BLOCK_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
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
	int RangeMax = FIELD_SIZE - 2;

	srand(time(0));

	X = 1 + (rand() % RangeMax);
	Y = 1 + (rand() % RangeMax);

	// -----------------------------------------------------------------------------
	// Set food block coordinates.
	// -----------------------------------------------------------------------------
	this->m_sFood = {
			X					, Y					, 0.0f	,	// X- , Y- , Z- coordinates in the world
			BLOCK_SIZE			, BLOCK_SIZE		, 0.01f	,	// X- , Y- , Z- coordinates for scaling
	};
}

// -----------------------------------------------------------------------------

void CApplication::NavigateSnake()
{
	// -----------------------------------------------------------------------------
	// Set iterator condition to define the speed of the snake.
	// -----------------------------------------------------------------------------
	if (m_MoveIterator == 6)
	{
		// -----------------------------------------------------------------------------
		// Change snake head position according to the currently given direction 
		// on key event. Also check for collision with border boxes.
		// -----------------------------------------------------------------------------
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

		// -----------------------------------------------------------------------------
		// Iterating through the snakes body array to follow its head. 
		// -----------------------------------------------------------------------------
		if (m_BodyLength > 0)
		{
			// -----------------------------------------------------------------------------
			// Transfer snake head information to first index of snake body array.
			// -----------------------------------------------------------------------------
			this->m_aSnakeBody[0] = this->m_sSnakeHead;

			for (int i = 0; i < m_BodyLength; i++)
			{
				this->m_aSnakeBody[i + 1] = this->m_aSnakeBodyOld[i];
				this->m_aSnakeBodyOld[i] = this->m_aSnakeBody[i];

				// -----------------------------------------------------------------------------
				// Check for snake collision with itself.
				// -----------------------------------------------------------------------------
				m_Collision = CheckCollision(this->m_sSnakeHead, this->m_aSnakeBody[i + 1]);
				if (m_Collision)
				{
					m_GameOver = true;
				}
			}
		}

		// -----------------------------------------------------------------------------
		// Reset iterator for timing.
		// -----------------------------------------------------------------------------
		m_MoveIterator = 0;
	}
	else
	{
		// -----------------------------------------------------------------------------
		// Increase iterator for timing.
		// -----------------------------------------------------------------------------
		m_MoveIterator++;
	}	
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
	CreateTexture("..\\data\\color_weiﬂ.jpg", &m_pCubeTextureWhite);
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
		m_FoodHit = false;
	}

	// -----------------------------------------------------------------------------
	// Change snake position depending on direction.
	// -----------------------------------------------------------------------------
	NavigateSnake();	

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnFrame()
{    
	float ScaleMatrix[16];
    float WorldMatrix[16];

	// -----------------------------------------------------------------------------
	// Stop the game when player collided / died.
	// -----------------------------------------------------------------------------
	if (m_GameOver)
	{
		puts("																		");
		puts("																		");
		puts("						    GAME OVER									");
		puts("																		");
		puts("						Sorry, you died !								");
		puts("																		");
		puts("																		\n");
		StopApplication();
	}

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
	// Set snake head mesh in the world and draw in green.
	// -----------------------------------------------------------------------------
	GetTranslationMatrix(m_sSnakeHead.aPosition[0], m_sSnakeHead.aPosition[1], m_sSnakeHead.aPosition[2], WorldMatrix);
	GetScaleMatrix(m_sSnakeHead.aScale[0], m_sSnakeHead.aScale[1], m_sSnakeHead.aScale[2], ScaleMatrix);
	MulMatrix(ScaleMatrix, WorldMatrix, WorldMatrix);
	SetWorldMatrix(WorldMatrix);

	DrawMesh(m_pCubeMeshGreen);

	// -----------------------------------------------------------------------------
	// Set snake body meshes in the world and draw in green.
	// -----------------------------------------------------------------------------
	if (m_BodyLength > 0)
	{
		for (int i = 0; i < m_BodyLength; i++)
		{
			GetTranslationMatrix(m_aSnakeBody[i].aPosition[0], m_aSnakeBody[i].aPosition[1], m_aSnakeBody[i].aPosition[2], WorldMatrix);
			GetScaleMatrix(m_aSnakeBody[i].aScale[0], m_aSnakeBody[i].aScale[1], m_aSnakeBody[i].aScale[2], ScaleMatrix);
			MulMatrix(ScaleMatrix, WorldMatrix, WorldMatrix);
			SetWorldMatrix(WorldMatrix);

			DrawMesh(m_pCubeMeshGreen);
		}
	}

	// -----------------------------------------------------------------------------
	// Set food block mesh in the world and draw in white.
	// -----------------------------------------------------------------------------
	GetTranslationMatrix(m_sFood.aPosition[0], m_sFood.aPosition[1], m_sFood.aPosition[2], WorldMatrix);
	GetScaleMatrix(m_sFood.aScale[0], m_sFood.aScale[1], m_sFood.aScale[2], ScaleMatrix);
	MulMatrix(ScaleMatrix, WorldMatrix, WorldMatrix);
	SetWorldMatrix(WorldMatrix);

	DrawMesh(m_pCubeMeshWhite);
	
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
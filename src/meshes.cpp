#include "meshes.h"

void CreateCube(BHandle* _ppCubeMesh, BHandle _pCubeTexture, float _EdgeLength)
{
	// -----------------------------------------------------------------------------
	// Define the vertices of the mesh and their attributes.
	// -----------------------------------------------------------------------------
	float s_HalfEdgeLength = 0.5f * _EdgeLength;

	float s_CubeVertices[][3] =
	{
		{ -s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
		{  s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
		{ -s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },

		{  s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
		{  s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },

		{  s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{ -s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{ -s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },

		{ -s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{ -s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
		{ -s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
		{ -s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },

		{ -s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength, -s_HalfEdgeLength, },
		{  s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },
		{ -s_HalfEdgeLength,  s_HalfEdgeLength,  s_HalfEdgeLength, },

		{ -s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{  s_HalfEdgeLength, -s_HalfEdgeLength,  s_HalfEdgeLength, },
		{  s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
		{ -s_HalfEdgeLength, -s_HalfEdgeLength, -s_HalfEdgeLength, },
	};


	static float s_CubeNormals[][3] =
	{
		{  0.0f,  0.0f, -1.0f, },
		{  0.0f,  0.0f, -1.0f, },
		{  0.0f,  0.0f, -1.0f, },
		{  0.0f,  0.0f, -1.0f, },

		{  1.0f,  0.0f,  0.0f, },
		{  1.0f,  0.0f,  0.0f, },
		{  1.0f,  0.0f,  0.0f, },
		{  1.0f,  0.0f,  0.0f, },

		{  0.0f,  0.0f,  1.0f, },
		{  0.0f,  0.0f,  1.0f, },
		{  0.0f,  0.0f,  1.0f, },
		{  0.0f,  0.0f,  1.0f, },

		{ -1.0f,  0.0f,  0.0f, },
		{ -1.0f,  0.0f,  0.0f, },
		{ -1.0f,  0.0f,  0.0f, },
		{ -1.0f,  0.0f,  0.0f, },

		{  0.0f,  1.0f,  0.0f, },
		{  0.0f,  1.0f,  0.0f, },
		{  0.0f,  1.0f,  0.0f, },
		{  0.0f,  1.0f,  0.0f, },

		{  0.0f, -1.0f,  0.0f, },
		{  0.0f, -1.0f,  0.0f, },
		{  0.0f, -1.0f,  0.0f, },
		{  0.0f, -1.0f,  0.0f, },
	};

	float s_U[] =
	{
		0.0f / 4.0f,
		1.0f / 4.0f,
		2.0f / 4.0f,
		3.0f / 4.0f,
		4.0f / 4.0f,
	};

	float s_V[] =
	{
		3.0f / 3.0f,
		2.0f / 3.0f,
		1.0f / 3.0f,
		0.0f / 3.0f,
	};

	float s_CubeTexCoords[][2] =
	{
		{ s_U[1], s_V[1], },
		{ s_U[2], s_V[1], },
		{ s_U[2], s_V[2], },
		{ s_U[1], s_V[2], },

		{ s_U[2], s_V[1], },
		{ s_U[3], s_V[1], },
		{ s_U[3], s_V[2], },
		{ s_U[2], s_V[2], },

		{ s_U[3], s_V[1], },
		{ s_U[4], s_V[1], },
		{ s_U[4], s_V[2], },
		{ s_U[3], s_V[2], },

		{ s_U[0], s_V[1], },
		{ s_U[1], s_V[1], },
		{ s_U[1], s_V[2], },
		{ s_U[0], s_V[2], },

		{ s_U[1], s_V[2], },
		{ s_U[2], s_V[2], },
		{ s_U[2], s_V[3], },
		{ s_U[1], s_V[3], },

		{ s_U[1], s_V[0], },
		{ s_U[2], s_V[0], },
		{ s_U[2], s_V[1], },
		{ s_U[1], s_V[1], },
	};

	// -----------------------------------------------------------------------------
	// Define the topology of the mesh via indices. An index addresses a vertex from
	// the array above. Three indices represent one triangle. When defining the 
	// triangles of a mesh imagine that you are standing in front of the triangle 
	// and looking to the center of the triangle. If the mesh represents a closed
	// body such as a cube, your view position has to be outside of the body. Now
	// define the indices of the addressed vertices of the triangle in counter-
	// clockwise order.
	// -----------------------------------------------------------------------------
	int s_CubeIndices[][3] =
	{
		{  0,  1,  2, },
		{  0,  2,  3, },

		{  4,  5,  6, },
		{  4,  6,  7, },

		{  8,  9, 10, },
		{  8, 10, 11, },

		{ 12, 13, 14, },
		{ 12, 14, 15, },

		{ 16, 17, 18, },
		{ 16, 18, 19, },

		{ 20, 21, 22, },
		{ 20, 22, 23, },
	};

	// -----------------------------------------------------------------------------
	// Define the mesh and its material. The material defines the look of the
	// surface covering the mesh. If the material should contain normals, colors, or
	// texture coordinates then their number has to match the number of vertices.
	// If you do not support normals in a mesh, YoshiX will not apply lighting to
	// this mesh. A textured mesh always has to contain texture coordinates and a
	// handle to a texture. A mesh always has to contain vertices and indices.
	// -----------------------------------------------------------------------------
	SMeshInfo MeshInfo;

	MeshInfo.m_pVertices = &s_CubeVertices[0][0];
	MeshInfo.m_pNormals = &s_CubeNormals[0][0];
	MeshInfo.m_pColors = nullptr;                          // No colors.
	MeshInfo.m_pTexCoords = &s_CubeTexCoords[0][0];
	MeshInfo.m_NumberOfVertices = 24;
	MeshInfo.m_NumberOfIndices = 36;
	MeshInfo.m_pIndices = &s_CubeIndices[0][0];
	MeshInfo.m_pTexture = _pCubeTexture;

	CreateMesh(MeshInfo, _ppCubeMesh);
}

// -----------------------------------------------------------------------------

void CreateSphere(BHandle* _ppSphereMesh, BHandle _pSphereTexture)
{
}

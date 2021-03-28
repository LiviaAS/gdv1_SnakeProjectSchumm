#include "meshes.h"

const float TEX_MIN = 0.0f;
const float TEX_MAX = 1.0f;

const int INDICES_PER_TRIANGLE = 3;

void CreateMeshObj(int NumOfVertices, float* pVertices, int NumOfTriangles, int* pTriangles, BHandle& Mesh)
{
    SMeshInfo MeshInfo;

    MeshInfo.m_NumberOfVertices = NumOfVertices;
    MeshInfo.m_pVertices = pVertices;

    MeshInfo.m_pNormals = nullptr;                  // No normals
    MeshInfo.m_pColors = nullptr;                   // No colors

    MeshInfo.m_NumberOfIndices = NumOfTriangles * INDICES_PER_TRIANGLE;
    MeshInfo.m_pIndices = pTriangles;

    CreateMesh(MeshInfo, &Mesh);
}

void CreateCubeMesh(BHandle& Mesh)
{
    float e = 0.5f; // half-edge length

    float s_CubeVertices[][3] = {   // [8] = {
        // front            
        { -e, e,-e },               // ,  TEX_MIN, TEX_MIN,  0.0f, 0.0f,-1.0f },
        { -e,-e,-e },               // ,  TEX_MIN, TEX_MAX,  0.0f, 0.0f,-1.0f },
        {  e,-e,-e },               // ,  TEX_MAX, TEX_MAX,  0.0f, 0.0f,-1.0f },
        {  e, e,-e },               // ,  TEX_MAX, TEX_MIN,  0.0f, 0.0f,-1.0f },
        // back     
        { -e,-e, e },               // ,  TEX_MIN, TEX_MIN,  0.0f, 0.0f, 1.0f },
        { -e, e, e },               // ,  TEX_MIN, TEX_MAX,  0.0f, 0.0f, 1.0f },
        {  e, e, e },               // ,  TEX_MAX, TEX_MAX,  0.0f, 0.0f, 1.0f },
        {  e,-e, e },               // ,  TEX_MAX, TEX_MIN,  0.0f, 0.0f, 1.0f },
        // top      
        { -e, e, e },               // ,  TEX_MIN, TEX_MIN,  0.0f, 1.0f, 0.0f },
        { -e, e,-e },               // ,  TEX_MIN, TEX_MAX,  0.0f, 1.0f, 0.0f },
        {  e, e,-e },               // ,  TEX_MAX, TEX_MAX,  0.0f, 1.0f, 0.0f },
        {  e, e, e },               // ,  TEX_MAX, TEX_MIN,  0.0f, 1.0f, 0.0f },
        // bottom   
        { -e,-e,-e },               // ,  TEX_MIN, TEX_MIN,  0.0f,-1.0f, 0.0f },
        { -e,-e, e },               // ,  TEX_MIN, TEX_MAX,  0.0f,-1.0f, 0.0f },
        {  e,-e, e },               // ,  TEX_MAX, TEX_MAX,  0.0f,-1.0f, 0.0f },
        {  e,-e,-e },               // ,  TEX_MAX, TEX_MIN,  0.0f,-1.0f, 0.0f },
        // right    
        {  e, e,-e },               // ,  TEX_MIN, TEX_MIN,  1.0f, 0.0f, 0.0f },
        {  e,-e,-e },               // ,  TEX_MIN, TEX_MAX,  1.0f, 0.0f, 0.0f },
        {  e,-e, e },               // ,  TEX_MAX, TEX_MAX,  1.0f, 0.0f, 0.0f },
        {  e, e, e },               // ,  TEX_MAX, TEX_MIN,  1.0f, 0.0f, 0.0f },
        // left     
        { -e, e, e },               // ,  TEX_MIN, TEX_MIN, -1.0f, 0.0f, 0.0f },
        { -e,-e, e },               // ,  TEX_MIN, TEX_MAX, -1.0f, 0.0f, 0.0f },
        { -e,-e,-e },               // ,  TEX_MAX, TEX_MAX, -1.0f, 0.0f, 0.0f },
        { -e, e,-e },               // ,  TEX_MAX, TEX_MIN, -1.0f, 0.0f, 0.0f },
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
    int s_CubeTriangles[][3] = {
        {  0, 1, 2 }, {  0, 2, 3 },
        {  4, 5, 6 }, {  4, 6, 7 },
        {  8, 9,10 }, {  8,10,11 },
        { 12,13,14 }, { 12,14,15 },
        { 16,17,18 }, { 16,18,19 },
        { 20,21,22 }, { 20,22,23 },
    };

    CreateMeshObj(24, &s_CubeVertices[0][0], 12, &s_CubeTriangles[0][0], Mesh);
}
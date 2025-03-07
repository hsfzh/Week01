#pragma once

FVertexSimple cube_vertices[] =
{
    // Front face (Z = +1) - (��: ����)
    { -1.0f, -1.0f,  1.0f,  1, 0, 0, 1 },  // Bottom-left
    {  1.0f, -1.0f,  1.0f,  1, 0, 0, 1 },  // Bottom-right
    {  1.0f,  1.0f,  1.0f,  1, 0, 0, 1 },  // Top-right

    { -1.0f, -1.0f,  1.0f,  1, 0, 0, 1 },  // Bottom-left
    {  1.0f,  1.0f,  1.0f,  1, 0, 0, 1 },  // Top-right
    { -1.0f,  1.0f,  1.0f,  1, 0, 0, 1 },  // Top-left

    // Back face (Z = -1) - (��: �ʷ�)
    {  1.0f, -1.0f, -1.0f,  0, 1, 0, 1 },  // Bottom-right
    { -1.0f, -1.0f, -1.0f,  0, 1, 0, 1 },  // Bottom-left
    { -1.0f,  1.0f, -1.0f,  0, 1, 0, 1 },  // Top-left

    {  1.0f, -1.0f, -1.0f,  0, 1, 0, 1 },  // Bottom-right
    { -1.0f,  1.0f, -1.0f,  0, 1, 0, 1 },  // Top-left
    {  1.0f,  1.0f, -1.0f,  0, 1, 0, 1 },  // Top-right

    // Left face (X = -1) - (��: �Ķ�)
    { -1.0f, -1.0f, -1.0f,  0, 0, 1, 1 },  // Bottom-back
    { -1.0f, -1.0f,  1.0f,  0, 0, 1, 1 },  // Bottom-front
    { -1.0f,  1.0f,  1.0f,  0, 0, 1, 1 },  // Top-front

    { -1.0f, -1.0f, -1.0f,  0, 0, 1, 1 },  // Bottom-back
    { -1.0f,  1.0f,  1.0f,  0, 0, 1, 1 },  // Top-front
    { -1.0f,  1.0f, -1.0f,  0, 0, 1, 1 },  // Top-back

    // Right face (X = +1) - (��: ���)
    {  1.0f, -1.0f,  1.0f,  1, 1, 0, 1 },  // Bottom-front
    {  1.0f, -1.0f, -1.0f,  1, 1, 0, 1 },  // Bottom-back
    {  1.0f,  1.0f, -1.0f,  1, 1, 0, 1 },  // Top-back

    {  1.0f, -1.0f,  1.0f,  1, 1, 0, 1 },  // Bottom-front
    {  1.0f,  1.0f, -1.0f,  1, 1, 0, 1 },  // Top-back
    {  1.0f,  1.0f,  1.0f,  1, 1, 0, 1 },  // Top-front

    // Top face (Y = +1) - (��: ��ȫ)
    { -1.0f,  1.0f,  1.0f,  1, 0, 1, 1 },  // Front-left
    {  1.0f,  1.0f,  1.0f,  1, 0, 1, 1 },  // Front-right
    {  1.0f,  1.0f, -1.0f,  1, 0, 1, 1 },  // Back-right

    { -1.0f,  1.0f,  1.0f,  1, 0, 1, 1 },  // Front-left
    {  1.0f,  1.0f, -1.0f,  1, 0, 1, 1 },  // Back-right
    { -1.0f,  1.0f, -1.0f,  1, 0, 1, 1 },  // Back-left

    // Bottom face (Y = -1) - (��: û��)
    { -1.0f, -1.0f, -1.0f,  0, 1, 1, 1 },  // Back-left
    {  1.0f, -1.0f, -1.0f,  0, 1, 1, 1 },  // Back-right
    {  1.0f, -1.0f,  1.0f,  0, 1, 1, 1 },  // Front-right

    { -1.0f, -1.0f, -1.0f,  0, 1, 1, 1 },  // Back-left
    {  1.0f, -1.0f,  1.0f,  0, 1, 1, 1 },  // Front-right
    { -1.0f, -1.0f,  1.0f,  0, 1, 1, 1 }   // Front-left
};
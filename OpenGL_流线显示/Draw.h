#pragma once
#include "glew/glew.h"
#include <iostream>
#include "stb_image.h"
struct  Vertex
{
	float   x, y, z;
	float   u, v;
};
class DrawImageScreen
{

private:
	GLsizei m_screenHeight;
	GLsizei m_screenWidth;
	std::shared_ptr<GLsizei> m_screen;
	unsigned   createTexture(int w, int h, const void* data, GLenum type);

private:
	void SetPixel(GLsizei x, GLsizei y, GLchar r, GLchar g, GLchar b, GLchar a);
public:
	DrawImageScreen(GLsizei width , GLsizei height); 
	DrawImageScreen();

	~DrawImageScreen();
	template<typename T>
	inline std::shared_ptr<T> MakeArray(int size)
	{
		return std::shared_ptr<T>(new T[size], [](T *p) { delete[] p; });
	}

	GLuint    createTextureFromImage(const char* fileName);
	

public:
	void CreateScreen();
	void Draw();
	 
};


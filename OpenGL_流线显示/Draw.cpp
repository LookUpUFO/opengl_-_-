#include "Draw.h"


DrawImageScreen::DrawImageScreen()
{

}
DrawImageScreen::DrawImageScreen(GLsizei width, GLsizei height)
{
	m_screenWidth	= width;
	m_screenHeight	= height;
	m_screen		= nullptr;
}

void DrawImageScreen::SetPixel(GLsizei x, GLsizei y, GLchar r, GLchar g, GLchar b, GLchar a)
{
	 
}

void DrawImageScreen::CreateScreen()
{
	m_screen = MakeArray< GLsizei>(m_screenHeight*m_screenWidth);

}
DrawImageScreen::~DrawImageScreen()
{

}

void DrawImageScreen::Draw()
{
	Vertex  rect[] =
	{
		{10,    10,     0,  0,  1},
		{410,   10,     0,  1,  1},
		{10,    410,    0,  0,  0},
		{410,   410,    0,  1,  0},
	};
	  
}

/**
*	µ˜”√freeimageº”‘ÿÕº∆¨
*/
GLuint   DrawImageScreen::createTextureFromImage(const char* fileName)
{
	int     width;
	int     height;
	int     chanel;
	GLuint  texId;
	stbi_uc*    pixels = stbi_load(fileName, &width, &height, &chanel, 0);
	if (chanel == 3)
	{
		texId = createTexture(width, height, pixels, GL_RGB);
	}
	else
	{
		texId = createTexture(width, height, pixels, GL_RGBA);
	}
	free(pixels);

	return  texId;
}

unsigned  DrawImageScreen::createTexture(int w, int h, const void* data, GLenum type)
{
	unsigned    texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, type, w, h, 0, type, GL_UNSIGNED_BYTE, data);

	
	return  texId;
}
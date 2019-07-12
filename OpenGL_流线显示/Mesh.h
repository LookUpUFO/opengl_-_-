#include "../math_Lib/Matrix.h"
#include <iostream>
#include <vector>

#pragma once
class Mesh
{
public:
	Mesh();
	~Mesh();
public:
	std::vector<WHQ::Vector4>  m_vertexArrar;
	std::vector<int>	m_indexArray;

};


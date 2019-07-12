#pragma once
#ifndef _VECTOR_H
#define _VECTOR_H

typedef struct  Vector3
{
	float x;
	float y;
	float z;
	Vector3(float x, float y, float z)
	{		
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	} 
	Vector3(float x, float y)
	{
		this->x = x;
		this->y = y;
		this->z = 0;
	}
}Vector2;


#endif // !_VECTOR_H

#pragma once
#include "../math_Lib/Matrix.h"

struct  linePoint
{
	Vector3 m_position;
	Vector3 m_speed;
	linePoint(Vector3 position, Vector3 speed)
	{
		m_position = position;
		m_speed = speed;
	}

	linePoint()
	{
		m_position = Vector3::Zero();
		m_speed = Vector3::Zero();
	}
};
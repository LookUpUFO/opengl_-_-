#pragma once
#include <math.h>
#include <iostream>

namespace WHQ
{
	struct  Matrix;
	typedef struct Vector4 Vector3, Vector2;

#define PI 3.1415926

	typedef struct Vector4
	{
		float x;
		float y;
		float z;
		float w;
		Vector4(float x, float y, float z = 0, float w = 0);
		Vector4();
		//ºá³Ë 1¡Á 4    * 4¡Á4  = 1¡Á4
		Vector4	operator *(Matrix right);
		Vector4	operator *(float right);
		Vector4	operator /(float right);

		Vector4	operator +(Vector4 right);
		Vector4	operator -(Vector4 right);

	static	float Dot(Vector3 dir1, Vector3 dir2);
	static	Vector3 Cross(Vector3 dir1, Vector3 dir2);
	float Length();

	Vector3 Normal();
	
	static Vector3 Zero();

	float Magnitude();
	}Vector3, Vector2;

	struct Matrix
	{
		float m00;
		float m01;
		float m02;
		float m03;

		float m10;
		float m11;
		float m12;
		float m13;

		float m20;
		float m21;
		float m22;
		float m23;

		float m30;
		float m31;
		float m32;
		float m33;

		Matrix();
		Matrix operator*(Matrix right);

		Matrix operator+(Matrix right);

		Matrix operator*(float value);

		Matrix operator-(Matrix right);


		//Êú³Ë 4¡Á4  * 4¡Á1
		Vector4 operator*(Vector4 right);

		static Matrix	Rotate_Z(float angle);
		 
		static Matrix	Identity();
	 
		static Matrix Translate(Vector3 offset);
		 
		static Matrix Scaler(Vector3 scal);

		//Matrix 
	};


	struct Rect 
	{
		Vector3 m_min;
		Vector3 m_max;
		bool isInRect(Vector3 s)
		{
			if (s.x >= m_min.x&& s.x <= m_max.x)
				if (s.y >= m_min.y&& s.y <= m_max.y)
					if (s.z >= m_min.z&& s.z <= m_max.z)
						return true;
			return false;
		}
		Rect(Vector3 min, Vector3 max)
		{
			m_max = max;
			m_min				= min;
		}
		Rect()
		{

		}
	};
}


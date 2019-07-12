#include "Matrix.h"
using namespace WHQ;

Vector4	Vector4::operator *(float right)
{
	Vector4 s;
	s.x = this->x *right;
	s.y = this->y *right;
	s.z = this->z *right;
	s.w = this->w *right;
	return s;

}
Vector4	Vector4::operator /(float right)
{
	Vector4 s;
	s.x = this->x /right;
	s.y = this->y /right;
	s.z = this->z /right;
	s.w = this->w /right;
	return s;
}
Vector4::Vector4(float x, float y, float z , float w )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}
Vector4	Vector4::operator +(Vector4 right)
{
	Vector4 s;
	s.x = this->x + right.x;
	s.y = this->y + right.y;
	s.z = this->z + right.z;
	s.w = this->w + right.w;
	return s;
}
Vector4	Vector4::operator -(Vector4 right)
{
	Vector4 s;
	s.x = this->x - right.x;
	s.y = this->y - right.y;
	s.z = this->z - right.z;
	s.w = this->w - right.w;
	return s;
}
Vector4::Vector4()
{
	Vector4(0, 0, 0, 0);
}
float Vector4::Dot(Vector3 dir1, Vector3 dir2)
{
	float s;
	s = dir1.x*dir2.x + dir1.y*dir2.y + dir1.z*dir2.z;
	return s;
}

Vector3 Vector4::Cross(Vector3 dir1, Vector3 dir2)
{
	Vector3 s;
	s.x = dir1.y*dir2.z - dir2.y*dir1.z;
	s.y = -dir1.x*dir2.z + dir2.x*dir1.z;
	s.z = dir1.x*dir2.y - dir2.x*dir1.y;
	return s;

}
float Vector4::Length()
{
	float s = pow(x, 2) + pow(y, 2) + pow(z, 2);
	s = std::sqrtf(s);
	return s;
}

Vector3 Vector4::Normal()
{
	float length = this->Length();
	Vector3 s;
	s.x = this->x / length;
	s.y = this->y / length;
	s.z = this->z / length;
	return s;
}

Vector3 WHQ::Vector4::Zero()
{
	return Vector3(0,0,0);
}

float WHQ::Vector4::Magnitude()
{

	return Length();
}

//ºá³Ë 1¡Á 4    * 4¡Á4  = 1¡Á4
Vector4 Vector4::operator *(Matrix right)
{
	Vector4 out;
	Matrix s;
	s.m00 = this->x;
	s.m01 = this->y;
	s.m02 = this->z;
	s.m03 = this->w;

	out.x = s.m00;
	out.y = s.m01;
	out.z = s.m02;
	out.w = s.m03;
	return out * right;
}

 

Matrix::Matrix()
{
	m00 = 0.f;
	m01 = 0.f;
	m02 = 0.f;
	m03 = 0.f;

	m10 = 0.f;
	m11 = 0.f;
	m12 = 0.f;
	m13 = 0.f;

	m20 = 0.f;
	m21 = 0.f;
	m22 = 0.f;
	m23 = 0.f;

	m30 = 0.f;
	m31 = 0.f;
	m32 = 0.f;
	m33 = 0.f;
}

Matrix Matrix::operator*(Matrix right)
{
	Matrix out;
	out.m00 = this->m00 * right.m00 + this->m01 * right.m10 + this->m02 * right.m20 + this->m03 * right.m30;

	out.m01 = this->m00 * right.m01 + this->m01 * right.m11 + this->m02 * right.m21 + this->m03 * right.m31;
	out.m02 = this->m00 * right.m02 + this->m01 * right.m12 + this->m02 * right.m22 + this->m03 * right.m32;
	out.m03 = this->m00 * right.m03 + this->m01 * right.m13 + this->m02 * right.m23 + this->m03 * right.m33;

	out.m10 = this->m10 * right.m00 + this->m11 * right.m10 + this->m12 * right.m20 + this->m13 * right.m30;
	out.m11 = this->m10 * right.m01 + this->m11 * right.m11 + this->m12 * right.m21 + this->m13 * right.m31;
	out.m12 = this->m10 * right.m02 + this->m11 * right.m12 + this->m12 * right.m22 + this->m13 * right.m32;
	out.m13 = this->m10 * right.m03 + this->m11 * right.m13 + this->m12 * right.m23 + this->m13 * right.m33;

	out.m20 = this->m20 * right.m00 + this->m21 * right.m10 + this->m22 * right.m20 + this->m23 * right.m30;
	out.m21 = this->m20 * right.m01 + this->m21 * right.m11 + this->m22 * right.m21 + this->m23 * right.m31;
	out.m22 = this->m20 * right.m02 + this->m21 * right.m12 + this->m22 * right.m22 + this->m23 * right.m32;
	out.m23 = this->m20 * right.m03 + this->m21 * right.m13 + this->m22 * right.m23 + this->m23 * right.m33;

	out.m30 = this->m30 * right.m00 + this->m31 * right.m10 + this->m32 * right.m20 + this->m33 * right.m30;
	out.m31 = this->m30 * right.m01 + this->m31 * right.m11 + this->m32 * right.m21 + this->m33 * right.m31;
	out.m32 = this->m30 * right.m02 + this->m31 * right.m12 + this->m32 * right.m22 + this->m33 * right.m32;
	out.m33 = this->m30 * right.m03 + this->m31 * right.m13 + this->m32 * right.m23 + this->m33 * right.m33;

	return out;
}

Matrix Matrix::operator+(Matrix right)
{
	Matrix out;
	out.m00 = this->m00 + right.m00;
	out.m01 = this->m01 + right.m01;
	out.m02 = this->m02 + right.m02;
	out.m03 = this->m03 + right.m03;

	out.m10 = this->m10 + right.m10;
	out.m11 = this->m11 + right.m11;
	out.m12 = this->m12 + right.m12;
	out.m13 = this->m13 + right.m13;

	out.m20 = this->m20 + right.m20;
	out.m21 = this->m21 + right.m21;
	out.m22 = this->m22 + right.m22;
	out.m23 = this->m23 + right.m23;

	out.m30 = this->m30 + right.m30;
	out.m31 = this->m31 + right.m31;
	out.m32 = this->m32 + right.m32;
	out.m33 = this->m33 + right.m33;
	return out;
}

Matrix Matrix::operator*(float value)
{
	Matrix out;
	out.m00 = this->m00 *value;
	out.m01 = this->m01 *value;
	out.m02 = this->m02 *value;
	out.m03 = this->m03 *value;

	out.m10 = this->m10 *value;
	out.m11 = this->m11 *value;
	out.m12 = this->m12 *value;
	out.m13 = this->m13 *value;

	out.m20 = this->m20 *value;
	out.m21 = this->m21 *value;
	out.m22 = this->m22 *value;
	out.m23 = this->m23 *value;

	out.m30 = this->m30 *value;
	out.m31 = this->m31 *value;
	out.m32 = this->m32 *value;
	out.m33 = this->m33 *value;
	return out;
}

Matrix Matrix::operator-(Matrix right)
{
	right = right * -1;
	return this->operator+(right);
}


//Êú³Ë 4¡Á4  * 4¡Á1 = 4X1
Vector4 Matrix::operator*(Vector4 right)
{
	Matrix out;
	out.m00 = right.x;
	out.m10 = right.y;
	out.m20 = right.z;
	out.m30 = right.w;
	out = this->operator*(out);
	Vector4 v;
	v.x = out.m00;
	v.y = out.m10;
	v.z = out.m20;
	v.w = out.m30;
	return v;

}


Matrix  Matrix::Rotate_Z(float angle)
{
	float radian = angle / 180 * PI;
	Matrix rotate = Identity();

	rotate.m00 = cosf(radian);
	rotate.m11 = cosf(radian);


	rotate.m01 = -sinf(radian);
	rotate.m10 = sinf(radian);

	rotate.m22 = 1;
	rotate.m33 = 1;
	return rotate;
}
 Matrix Matrix::Identity()
{
	Matrix identity;
	identity.m00 = 1;
	identity.m11 = 1;
	identity.m22 = 1;
	identity.m33 = 1;
	return identity;
}

 Matrix Matrix::Translate(Vector3 offset)
 {
	 Matrix out = Identity();
	 out.m03 = offset.x;
	 out.m13 = offset.y;
	 out.m23 = offset.z;
	 out.m33 = 1;
	 return out;
 }

 Matrix Matrix::Scaler(Vector3 scal)
 {
	 Matrix identity = Identity();
	 identity.m00 = scal.x;
	 identity.m11 = scal.y;
	 identity.m22 = scal.z;
	 identity.m33 = 1;
	 return identity;
   }
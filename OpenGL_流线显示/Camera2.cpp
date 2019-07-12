#include "Camera2.h"


#if true
void Camera2::CameraInit(Vector3 positon, Vector3 up, Vector3 forward)
{
	Matrix view = Matrix::Identity();

	view.m03 = positon.x;
	view.m13 = positon.y;
	view.m23 = positon.z;
	
	up			= up.Normal();
	Vector3 right = Vector3::Cross(forward, up).Normal();
	view.m00 = right.x;
	view.m01 = right.y;
	view.m02 = right.z;

	view.m10 = up.x;
	view.m11 = up.y;
	view.m12 = up.z;

	view.m20 = forward.x;
	view.m21 = forward.y;
	view.m22 = forward.z;

	m_matView = view;
	 
}

 
void Camera2::Oritho(float left, float right, float bottom, float top, float zNear, float zfar)
{
	Matrix oritho = Matrix::Identity();

	oritho.m00 = 2 / (right - left);
	oritho.m03 = (right+left)/ (right - left);

	oritho.m11 = 2 / (top - bottom);
	oritho.m13 = (top + bottom) / (top - bottom);


	oritho.m22 = -2 / (zNear - zfar);
	oritho.m23 = (zNear + zfar) / (zNear - zfar);

	m_matProject = oritho;
}

void Camera2::Update()
{
	 
}

#endif


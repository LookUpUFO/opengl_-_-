#pragma once
#include "../math_Lib/Matrix.h"

using  namespace WHQ;

class Camera
{

private:
	Vector3 m_position;
	Vector3 m_up;
	Vector3 m_forward;

	 
	Matrix  m_matProject;
	//指相机坐标系
	Matrix  m_matView;


	Vector3 m_taget;
public: 

	void SetTarget(Vector3 target);
	//正交投影
	void  Oritho(Vector3 left, Vector3 right, Vector3 bottom, Vector3 top, Vector3 zNear, Vector3 zfar);
	//透视投影
	void Perspective(float forve, float aspect, float zNear, float zFar);
	//世界坐标系转屏幕坐标系
	Vector3  World2Screen(Vector3 pos);
	//世界坐标系转相机坐标系统
	Vector3 World2Camera(Vector3 pos);
	//相机坐标系转实际坐标系
	Vector3 Camera2World(Vector3 pos);

	
public:
	Camera(Vector3 positon , Vector3 up , Vector3 forward  );

	~Camera();
};


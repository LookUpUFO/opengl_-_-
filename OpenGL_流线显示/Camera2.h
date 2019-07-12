#pragma once

#include "Component.h"
#include "../math_Lib/Matrix.h" 

using  namespace WHQ;

class Camera2 :public Component
{
	
private:

	Matrix  m_matProject;
	//指相机坐标系
	Matrix  m_matView;
	Vector3 m_taget;

	
public: 

	void SetTarget(Vector3 target);
	//正交投影
	void  Oritho(float left, float right, float bottom, float top, float zNear, float zfar);
	//透视投影
	void Perspective(float forve, float aspect, float zNear, float zFar);
	//世界坐标系转屏幕坐标系
	Vector3  World2Screen(Vector3 pos);
	//世界坐标系转相机坐标系统
	Vector3 World2Camera(Vector3 pos);
	//相机坐标系转实际坐标系
	Vector3 Camera2World(Vector3 pos);
	//相机移动
	void Move(Vector3 direct , float distance = 1);
	//旋转:绕世界坐标系中axis轴旋转angle 角度
	void Rotation(Vector3 axis, float angle);

 
	void Update() override;
	 
 
	Vector3 GetPosition();
	Vector3 GetTarget();
	Matrix  GetProject();


public:
	void CameraInit(Vector3 positon, Vector3 up, Vector3 forward); 

	
};
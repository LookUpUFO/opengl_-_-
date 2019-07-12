#pragma once

#include "Component.h"
#include "../math_Lib/Matrix.h" 

using  namespace WHQ;

class Camera2 :public Component
{
	
private:

	Matrix  m_matProject;
	//ָ�������ϵ
	Matrix  m_matView;
	Vector3 m_taget;

	
public: 

	void SetTarget(Vector3 target);
	//����ͶӰ
	void  Oritho(float left, float right, float bottom, float top, float zNear, float zfar);
	//͸��ͶӰ
	void Perspective(float forve, float aspect, float zNear, float zFar);
	//��������ϵת��Ļ����ϵ
	Vector3  World2Screen(Vector3 pos);
	//��������ϵת�������ϵͳ
	Vector3 World2Camera(Vector3 pos);
	//�������ϵתʵ������ϵ
	Vector3 Camera2World(Vector3 pos);
	//����ƶ�
	void Move(Vector3 direct , float distance = 1);
	//��ת:����������ϵ��axis����תangle �Ƕ�
	void Rotation(Vector3 axis, float angle);

 
	void Update() override;
	 
 
	Vector3 GetPosition();
	Vector3 GetTarget();
	Matrix  GetProject();


public:
	void CameraInit(Vector3 positon, Vector3 up, Vector3 forward); 

	
};
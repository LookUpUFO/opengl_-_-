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
	//ָ�������ϵ
	Matrix  m_matView;


	Vector3 m_taget;
public: 

	void SetTarget(Vector3 target);
	//����ͶӰ
	void  Oritho(Vector3 left, Vector3 right, Vector3 bottom, Vector3 top, Vector3 zNear, Vector3 zfar);
	//͸��ͶӰ
	void Perspective(float forve, float aspect, float zNear, float zFar);
	//��������ϵת��Ļ����ϵ
	Vector3  World2Screen(Vector3 pos);
	//��������ϵת�������ϵͳ
	Vector3 World2Camera(Vector3 pos);
	//�������ϵתʵ������ϵ
	Vector3 Camera2World(Vector3 pos);

	
public:
	Camera(Vector3 positon , Vector3 up , Vector3 forward  );

	~Camera();
};


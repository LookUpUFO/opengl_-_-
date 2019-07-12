#pragma once
#include "Component.h"
#include "../math_Lib/Matrix.h"
using namespace WHQ;

//���������λ����Ϣ����
class Translate :public Component
{

private:
	Vector3 m_position;
	Vector3 m_up;
	Vector3 m_right;
	Vector3 m_forward;

	Matrix	m_matLocal2Wolrd;

	Vector3 m_rotateion;
	Vector3 m_scal;
public:

	void Update() override;

public:
	/*
	����λ�ã�
	isWorld = true ��������������ϵλ�� ;
	false �����ؾֲ�����ϵλ��
	*/
	Vector3 GetPosition(bool isWorld = true);
	/*
	������ת�Ƕ�
	isWorld = true :������������ϵ����ת�Ƕ�
	isWorld =false :���ؾֲ�����ϵ�½Ƕ�
	*/
	Vector3 GetRotation(bool isWorld = true); 
	Vector3 GetScal(bool isWorld = true);
	Matrix GetLocal2WorldMatrix();
	/*
	�ֲ�����ϵת��������ϵ
	*/
	Vector3 Local2World(Vector3 pos);
 
};


#pragma once
#include "Component.h"
#include "../math_Lib/Matrix.h"
using namespace WHQ;

//对象的描述位置信息描述
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
	返回位置：
	isWorld = true ：返回世界坐标系位置 ;
	false ：返回局部坐标系位置
	*/
	Vector3 GetPosition(bool isWorld = true);
	/*
	返回旋转角度
	isWorld = true :返回世界坐标系下旋转角度
	isWorld =false :返回局部坐标系下角度
	*/
	Vector3 GetRotation(bool isWorld = true); 
	Vector3 GetScal(bool isWorld = true);
	Matrix GetLocal2WorldMatrix();
	/*
	局部坐标系转世界坐标系
	*/
	Vector3 Local2World(Vector3 pos);
 
};


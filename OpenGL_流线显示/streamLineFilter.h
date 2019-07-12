#pragma once
#include <list> 
#include <iostream>
#include<vector>
#include "PointClound.h"

typedef int T;
#include "../math_Lib/Matrix.h"
#include "Mesh.h"
#include "GlobalDefine.h"

using namespace WHQ;
#define OUT 
#define IN


class StreamLineFilter
{ 

public: 
	void SetInput(std::shared_ptr<PointClound > pPointClound);
	void Update(int beginX, int beginY, int beginZ, float step);

	std::vector<Vector3> GetOutPut();

	const std::vector<Vector3>& GetCloundPoint();
private:
	
	///计算下一个坐标点
	const Point *  RungeKutta(IN OUT linePoint&   currentPos, IN const  Point  *    basePos,bool isInverse = false);
	//差值计算当前点方向
	const Point *  DeviatCalculateDir(IN  const  Point * basePos, OUT linePoint& currentPos);
	const Point *  DeviatCalculateDir3D(IN const  Point * basePos, OUT linePoint& currentPos);
	const Point *  DeviatCalculateDir2D(IN const  Point * basePos, OUT linePoint& currentPos);
private:
	std::shared_ptr<PointClound > m_pPointClound;
	bool m_isThreedD;
	float m_step;
	std::vector<Vector3> m_positonArray;

};

 
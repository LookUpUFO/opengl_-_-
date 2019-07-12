#pragma once
#include "../math_Lib/Matrix.h"
#include <list>
#include <vector>

typedef int Int;


using namespace WHQ;
using namespace std;

struct Border;
//template <class T>
struct  Point;
//template <class T>
class	PointClound;

struct Attribute
{
	//速度
	Vector3 m_speed;
	//压力
	float m_pressure;
	//速度大小;
};


//template <class T>
struct  Point
{
	Attribute m_attribute;
	 
	Vector3 m_position;

	//二维
	const Point * m_leftPoint;
	const Point * m_rightPoint;
	const Point * m_downPoint;
	const Point * m_upPoint;
	//三维下 *			 
	const Point * m_frontPoint;
	const Point * m_backPoint;


	Point(Vector3 pos, Attribute attribute);
	Point();

};







//template <class T>
class PointClound
{
public:
	PointClound();
	~PointClound();
	Point   GetFirstPos();

	bool isInCube(Vector3 pos,const Point *point) ;
	///建立点云关系网；
	///传入的数据循环规律为：x 循环,y 循环 ,z 循环 
	void SetInput(std::vector<Point >& pointList, int xLength, int yLength, int zLength = 1);

	const Point * GetPoint(int x ,int y, int z);
	///判断是三维数据
	bool IsThreedD();
private:
	std::vector<  Point > m_pointList;
	Int m_xLoop;
	Int m_yLoop;
	Int m_zLoop;

	const Point* m_endPoint;
	const Point* m_beinPoint;
};



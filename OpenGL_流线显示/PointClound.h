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
	//�ٶ�
	Vector3 m_speed;
	//ѹ��
	float m_pressure;
	//�ٶȴ�С;
};


//template <class T>
struct  Point
{
	Attribute m_attribute;
	 
	Vector3 m_position;

	//��ά
	const Point * m_leftPoint;
	const Point * m_rightPoint;
	const Point * m_downPoint;
	const Point * m_upPoint;
	//��ά�� *			 
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
	///�������ƹ�ϵ����
	///���������ѭ������Ϊ��x ѭ��,y ѭ�� ,z ѭ�� 
	void SetInput(std::vector<Point >& pointList, int xLength, int yLength, int zLength = 1);

	const Point * GetPoint(int x ,int y, int z);
	///�ж�����ά����
	bool IsThreedD();
private:
	std::vector<  Point > m_pointList;
	Int m_xLoop;
	Int m_yLoop;
	Int m_zLoop;

	const Point* m_endPoint;
	const Point* m_beinPoint;
};



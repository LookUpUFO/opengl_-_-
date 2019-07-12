#include "Brasky.h"
//#include <minwindef.h>



Brasky::Brasky()
{
	m_isRender = true;
}


Brasky::~Brasky()
{
}

void Brasky::Render()
{
	if (!m_isRender)
		return;

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2f(m_beginPos.x, m_beginPos.y);
	glVertex2f(m_endPos.x, m_endPos.y);
	glEnd();
	glFlush();
}

void Brasky::SetInput(Vector3 beginPos, Vector3 endPos, Rect clipRect)
{
	m_beginPos = beginPos;
	m_endPos = endPos;
	m_clipRect = clipRect;


}
//原理：
/*
线段与每个边框（凸多边形）的法向量（指向多边形内部）的点乘的所有结果为A集合
分为：
	1.	A<0  小于0的集合
	2.	A>0	 大于0的集合

	此时可画图
	可知：
	A<0	中的当数值最大u1时后在边框上，此时可知其交点
	A>0	中的当数值最小u2时候在边框上，此时也可知交点

	当满足u1<u2时,则可求得此线段
	不满最时，则抛弃此线段，不在线段裁剪区域之内


	因为此裁剪时上诉理论的特殊部分，所以，变得简单起来。
*/



void Brasky::Update()
{
	
	float dertaX = m_endPos.x - m_beginPos.x;
	float dertaY = m_endPos.y - m_beginPos.y;

	float m = dertaY / dertaX;
	//左边界
	Vector3 pt[4];
	Vector3 p1 = m_beginPos;
	Vector3 p2 = m_endPos;

	pt[0].y = p1.y + m * (m_clipRect.m_min.x - p1.x);
	pt[0].x = m_clipRect.m_min.x; 
	float s[4];
	s[0] = Vector3::Dot(Vector3(1, 0, 0), pt[0]);
	 
	//上边界
	pt[1].x = p1.x + (m_clipRect.m_max.y - p1.y) / m;
	pt[1].y = m_clipRect.m_max.y;
	s[1]= Vector3::Dot(Vector3(0, -1, 0), pt[1]);

	//右边界
	pt[2].x = m_clipRect.m_max.x;
	pt[2].y = p1.y + m * (m_clipRect.m_max.x - p1.x);
	s[2] = Vector3::Dot(Vector3(-1, 0, 0), pt[2]);

	//下边界
	pt[3].y = m_clipRect.m_min.y;
	pt[3].x = p1.x + (m_clipRect.m_min.y - p1.y) / m;
	s[3] = Vector3::Dot(Vector3(0, 1, 0), pt[3]);

	 
	int max_u = 1000000;
	int max_index = 0;
	int min_v = -100000;
	int min_index = 0;
	for (int i = 0; i < 4; i++)
	{
		if (s[i] > 0)
		{ 
			max_u = max_u< s[i] ?max_u: s[i]; //min(max_u,s[i]);
			if (max_u == s[i])
				max_index = i; 
		}
		else
		{
			min_v = min_v> s[i] ? min_v:s[i]; //max(min_v, s[i]);
			if (min_v == s[i])
				min_index = i;
		}
	}
	if (max_u < min_v)
		m_isRender = false;
	m_beginPos = pt[min_index];
	m_endPos = pt[max_index];
}




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
//ԭ��
/*
�߶���ÿ���߿�͹����Σ��ķ�������ָ�������ڲ����ĵ�˵����н��ΪA����
��Ϊ��
	1.	A<0  С��0�ļ���
	2.	A>0	 ����0�ļ���

	��ʱ�ɻ�ͼ
	��֪��
	A<0	�еĵ���ֵ���u1ʱ���ڱ߿��ϣ���ʱ��֪�佻��
	A>0	�еĵ���ֵ��Сu2ʱ���ڱ߿��ϣ���ʱҲ��֪����

	������u1<u2ʱ,�����ô��߶�
	������ʱ�����������߶Σ������߶βü�����֮��


	��Ϊ�˲ü�ʱ�������۵����ⲿ�֣����ԣ���ü�������
*/



void Brasky::Update()
{
	
	float dertaX = m_endPos.x - m_beginPos.x;
	float dertaY = m_endPos.y - m_beginPos.y;

	float m = dertaY / dertaX;
	//��߽�
	Vector3 pt[4];
	Vector3 p1 = m_beginPos;
	Vector3 p2 = m_endPos;

	pt[0].y = p1.y + m * (m_clipRect.m_min.x - p1.x);
	pt[0].x = m_clipRect.m_min.x; 
	float s[4];
	s[0] = Vector3::Dot(Vector3(1, 0, 0), pt[0]);
	 
	//�ϱ߽�
	pt[1].x = p1.x + (m_clipRect.m_max.y - p1.y) / m;
	pt[1].y = m_clipRect.m_max.y;
	s[1]= Vector3::Dot(Vector3(0, -1, 0), pt[1]);

	//�ұ߽�
	pt[2].x = m_clipRect.m_max.x;
	pt[2].y = p1.y + m * (m_clipRect.m_max.x - p1.x);
	s[2] = Vector3::Dot(Vector3(-1, 0, 0), pt[2]);

	//�±߽�
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




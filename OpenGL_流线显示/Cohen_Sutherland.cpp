#include "Cohen_Sutherland.h"



Cohen_Sutherland::Cohen_Sutherland()
{
	m_isRender = true;
}


Cohen_Sutherland::~Cohen_Sutherland()
{

}

void Cohen_Sutherland::Render()
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

void Cohen_Sutherland::SetInput(Vector3 beginPos, Vector3 endPos, Rect clipRect)
{
	m_beginPos	= beginPos;
	m_endPos	= endPos;
	m_clipRect	= clipRect; 
	m_beginPosMark	= GetMark(m_beginPos);
	m_endPosMark	= GetMark(m_endPos);
}


void Cohen_Sutherland::Update()
{
	
	//1.边界内
	if ((m_beginPosMark | INCLUPMARK) == 0 && (m_endPosMark | INCLUPMARK) == 0)
	{
		return;
	}
	//边界外
	if (m_beginPosMark & m_endPosMark)
	{
		m_isRender = false;
		return;
	}
	//不可确定部分
	m_beginPos = Caculate(m_beginPos, m_beginPosMark);
	m_endPos = Caculate(m_endPos, m_endPosMark);

}
unsigned char Cohen_Sutherland::GetMark(Vector3 pos)
{
	unsigned char mark =0;
	if (m_clipRect.isInRect(pos))
	{
		mark |= 0;
	}
	//上边界
	if (m_clipRect.m_max.y < pos.y)
		mark |= UPMARK;
	//下边界
	if (m_clipRect.m_min.y > pos.y)
		mark |= DOWNMARK;
	//左边界
	if (m_clipRect.m_min.x > pos.x)
		mark |= LEFTMARK;
	//右边界
	if (m_clipRect.m_max.x < pos.x)
		mark |= RIGHTMARK;
	return mark;
}


Vector3 Cohen_Sutherland:: Caculate(Vector3 pos, unsigned char& mark)
{
	Vector3 outPos	= pos;
	float dertaX	= m_endPos.x - m_beginPos.x;
	float dertaY	= m_endPos.y - m_beginPos.y;

	float m			= dertaY / dertaX;
	//上边界计算
	float y = 0;
	float x = 0;
	if (mark & UPMARK)
	{
		x = pos.x + (m_clipRect.m_max.y - pos.y)/m;
		outPos.x =  x;
		outPos.y = m_clipRect.m_max.y;
		mark = GetMark(outPos);
	}
	if (mark & RIGHTMARK)
	{
		y = pos.y + m * (m_clipRect.m_max.x - pos.x);
		outPos.x = m_clipRect.m_max.x;
		outPos.y = y;
		mark = GetMark(outPos);
	}
	if (mark & DOWNMARK)
	{
		x = pos.x + (m_clipRect.m_min.y - pos.y) / m;
		outPos.x = x;
		outPos.y = m_clipRect.m_min.y;
		mark = GetMark(outPos);
	}
	if (mark & LEFTMARK)
	{
		y = pos.y + m * (m_clipRect.m_min.x - pos.x);
		outPos.x = m_clipRect.m_min.x;
		outPos.y = y;
		mark = GetMark(outPos);
	} 
	return outPos;
}
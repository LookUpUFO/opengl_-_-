#include "NormalClip.h"

void NormalClipClass::Render()
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
void NormalClipClass::SetInput(Vector3 beginPos, Vector3 endPos, Rect clipRect)
{
	m_beginPos = beginPos;
	m_endPos = endPos;
	m_clipRect = clipRect;

	m_lineDir = m_endPos - m_beginPos;

}

void NormalClipClass::Update()
{
	//1.�˵�ȫ�ڲü���
	if (m_clipRect.isInRect(m_beginPos) && m_clipRect.isInRect(m_endPos))
	{
		m_isRender = true;
		return;
	}
	//���ÿ���߽磬����Ƿ�ȫ�ڱ߽���
	//1.��߽�
	if (m_clipRect.m_min.x > m_beginPos.x  && m_clipRect.m_min.x > m_endPos.x)
	{
		m_isRender = false;
		return;
	}
	//�ұ߽�
	if (m_clipRect.m_max.x < m_beginPos.x  && m_clipRect.m_max.x < m_endPos.x)
	{
		m_isRender = false;
		return;
	}
	//�ϱ߽�
	if (m_clipRect.m_max.y < m_beginPos.y  && m_clipRect.m_max.y < m_endPos.y)
	{
		m_isRender = false;
		return;
	}
	//�±߽�
	if (m_clipRect.m_min.y > m_beginPos.y  && m_clipRect.m_min.y > m_endPos.y)
	{
		m_isRender = false;
		return;
	}



	//��߽�
	float u = (m_clipRect.m_min.x - m_beginPos.x) / (m_lineDir.x);
	bool isLeftValidFoce = false;
	Vector3 leftValidPos;
	//�ཻ���󽻵�
	if (0 < abs(u) && abs(u) < 1)
	{
		//������߽��yֵ
		float y = m_beginPos.y + u * (m_lineDir.y);
		if (m_clipRect.m_max.y > y && m_clipRect.m_min.y < y)
		{
			isLeftValidFoce = true;
			leftValidPos = Vector3(m_clipRect.m_min.x, y);
		}
	}
	//�ұ߽�
	u = (m_clipRect.m_max.x - m_beginPos.x) / (m_lineDir.x);
	bool isRightValidFoce = false;
	Vector3 rightValidPos;
	//�ཻ���󽻵�
	if (0 < abs(u) && abs(u) < 1)
	{
		//������߽��yֵ
		float y = m_beginPos.y + u * (m_lineDir.y);
		if (m_clipRect.m_max.y > y && m_clipRect.m_min.y < y)
		{
			isRightValidFoce = true;
			rightValidPos = Vector3(m_clipRect.m_max.x, y);
		}
	}
	//�±߽�
	u = (m_clipRect.m_min.y - m_beginPos.y) / (m_lineDir.y);
	bool isdownValidFoce = false;
	Vector3 downValidPos;
	//�ཻ���󽻵�
	if (0 < abs(u) && abs(u) < 1)
	{
		//������߽��yֵ
		float x = m_beginPos.x + u * (m_lineDir.x);
		if (m_clipRect.m_max.x > x && m_clipRect.m_min.x < x)
		{
			isdownValidFoce = true;
			downValidPos = Vector3(x, m_clipRect.m_min.y);
		}
	}
	//�ϱ߽�
	u = (m_clipRect.m_max.y - m_beginPos.y) / (m_lineDir.y);
	bool isUpValidFoce = false;
	Vector3 upValidPos;
	//�ཻ���󽻵�
	if (0 < abs(u) && abs(u) < 1)
	{
		//������߽��yֵ
		float x = m_beginPos.x + u * (m_lineDir.x);
		if (m_clipRect.m_max.x > x && m_clipRect.m_min.x < x)
		{
			isUpValidFoce = true;
			upValidPos = Vector3(x, m_clipRect.m_max.y);
		}
	}

	//�ҵ�����������
	Vector3 endPos;
	Vector3 beinPos;
	bool endisUsed = false;
	bool beinisUsed = false;
	if (isLeftValidFoce)
	{
		endPos = leftValidPos;
		endisUsed = true;
	}
	if (isRightValidFoce)
	{
		if (endisUsed)
		{
			beinPos = rightValidPos;
			beinisUsed = true;
		}
		else
		{
			endPos = rightValidPos;
			endisUsed = true;
		}
	}
	if (isdownValidFoce)
	{
		if (!endisUsed && !beinisUsed)
			if (endisUsed)
			{
				beinPos = downValidPos;
				beinisUsed = true;
			}
			else
			{
				endPos = downValidPos;
				endisUsed = true;
			}
	}
	if (isUpValidFoce)
	{
		if (!endisUsed && !beinisUsed)
			if (endisUsed)
			{
				beinPos = upValidPos;
				beinisUsed = true;
			}
			else
			{
				endPos = upValidPos;
				endisUsed = true;
			}
	}
	if (endisUsed && beinisUsed)
	{
		m_endPos = endPos;
		m_beginPos = beinPos;
		return;
	}
	//�ж��ĸ��˵��ڷ�Χ��
	if (m_clipRect.isInRect(m_beginPos))
	{
		m_endPos = endPos;
		return;
	}
	if (m_clipRect.isInRect(m_endPos))
	{
		m_beginPos = endPos;
		return;
	}
	return;

}

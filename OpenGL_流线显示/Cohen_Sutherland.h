#pragma once
#include "IRender.h"
class Cohen_Sutherland :
	public IRender
{
public:
	Cohen_Sutherland();
	~Cohen_Sutherland();

	// Í¨¹ý IRender ¼Ì³Ð
	virtual void Render() override;
	virtual void SetInput(Vector3 beginPos, Vector3 endPos, Rect clipRect) override;
	virtual void Update() override;
private:
	Vector3 m_beginPos;
	Vector3 m_endPos;
	Rect m_clipRect;

	unsigned char	m_beginPosMark;
	unsigned char	m_endPosMark;

	unsigned char GetMark(Vector3 pos);

	const unsigned char INCLUPMARK = 0;
	const unsigned char UPMARK		= 1 << 3;
	const unsigned char DOWNMARK	= 1 << 2;
	const unsigned char LEFTMARK	= 1 << 0;
	const unsigned char RIGHTMARK	= 1 << 1;

	bool m_isRender;

	Vector3  Caculate(Vector3 pos, unsigned char& mark);
};


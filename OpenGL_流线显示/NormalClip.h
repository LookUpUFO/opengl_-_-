#pragma once
#include "IRender.h"

using namespace WHQ;

class NormalClipClass :public IRender
{ 
public: 
	void Render() override;

	void SetInput(Vector3 beginPos , Vector3 endPos , Rect clipRect) override;
	void Update() override;

	Vector3 m_beginPos;
	Vector3 m_endPos;	
	Rect m_clipRect;

	Vector3 m_lineDir;
	bool m_isRender;
	NormalClipClass()
	{
		m_isRender = true;
	}
};


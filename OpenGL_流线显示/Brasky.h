#pragma once
#include "IRender.h"
class Brasky :
	public IRender
{
public:
	Brasky();
	~Brasky();

	// ͨ�� IRender �̳�
	virtual void Render() override;
	virtual void SetInput(Vector3 beginPos, Vector3 endPos, Rect clipRect) override;
	virtual void Update() override;
private:
	Vector3 m_beginPos;
	Vector3 m_endPos;
	Rect m_clipRect;
	bool m_isRender;
};


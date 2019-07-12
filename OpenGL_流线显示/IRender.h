#pragma once
#include "../math_Lib/Matrix.h"

#include "glew/glew.h"

using namespace WHQ;
class IRender 
{
public:
	void virtual Render() =0 ;
	void virtual SetInput(Vector3 beginPos, Vector3 endPos, Rect clipRect) =0;
	void  virtual Update() =0;
};
 

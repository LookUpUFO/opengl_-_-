#pragma once
#include "../math_Lib/Matrix.h"
#include "PointClound.h"
#include "Mesh.h"
#include "GlobalDefine.h"


//typedef linePoint MeshPoint;

struct MeshPoint  
{
	Attribute m_attribute;
	Vector3  m_position;
};
class MarchingCube
{

public:
	MarchingCube();
	~MarchingCube();

public: 
	void SetInput(std::shared_ptr<PointClound > pPointClound, float thresholdMax , float thresholdMin);
	void Update();
	Mesh GetOutPut();


private:
		std::shared_ptr<PointClound > m_pPointClound;
		float m_thresholdMax;
		float m_thresholdMin;
		Mesh  m_mesh;
};
typedef unsigned char byte;
#define null  NULL 




class CubeCell
{
public:
	  const byte VULF = 1 << 0;
	  const byte VULB = 1 << 1;
	  const byte VLLB = 1 << 2;
	  const byte VLLF = 1 << 3;
	  const byte VURF = 1 << 4;
	  const byte VURB = 1 << 5;
	  const byte VLRB = 1 << 6;
	  const byte VLRF = 1 << 7;

	   const byte PointIndexToFlag[8]
	  {
			  VULF,
			  VULB,
			  VLLB,
			  VLLF,
			  VURF,
			  VURB,
			  VLRB,
			  VLRF
	  };

	  CubeCell()
	{
		 
		// edgesArray = new List<int[]>(10);
		////ValidArray = new List<MeshPoint>(10);

	}

	~CubeCell()
	{
		 
		edgesArray.clear();
		 

		m_validPositionArray.clear();
		 
	}
	const Point* cubePoint[8];
	float m_thresholdValueMax;
	float m_thredSholdValueMin;
	bool isValidInput;

	byte m_Flag;
	void SetInput(const Point* leftUpFrontPoint, float thresholdValueMax, float thredSholdValueMin); 
	void UpDate();
	

	std::list<MeshPoint>& GetOutPut();
 

	std::list<int*> edgesArray;
	std::list<MeshPoint> m_validPositionArray;
	/// <summary>
	/// 获取一个cube的有效边所在的顶点
	/// </summary>
	/// <returns></returns>
	void GetValidEdge();



	//边信息
	static const   int  EdgeIndexToEdgeVertexIndex[12][2];
 


 private:
//查询表
	 static  const  int TriTable[256][16];
};

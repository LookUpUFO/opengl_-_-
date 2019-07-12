#include "StreamLineFilter.h"

void StreamLineFilter::SetInput(std::shared_ptr<PointClound > pPointClound)
{
	m_pPointClound = pPointClound;
	m_isThreedD = m_pPointClound->IsThreedD();


}


void StreamLineFilter::Update(int beginX, int beginY, int beginZ, float step)
{
	m_step = step;
	//获取第一个网格数据
	const Point * nextPoint ,* lastNextPoint;

	nextPoint =( m_pPointClound->GetPoint(beginX, beginY, beginZ));
	   
	linePoint nextPos (nextPoint->m_position, nextPoint->m_attribute.m_speed);

	int loopCount = 0;
	lastNextPoint = nextPoint;

	 
	while (nextPoint != nullptr)
	{
		//1.保存计算前的坐标	
		m_positonArray.push_back(nextPos.m_position);

		//开始计算
		nextPoint = RungeKutta(nextPos, nextPoint);		
		
		
		//3.判断是否为是涡流，即死循环
		loopCount++;
		if (lastNextPoint != nextPoint)
			loopCount = 0;
		if(loopCount>5000)
			break;
		/*if (!m_pPointClound->isInCube(nextPos.m_position, nextPoint))
			return; */
		lastNextPoint = nextPoint;

		//2.保存计算后坐标点 
		//std::cout << nextPos.m_position.x << "," << nextPos.m_position.y << "," << nextPos.m_position.z << endl; 
		m_positonArray.push_back(nextPos.m_position*20);
	}
}

std::vector<Vector3> StreamLineFilter::GetOutPut()
{
	return m_positonArray;
}

const std::vector<Vector3>& StreamLineFilter::GetCloundPoint()
{
	 

	return m_positonArray;
}


//计算下一个坐标点
const Point   *  StreamLineFilter::RungeKutta(IN OUT linePoint& currentPos,  IN const  Point  *  basePos, bool isInverse )
{
	linePoint p2;
	p2.m_speed = currentPos.m_speed.Normal(); 
	float c = m_step * p2.m_speed.Length();
	p2.m_position = currentPos.m_position + p2.m_speed *c;//currentPos.m_position + p2.m_speed; //

	auto temp = DeviatCalculateDir(basePos, p2);
	 
	p2.m_position = currentPos.m_position +  (p2.m_speed + currentPos.m_speed) * c*0.5f;
	if (isInverse)
	{
		p2.m_speed = Vector3::Zero() - p2.m_speed;
	}
	if (!m_isThreedD)
		p2.m_speed.z = 0;

	currentPos = p2;


	

	return temp;
}

const Point * StreamLineFilter::DeviatCalculateDir(IN  const  Point * basePos, OUT linePoint& currentPos)
{
	if ( m_isThreedD)
	{
		return DeviatCalculateDir3D(basePos, currentPos);
	}
	else
	{
		return DeviatCalculateDir2D(basePos, currentPos); 
	}
}
//差值计算当前点方向
const Point * StreamLineFilter::DeviatCalculateDir2D(IN const  Point * basePos, OUT linePoint& currentPos)
{
	linePoint baseUpFrontVector;
	baseUpFrontVector.m_position = Vector3::Zero();
	linePoint baseFrontVector;
	baseFrontVector.m_position = Vector3::Zero();
	linePoint baseRightFrontVector;
	baseRightFrontVector.m_position = Vector3::Zero();
	linePoint baseRightUpFrontVector;
	baseRightUpFrontVector.m_position = Vector3::Zero();

	 



	const Point  *temp = basePos;

	while (temp != NULL)
	{ 
		if (temp->m_upPoint != NULL)
		{
			baseUpFrontVector = linePoint(temp->m_upPoint->m_position, temp->m_upPoint->m_attribute.m_speed);

			if (baseUpFrontVector.m_position.y < currentPos.m_position.y)
			{
				temp = temp->m_upPoint;
				continue;
			}
		}
		else
		{
			break;
		}

		baseFrontVector = linePoint(temp->m_position, temp->m_attribute.m_speed);

		if (baseFrontVector.m_position.y > currentPos.m_position.y)
		{
			temp = temp->m_downPoint;
			continue;
		}
		if (baseFrontVector.m_position.x > currentPos.m_position.x)
		{
			temp = temp->m_leftPoint;
			continue;
		}
		if (baseFrontVector.m_position.z > currentPos.m_position.z)
		{
			temp = temp->m_frontPoint;
			continue;
		}


		if (temp->m_rightPoint != NULL)
		{
			baseRightFrontVector = linePoint(temp->m_rightPoint->m_position, temp->m_rightPoint->m_attribute.m_speed);
			if (baseRightFrontVector.m_position.x < currentPos.m_position.x)
			{
				temp = temp->m_rightPoint;
				continue;
			}
		}
		else
		{
			break;
		}


		baseUpFrontVector = linePoint(temp->m_upPoint->m_position, temp->m_upPoint->m_attribute.m_speed); //temp.m_UpPoint.m_BigCubeVertex[temp.m_UpPoint.m_pointIndex];
		baseFrontVector = linePoint(temp->m_position, temp->m_attribute.m_speed);// temp.m_BigCubeVertex[temp.m_pointIndex];
		baseRightFrontVector = linePoint(temp->m_rightPoint->m_position, temp->m_rightPoint->m_attribute.m_speed); //temp.m_RightPoint.m_BigCubeVertex[temp.m_RightPoint.m_pointIndex];
		baseRightUpFrontVector = linePoint(temp->m_rightPoint->m_upPoint->m_position, temp->m_rightPoint->m_upPoint->m_attribute.m_speed); //temp.m_RightPoint.m_UpPoint.m_BigCubeVertex[temp.m_RightPoint.m_UpPoint.m_pointIndex];
 

		float x2 = baseRightFrontVector.m_position.x;
		float x1 = baseFrontVector.m_position.x;
		float x = currentPos.m_position.x;
		float y2 = baseUpFrontVector.m_position.y;

		float y = currentPos.m_position.y;
		float y1 = baseFrontVector.m_position.y;


		Vector3 Fq11 = baseFrontVector.m_speed;
		Vector3 Fq21 = baseRightFrontVector.m_speed;
		Vector3 Fq12 = baseUpFrontVector.m_speed;
		Vector3 Fq22 = baseRightUpFrontVector.m_speed;

		auto R1 = Fq11 * (x2 - x) / (x2 - x1) + Fq21 * (x - x1) / (x2 - x1);
		auto R2 = Fq12 * (x2 - x) / (x2 - x1) + Fq22 * (x - x1) / (x2 - x1);
		auto Fp_front = R1 * (y2 - y) / (y2 - y1) + R2 * (y - y1) / (y2 - y1);


		////x2 = baseRightBackVector.m_position.x;
		////x1 = baseBackVector.m_position.x;
		//x = currentPos.m_position.x;
		////y2 = baseUpBackVector.m_position.y;
		//y = currentPos.m_position.y;
		////y1 = baseBackVector.m_position.y;

		//Fq11 = baseFrontVector.m_speed;
		//Fq21 = baseRightFrontVector.m_speed;
		//Fq12 = baseUpFrontVector.m_speed;
		//Fq22 = baseRightUpFrontVector.m_speed;

		//R1 = Fq11 * (x2 - x) / (x2 - x1) + Fq21 * (x - x1) / (x2 - x1);
		//R2 = Fq12 * (x2 - x) / (x2 - x1) + Fq22 * (x - x1) / (x2 - x1);
		//auto Fp_back = R1 * (y2 - y) / (y2 - y1) + R2 * (y - y1) / (y2 - y1);

		//float z1 = baseFrontVector.m_position.z;
		//float z = currentPos.m_position.z;
		//float z2 = baseBackVector.m_position.z;

		//auto Fp = Fp_front * std::fabsf((z1 - z) / (z2 - z1)) + Fp_back * std::fabsf((z - z2) / (z2 - z1));

		currentPos.m_speed = Fp_front;

		return temp;

	}
	return NULL;
}


//差值计算当前点方向
const Point * StreamLineFilter::DeviatCalculateDir3D(IN const  Point * basePos, OUT linePoint& currentPos)
{
	linePoint baseUpFrontVector;
	baseUpFrontVector.m_position		= Vector3::Zero();
	linePoint baseFrontVector;
	baseFrontVector.m_position			= Vector3::Zero();
	linePoint baseRightFrontVector;
	baseRightFrontVector.m_position		= Vector3::Zero();
	linePoint baseRightUpFrontVector;
	baseRightUpFrontVector.m_position	= Vector3::Zero();

	linePoint baseUpBackVector;
	baseUpFrontVector.m_position		= Vector3::Zero();
	linePoint baseBackVector;
	baseFrontVector.m_position			= Vector3::Zero();
	linePoint baseRightBackVector;
	baseRightFrontVector.m_position		= Vector3::Zero();
	linePoint baseRightUpBackVector;
	baseRightUpFrontVector.m_position	= Vector3::Zero();

	 

	const Point  *temp=  basePos;

	while (temp != NULL)
	{
		if (temp->m_backPoint != NULL)
		{
			baseBackVector = linePoint(temp->m_backPoint->m_position, temp->m_backPoint->m_attribute.m_speed);

			if (baseBackVector.m_position.z < currentPos.m_position.z)
			{
				temp = temp->m_backPoint;
				continue;
			}
		}
		else
		{
			break;
		}



		if (temp->m_upPoint != NULL)
		{
			baseUpFrontVector = linePoint(temp->m_upPoint->m_position , temp->m_upPoint->m_attribute.m_speed);

			if (baseUpFrontVector.m_position.y < currentPos.m_position.y)
			{
				temp = temp->m_upPoint;
				continue;
			}
		}
		else
		{
			break;
		}
	 
		baseFrontVector = linePoint(temp->m_downPoint->m_position, temp->m_downPoint->m_attribute.m_speed);

		if (baseFrontVector.m_position.y > currentPos.m_position.y)
		{
			temp = temp->m_downPoint;
			continue;
		}
		if (baseFrontVector.m_position.x > currentPos.m_position.x)
		{
			temp = temp->m_leftPoint;
			continue;
		}
		if (baseFrontVector.m_position.z > currentPos.m_position.z)
		{
			temp = temp->m_frontPoint;
			continue;
		}


		if (temp->m_rightPoint != NULL)
		{
			baseRightFrontVector = linePoint(temp->m_rightPoint->m_position,temp->m_rightPoint->m_attribute.m_speed);
			if (baseRightFrontVector.m_position.x < currentPos.m_position.x)
			{
				temp = temp->m_rightPoint;
				continue;
			}
		}
		else
		{
			break;
		}


		baseUpFrontVector = linePoint(temp->m_upPoint->m_position, temp->m_upPoint->m_attribute.m_speed); //temp.m_UpPoint.m_BigCubeVertex[temp.m_UpPoint.m_pointIndex];
		baseFrontVector = linePoint(temp->m_position ,temp->m_attribute.m_speed);// temp.m_BigCubeVertex[temp.m_pointIndex];
		baseRightFrontVector = linePoint(temp->m_rightPoint->m_position, temp->m_rightPoint->m_attribute.m_speed); //temp.m_RightPoint.m_BigCubeVertex[temp.m_RightPoint.m_pointIndex];
		baseRightUpFrontVector = linePoint(temp->m_rightPoint->m_upPoint->m_position, temp->m_rightPoint->m_upPoint-> m_attribute.m_speed); //temp.m_RightPoint.m_UpPoint.m_BigCubeVertex[temp.m_RightPoint.m_UpPoint.m_pointIndex];
		
		baseUpBackVector = linePoint(temp->m_upPoint->m_backPoint->m_position, temp->m_upPoint->m_backPoint->m_attribute.m_speed); //temp.m_UpPoint.m_BackPoint.m_BigCubeVertex[temp.m_UpPoint.m_BackPoint.m_pointIndex];
		baseBackVector = linePoint(temp->m_backPoint->m_position, temp->m_backPoint->m_attribute.m_speed); //temp.m_BackPoint.m_BigCubeVertex[temp.m_BackPoint.m_pointIndex];
		baseRightBackVector = linePoint(temp->m_rightPoint->m_backPoint->m_position, temp->m_rightPoint->m_backPoint->m_attribute.m_speed);// temp.m_RightPoint.m_BackPoint.m_BigCubeVertex[temp.m_RightPoint.m_BackPoint.m_pointIndex];
		baseRightUpBackVector = linePoint(temp->m_upPoint-> m_rightPoint->m_backPoint->m_position, temp->m_upPoint->m_rightPoint->m_backPoint->m_attribute.m_speed); //temp.m_UpPoint.m_RightPoint.m_BackPoint.m_BigCubeVertex[temp.m_UpPoint.m_RightPoint.m_BackPoint.m_pointIndex];


		//  float length_x = Mathf.Abs(baseFrontVector.pos.x - baseRightFrontVector.pos.x);
		//  float length_y = Mathf.Abs(baseFrontVector.pos.y - baseUpFrontVector.pos.y);
		//  float length_z = Mathf.Abs(baseFrontVector.pos.z - baseBackVector.pos.z);

		float x2 = baseRightFrontVector.m_position.x;
		float x1 = baseFrontVector.m_position.x;
		float x = currentPos.m_position.x;
		float y2 = baseUpFrontVector.m_position.y;
		float y = currentPos.m_position.y;
		float y1 = baseFrontVector.m_position.y;


		Vector3 Fq11 = baseFrontVector.m_speed;
		Vector3 Fq21 = baseRightFrontVector.m_speed;
		Vector3 Fq12 = baseUpFrontVector.m_speed;
		Vector3 Fq22 = baseRightUpFrontVector.m_speed;

		auto R1			= Fq11*(x2 - x) / (x2 - x1)		+ Fq21*(x - x1) / (x2 - x1)  ;
		auto R2			= Fq12 *(x2 - x) / (x2 - x1)	+ Fq22*(x - x1) / (x2 - x1) ;
		auto Fp_front	= R1*(y2 - y) / (y2 - y1) + R2*(y - y1) / (y2 - y1) ;


		x2 = baseRightBackVector.m_position.x;
		x1 = baseBackVector.m_position.x;
		x = currentPos.m_position.x;
		y2 = baseUpBackVector.m_position.y;
		y = currentPos.m_position.y;
		y1 = baseBackVector.m_position.y;

		Fq11 = baseFrontVector.m_speed;
		Fq21 = baseRightFrontVector.m_speed;
		Fq12 = baseUpFrontVector.m_speed;
		Fq22 = baseRightUpFrontVector.m_speed;

		R1 = Fq11*(x2 - x) / (x2 - x1)  + Fq21*(x - x1) / (x2 - x1) ;
		R2 = Fq12*(x2 - x) / (x2 - x1) + Fq22*(x - x1) / (x2 - x1) ;
		auto Fp_back = R1*(y2 - y) / (y2 - y1) + R2*(y - y1) / (y2 - y1) ;

		float z1 = baseFrontVector.m_position.z;
		float z = currentPos.m_position.z;
		float z2 = baseBackVector.m_position.z;

		auto Fp = Fp_front* std::fabsf((z1 - z) / (z2 - z1))   + Fp_back*std::fabsf((z - z2) / (z2 - z1)) ;

		currentPos.m_speed = Fp;

		return temp;

	}
	return NULL; 
}
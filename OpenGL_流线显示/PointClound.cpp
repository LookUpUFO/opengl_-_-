#include "PointClound.h"


//template <class T>
PointClound ::PointClound()
{

}



//template <class T>
PointClound ::~PointClound()
{
	m_pointList.clear();
}

//template<class T>
Point  PointClound ::GetFirstPos()
{
	auto begin = m_pointList.front();
	return  begin;
}

bool PointClound::isInCube(Vector3 pos,const Point *point) 
{
	if (point == NULL)
		return false;
	if (point->m_rightPoint != NULL)
		if (pos.x > point->m_rightPoint->m_position.x || pos.x < point->m_position.x)
			return false;
	if (point->m_upPoint != NULL)
		if (pos.y > point->m_upPoint->m_position.y || pos.y < point->m_position.y)
			return false;

	if (IsThreedD())
	{
		if (point->m_backPoint != NULL)
			if (pos.z > point->m_backPoint->m_position.z || pos.z < point->m_position.z)
				return false; 
	}
	return true;
}

//规定数据先x变化，在y变化，在z变化 
//template<class T>
void PointClound ::SetInput(std::vector<Point >& pointList, int xLength, int yLength, int zLength)
{
	//数据不符
	if (pointList.size() != xLength * yLength*zLength)
		return;

	m_xLoop = xLength;
	m_yLoop = yLength;
	m_zLoop = zLength;

	m_pointList.resize(pointList.size());
	//判断点云变化顺序
	Int count = 0;
	auto itear = pointList.begin();

	//Point  * pleftPoint = nullptr;
	//建立点之间的关系网

	
	for (Int z = 0; z < zLength; z++)
	{

		for (Int y = 0; y < yLength; y++)
		{
			for (Int x = 0; x < xLength; x++, itear++, count++)
			{
				m_pointList[count]=(*itear);
				Point  * pleftCurrentPos = &m_pointList[count]; 
				if (x > 0)
				{

					Point  *pleftPoint = &m_pointList[count - 1];
					//按照从左至右增大顺序排列
					if (pleftPoint->m_position.x <= pleftCurrentPos->m_position.x)
					{
						pleftPoint->m_rightPoint		= pleftCurrentPos;
						pleftCurrentPos->m_leftPoint	= pleftPoint;
						m_endPoint = pleftCurrentPos;
					}									  
					else								  
					{									  
						pleftCurrentPos->m_rightPoint	= pleftPoint;
						pleftPoint->m_leftPoint			= pleftCurrentPos;
						m_endPoint = pleftPoint;
					}
				}
				////由下至上增大
				if (y > 0 )
				{

					Point  * pdownCurrentPos = &m_pointList[count];
					Point  * pdownPoint = &m_pointList[count- xLength];
					if (pdownCurrentPos->m_position.y >= pdownPoint->m_position.y)
					{
						pdownCurrentPos->m_downPoint = pdownPoint;
						pdownPoint->m_upPoint = pdownCurrentPos;
						m_endPoint = pdownCurrentPos;
					}
					else
					{
						pdownCurrentPos->m_upPoint = pdownPoint;
						pdownPoint->m_downPoint = pdownCurrentPos;
						m_endPoint = pdownPoint;
					}
					 
				}

				//由外到内增大
				if (z > 0)
				{
					Point  * pcurrentPos = &m_pointList[z*yLength*xLength + y * xLength + x];
					Point  * plastPoint = &m_pointList[(z - 1)*yLength*xLength + y * xLength + x];
					if (pcurrentPos->m_position.z >= plastPoint->m_position.z)
					{
						pcurrentPos->m_frontPoint	= plastPoint;
						plastPoint->m_backPoint		=pcurrentPos;

						m_endPoint = pcurrentPos;
					}
					else
					{
						pcurrentPos->m_backPoint	=plastPoint;
						plastPoint->m_frontPoint	=pcurrentPos;
						m_endPoint = plastPoint;
					}
				} 
				//pleftPoint = pleftCurrentPos;
			}
			//pleftPoint = nullptr;

		}

	}

	m_beinPoint = m_endPoint;
	for (Int z = 0; z < zLength-1 && IsThreedD(); z++)
	{
		m_endPoint = m_endPoint->m_frontPoint;
	}
	
	for (Int x = 0; x < xLength-1; x++)
	{
		m_beinPoint = m_beinPoint->m_leftPoint;
	}
	for (Int y = 0; y < yLength-1; y++)
	{
		m_beinPoint = m_beinPoint->m_downPoint;
	} 
}

//template<class T>
const Point * PointClound ::GetPoint(int x , int y, int z)
{

	const Point * p = m_beinPoint;
	for (int iz = 0; iz < z; iz++)
	{
		p = p->m_frontPoint;
	}
	for (int iy = 0; iy < y; iy++)
	{
		p = p->m_upPoint;
	}
	for (int ix = 0; ix < x; ix++)
	{
		p = p->m_rightPoint;
	}
	 
	return p;

}

//template<class T>
bool PointClound ::IsThreedD()
{
	return  m_xLoop>2 && m_yLoop>2 && m_zLoop>2;
}

//template<class T>
inline Point ::Point( Vector3 pos, Attribute attribute)
{
	m_attribute = attribute;
	m_position = pos;
	Point();
}


//template<class T>
Point ::Point()
{
	m_leftPoint = NULL;
	m_rightPoint = NULL;
	m_downPoint = NULL;
	m_upPoint = NULL;
	m_frontPoint = NULL;
	m_backPoint = NULL;
	
}

#include <iostream>
#include "glew/glew.h"
//#include "Draw.h" 
#include <freeglut.h>
#include "stb_image.h"
#include <vector>

#include "../math_Lib/Matrix.h"
#include <math.h> 
#include "NormalClip.h"
#include "Cohen_Sutherland.h"
#include "Brasky.h"

#include "StreamLineFilter.h"
#include <fstream>

#include "MarchingCube.h"

using namespace  WHQ;
 
std::list<  Mesh > streamLine(string path);

GLint width = 100;
GLint height = 150;
IRender * g_render;



void ShowClipZone(Rect rect)
{
	glColor3f(0, 0, 0);
	float offset = 0;
	glBegin(GL_LINE_STRIP);
	glVertex2f(rect.m_min.x+ offset, rect.m_min.y+ offset);
	glVertex2f(rect.m_min.x+ offset, rect.m_max.y- offset);

	glVertex2f(rect.m_max.x- offset, rect.m_max.y- offset);
	glVertex2f(rect.m_max.x - offset, rect.m_min.y+ offset);
	glVertex2f(rect.m_min.x + offset, rect.m_min.y + offset);

	glEnd();
	glFlush();
	 
}

std::list< Mesh > pmeshArray;

GLuint vbo = 0;

void init()
{ 
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	
	//设置裁剪区域
	//gluOrtho2D(0, 9, -3, 3);
	glOrtho(0, 9, -3, 3, -10, 10);

	glMatrixMode(GL_MODELVIEW);
 

	pmeshArray = streamLine("E:\\9hz_lamdaci_0001.dat");
	 

}
static GLfloat angle = 0.0f;   
 
void RenderLoop()
{
	//设置适口
	//设置适口
	//glViewport(0, 0, 200, 100);

	glClearColor(1, 1, 1,1);
	glClear(GL_COLOR_BUFFER_BIT);	
 
	 
	glColor3f(0, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer( 3, GL_FLOAT, sizeof(Vector3), &(pmeshArray.front().m_vertexArrar[0]));
	glDrawArrays(GL_POINTS, 0, pmeshArray.front().m_vertexArrar.size());
	
	glFlush();



}

void OnReshapeWindowFunc(int width, int height)
{
	std::cout << width << "," << height << endl;
	//glOrtho(0, width, -3, height, -10, 10);
	glViewport(0, 0, width, height);
}


int main(int argc , char ** argv)
{
	 
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 300);
	glutCreateWindow("Display OpenGL");
	glewInit();
	init(); 

	glutDisplayFunc(RenderLoop);
	glutReshapeFunc(OnReshapeWindowFunc);
	glutMainLoop( );
 
	return 0;

}


float String2Number(string& s);
std::vector<std::string> s_split(const std::string& in, const std::string& delim);

#include <regex>
#include <sstream>
#include "PointClound.h"


std::list< Mesh  > streamLine(string path)
{
	//文件读取
	std::ifstream reader;
	reader.open(path);
	char dataBuffer[1000];
 
	int titleCount = 2;
	while (titleCount)
	{
		reader.getline(dataBuffer, 1000); 
		cout << dataBuffer << std::endl;
		titleCount--;
	}
	//system("cls");
	const int xloop = 100;
	const int yloop = 56;
	const int zloop = 24;

	//数据读取
	int contentSize = xloop*yloop*zloop;//100 * 56 * 24;
	 
	Point point;
	Attribute attribute;
	vector<Point> pointList;
	pointList.resize(contentSize);

	vector<string> numberArray;
	int lineCount = 0;
	while (contentSize)
	{
		reader.getline(dataBuffer, 1000);
	
	
	 	string line(dataBuffer); 
		//std::regex e("[\t\\s]+");
		//line = std::regex_replace(line, e, ",");
		int count =0;
		char s[10] = {'\0','\0'};
		//s.resize(8);
		char lastChar= '\0';
		int charCount = 0;
		while (true)
		{
			
			if (dataBuffer[count] != ' ' && dataBuffer[count] !='\t' )
			{
				char t = dataBuffer[count];
				s[charCount++] = t;
			}
			else if ((dataBuffer[count] == ' ' || dataBuffer[count] == '\t') && lastChar != dataBuffer[count] )
			{
				numberArray.push_back(s);
				//s.clear();
				charCount = 0;
				std::memset(s, '\0', 10);
			}
			lastChar = dataBuffer[count];
			count++;
			if (dataBuffer[count] == '\r' || dataBuffer[count] == '\n' || dataBuffer[count] == '\0')
			{
				numberArray.push_back(s);
				break;
			}
		}
	  
		Vector3 pos;
		pos.x = String2Number(numberArray[0]);
		pos.y = String2Number(numberArray[1]);
		pos.z = String2Number(numberArray[2]);


		attribute.m_speed.x = String2Number(numberArray[3]);
		attribute.m_speed.y = String2Number(numberArray[4]);
		attribute.m_speed.z = String2Number(numberArray[5]);

		attribute.m_pressure = String2Number(numberArray[9]); //attribute.m_speed.Length();

		point.m_position = pos;
		point.m_attribute = attribute;


		pointList[lineCount++]=(point);

		numberArray.clear();
		contentSize--;
	}
	cout << "pointList Count =" << pointList.size() << endl;
	reader.close();

	std::shared_ptr<PointClound> pc = std::make_shared<PointClound>();
	pc->SetInput(pointList,xloop,yloop,zloop);

	StreamLineFilter lineFilter;
	lineFilter.SetInput(pc);
	std::list<  Mesh  > lishMesh;
	//for (int k = 0; k < 22; k++)
	//{
	//	lineFilter.Update(k, 25, 0, 0.025f);
	//	std::shared_ptr< Mesh> mesh = std::make_shared<Mesh>();
	//	mesh->m_vertexArrar = lineFilter.GetOutPut();
	//	lishMesh.push_back(mesh);
	//}


	MarchingCube cube;
	cube.SetInput(pc,22,0);
	cube.Update();
	lishMesh.push_back(cube.GetOutPut());

	 


	return lishMesh;

}


std::vector<std::string> s_split(const std::string& in, const std::string& delim) 
{
	std::regex re{ delim };
	// 调用 std::vector::vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type())
	// 构造函数,完成字符串分割
	return std::vector<std::string> {
		std::sregex_token_iterator(in.begin(), in.end(), re, -1),
			std::sregex_token_iterator()
	};
}
 
float String2Number(string& s)
{

	std::string::size_type sz;
	return std::stof(s, &sz);

	//istringstream iss(s);
	//T number;
	//iss >> number;
	//return number; 
}
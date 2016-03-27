// pbrtCube.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define PBRT_PROBES_NONE
#define PBRT_HAS_OPENEXR

#include <iostream>

//#include "pbrt.h"
#include "pbrt.h"
#include "camera.h"
#include "scene.h"
#include "imageio.h"
#include "intersection.h"
#include "montecarlo.h"
#include "sampler.h"
#include "texture.h"
#include "integrator.h"

#include "api.h"
#include "probes.h"
#include "parser.h"
#include "parallel.h"

#include "paramset.h"

float g_cubeVertex[] = 
{
	-0.1f, -0.1f, -0.1f,  
	-0.1f, -0.1f,  0.1f,   
	-0.1f,  0.1f,  0.1f,    
	0.1f,   0.1f,    -0.1f,    
	-0.1f,    -0.1f,    -0.1f,  
	-0.1f,    0.1f,    -0.1f,   
	0.1f,    -0.1f,    0.1f,   
	-0.1f,    -0.1f,    -0.1f,  
	0.1f,    -0.1f,    -0.1f,   
	0.1f,    0.1f,    -0.1f,   
	0.1f,    -0.1f,    -0.1f,   
	-0.1f,    -0.1f,    -0.1f,  
	-0.1f,    -0.1f,    -0.1f,  
	-0.1f,    0.1f,    0.1f,   
	-0.1f,    0.1f,    -0.1f,   
	0.1f,    -0.1f,    0.1f,   
	-0.1f,    -0.1f,    0.1f,   
	-0.1f,    -0.1f,    -0.1f,  
	-0.1f,    0.1f,    0.1f,   
	-0.1f,    -0.1f,    0.1f,   
	0.1f,    -0.1f,    0.1f,   
	0.1f,    0.1f,    0.1f,  
	0.1f,    -0.1f,    -0.1f,   
	0.1f,    0.1f,    -0.1f,   
	0.1f,    -0.1f,    -0.1f,   
	0.1f,    0.1f,    0.1f,   
	0.1f,    -0.1f,    0.1f,   
	0.1f,    0.1f,    0.1f,   
	0.1f,    0.1f,    -0.1f,   
	-0.1f,    0.1f,    -0.1f,   
	0.1f,    0.1f,    0.1f,   
	-0.1f,    0.1f,    -0.1f,   
	-0.1f,    0.1f,    0.1f,   
	0.1f,    0.1f,    0.1f,   
	-0.1f,    0.1f,    0.1f,  
	0.1f,    -0.1f,    0.1f,  
};

int g_cubeIndex[] = 
{
	0,1, 2,
	3 ,4 ,5,
	6 ,7 ,8,
	9 ,10 ,11,
	12 ,13, 14,
	15 ,16 ,17,
	18 ,19 ,20,
	21, 22, 23,
	24, 25, 26,
	27, 28, 29,
	30, 31, 32,
	33, 34 ,35,
};

int _tmain(int argc, _TCHAR* argv[])
{
	Options options;
	pbrtInit(options);

	ParamSet filmParamSet;
	pbrtFilm("image", filmParamSet);

	pbrtLookAt(0, 0.2, 0.2, -0.02, 0.1, 0,  0, 1, 0);

	ParamSet cameraParamSet;
	float fov = 60;
	cameraParamSet.AddFloat("fov", &fov);
	pbrtCamera("perspective", cameraParamSet);

	pbrtWorldBegin();

	pbrtAttributeBegin();
	pbrtCoordSysTransform("camera");
	//pbrtLightSource();
	ParamSet lightParamSet;
	float lightColor[3];
	lightColor[0] = 0.7;
	lightColor[1] = 0.7;
	lightColor[2] = 0.7;
	lightParamSet.AddRGBSpectrum("I", lightColor, 3);
	pbrtLightSource("point", lightParamSet);
	pbrtAttributeEnd();

	pbrtAttributeBegin();

	pbrtAttributeEnd();
	ParamSet materialParamSet;
	float materialColor[3];
	materialColor[0] = 0.4;
	materialColor[1] = 0.42;
	materialColor[2] = 0.4;
	materialParamSet.AddRGBSpectrum("Kd", materialColor, 3);
	pbrtMaterial("matter", materialParamSet);
	ParamSet sharpParamSet;
	Point points[36];
	for (int i = 0; i < 36; ++i)
	{
		Point point = Point(g_cubeVertex[i * 3], g_cubeVertex[i * 3 + 1], g_cubeVertex[i * 3 + 2]);
		points[i] = point;
	}
	sharpParamSet.AddPoint("P", points, 36);
	sharpParamSet.AddInt("indices", g_cubeIndex, 36);
	pbrtShape("trianglemesh", sharpParamSet);
	pbrtWorldEnd();

	pbrtCleanup();

	char str[8];
	std::cin.getline(str, 5);

	return 0;
}


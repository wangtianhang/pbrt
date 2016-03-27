// pbrtCube.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../core/pbrt.h"
#include "../core/api.h"



int _tmain(int argc, _TCHAR* argv[])
{
	Options options;
	pbrtInit(options);

	ParamSet filmParamSet;
	pbrtFilm("image", paramSet);



	pbrtCleanup();

	char str[8];
	std::cin.getline(str, 5);

	return 0;
}


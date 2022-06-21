//Declaration header
#include"logger.h"
#include<iostream>
using namespace std;




namespace Minimal2DEngine
{


	logger::logger()
		: 
		file(nullptr)
	{

	}


	logger::~logger()
	{
		fprintf(file,"---END--");
		fprintf(file,"\n");
		fclose(file);
	}


	void logger::init(const char* pHeader)
	{
		file = fopen("log.txt","w");
		if (!file)
		{
			std::cout << "Failed to create a log file!";
			std::abort();
		}

		fprintf(file,pHeader);
		fprintf(file,"\n\n\n");
	}


	void logger::log(const char* pFormat,...)
	{
		va_list list;
		va_start(list,pFormat);
		vfprintf(file,pFormat,list);
		fprintf(file, "\n");
		va_end(list);
	}

	
}

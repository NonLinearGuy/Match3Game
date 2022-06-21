//Declaration headers
#include"debugger.h"


//C++ headers
#include<string>


//engine headers
#include "logger.h"




namespace Minimal2DEngine
{


	GLenum check_for_error_(const char *file,int line)
	{
		GLenum errorFlag = GL_NO_ERROR;
	
		if((errorFlag=glGetError())!=GL_NO_ERROR)
		{
			std::string error;

			switch(errorFlag)
			{
		
			case GL_INVALID_ENUM: error = "INVALID ENUM"; break;
			case GL_INVALID_VALUE: error = "INVALID VALUE"; break;
			case GL_INVALID_OPERATION: error = "INVALID OPERATION"; break;
			case GL_STACK_OVERFLOW: error = "STACK OVERFLOW "; break;
			case GL_STACK_UNDERFLOW: error = "STACK UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY: error = "OUT OF MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID FRAMEBUFFER OPERATION"; break;
		
			}

			logger::getInstance()->getInstance()->log(
				"OpenGL Error : \n"
				"File : %s \n"
				"Line : %d \n"
				"Error Flag : %d \n"
				"Description : %s \n" , file,line,errorFlag,error.c_str()
			);

		}

		return errorFlag;
	}


	void APIENTRY debug_output_callback(
		GLenum pSource,
		GLenum pType,
		GLuint pID,
		GLenum pSeverity,
		GLsizei pLength,
		const GLchar* pMessage,
		const void *pUserParam
							
	)
	{



		//Ignorning unnecessary error codes
		if(pID == 131169 ||pID== 131185 ||pID== 131218 ||pID== 131204) return; 


		logger::getInstance()->log("---------------\n");
		logger::getInstance()->log("Debug Message (%d) : %s \n", pID, pMessage);

		switch (pSource)
		{
			case GL_DEBUG_SOURCE_API:             logger::getInstance()->log( "Source: API"); break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   logger::getInstance()->log( "Source: Window System"); break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER: logger::getInstance()->log( "Source: Shader Compiler"); break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:     logger::getInstance()->log( "Source: Third Party"); break;
			case GL_DEBUG_SOURCE_APPLICATION:     logger::getInstance()->log( "Source: Application"); break;
			case GL_DEBUG_SOURCE_OTHER:           logger::getInstance()->log( "Source: Other"); break;
		}
		
		logger::getInstance()->log("\n");

		switch (pType)
		{
			case GL_DEBUG_TYPE_ERROR:               logger::getInstance()->log( "Type: Error"); break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: logger::getInstance()->log( "Type: Deprecated Behaviour"); break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  logger::getInstance()->log( "Type: Undefined Behaviour"); break; 
			case GL_DEBUG_TYPE_PORTABILITY:         logger::getInstance()->log( "Type: Portability"); break;
			case GL_DEBUG_TYPE_PERFORMANCE:         logger::getInstance()->log( "Type: Performance"); break;
			case GL_DEBUG_TYPE_MARKER:              logger::getInstance()->log( "Type: Marker"); break;
			case GL_DEBUG_TYPE_PUSH_GROUP:          logger::getInstance()->log( "Type: Push Group"); break;
			case GL_DEBUG_TYPE_POP_GROUP:           logger::getInstance()->log( "Type: Pop Group"); break;
			case GL_DEBUG_TYPE_OTHER:               logger::getInstance()->log( "Type: Other"); break;
		}

		logger::getInstance()->log("\n");
    
		switch (pSeverity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         logger::getInstance()->log( "Severity: high"); break;
			case GL_DEBUG_SEVERITY_MEDIUM:       logger::getInstance()->log( "Severity: medium"); break;
			case GL_DEBUG_SEVERITY_LOW:          logger::getInstance()->log( "Severity: low"); break;
			case GL_DEBUG_SEVERITY_NOTIFICATION: logger::getInstance()->log( "Severity: notification"); break;
		} 
	
		logger::getInstance()->log("\n\n");

		std::abort();
	}


}


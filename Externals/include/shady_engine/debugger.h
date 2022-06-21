#ifndef INC_SHADY_ENGINE_DEBUGGER_H
#define INC_SHADY_ENGINE_DEBUGGER_H




//Third party headers
#include<GL/glew.h>
#include<GLFW/glfw3.h>




namespace shady_engine
{
	

	#define check_for_error() checkForError_(__FILE__,__LINE__)

	GLenum check_for_error_(const char *file,int line);

	void APIENTRY debug_output_callback(
		GLenum pSource,
		GLenum pType,
		GLuint pID,
		GLenum pSeverity,
		GLsizei pLength,
		const GLchar* pMessage,
		const void *pUserParam
						
		);


}


#endif
#ifndef INC_SHADY_ENGINE_SHADER_H
#define INC_SHADY_ENGINE_SHADER_H



#include <glad/glad.h>
//C++ Headers
#include<string>


//Third Party Libraries Headers

#include<glm/glm.hpp>
#include<glm/gtc/type_ptr.hpp>


//shady_engine headers
#include"logger.h"




namespace Minimal2DEngine
{


	class Shader
	{


	public:

		
		Shader();

		
		Shader( const std::string& name,
			const char* pVertexShader, 
			const char* pFragShader
		);


		void CreateShader(
			const char* pVertexShader,
			const char* pFragShader
		);

		~Shader();


		inline GLuint GetID() { 
			return mProgramID; 
		}


	
		void Use();


		void Set1i(
			const std::string& pName,
			GLint pValue
		);


		void Set1f(
			const std::string& pName, 
			GLfloat pValue
		);


		void Set2fv(
			const std::string& pName, 
			const glm::vec2& pVector
		);


		void Set3fv(
			const std::string& pName, 
			const glm::vec3& pVector
		);


		void Set4fv(
			const std::string& pName, 
			const glm::vec4& pVector
		);


		void SetMat4(
			const std::string& pName, 
			const glm::mat4& pMat
		);


	private:

		GLuint mProgramID;
        std::string mName;

		void CheckForErrors(
			std::string type,
			GLuint pID
		);


	}; //End of namespace


}

#endif

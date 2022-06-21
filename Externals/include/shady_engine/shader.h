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




namespace shady_engine
{


	class shader
	{


	public:

		
		shader();

		
		shader(
			const char* pVertexShader, 
			const char* pFragShader
		);


		void create_shader(
			const char* pVertexShader,
			const char* pFragShader
		);

		~shader();


		inline GLuint get_id() { 
			return mProgramID; 
		}


	
		void use();


		void set1i(
			const std::string& pName,
			GLint pValue
		);


		void set1f(
			const std::string& pName, 
			GLfloat pValue
		);


		void set2fv(
			const std::string& pName, 
			const glm::vec2& pVector
		);


		void set3fv(
			const std::string& pName, 
			const glm::vec3& pVector
		);


		void set4fv(
			const std::string& pName, 
			const glm::vec4& pVector
		);


		void setMat4(
			const std::string& pName, 
			const glm::mat4& pMat
		);


	private:

		GLuint mProgramID;

		void check_for_errors_bro(
			std::string &type,
			GLuint pID
		);


	}; //End of namespace


}

#endif

//Declaration headers
#include"Shader.h"

#include<string>


//C++ headers
#include<iostream>




namespace Minimal2DEngine
{


	Shader::Shader() {}


	Shader::Shader(const std::string& pName,
		const char* pVertexShader,
		const char* pFragShader
	)

	{
        this->mName = pName;
		//Creating and Compiling shaders

		//Vertex shader

		GLuint vsObj = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vsObj, 1, &pVertexShader, 0);
		glCompileShader(vsObj);

		//Fragment shader
		GLuint fsObj = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fsObj, 1, &pFragShader, 0);
		glCompileShader(fsObj);



		//Creating,Attaching and linking shaders with program

		mProgramID = glCreateProgram();
		glAttachShader(mProgramID, vsObj);
		glAttachShader(mProgramID, fsObj);
		glLinkProgram(mProgramID);

		try
		{
			CheckForErrors(std::string("vertex shader"), vsObj);
			CheckForErrors(std::string("fragment shader"), fsObj);
			CheckForErrors(std::string("program"), mProgramID);
		}
		catch (std::runtime_error& e)
		{

			glDeleteShader(vsObj);
			glDeleteShader(fsObj);
			glDeleteProgram(mProgramID);
			
			
			logger::getInstance()->log(pVertexShader);
			throw e;
		}

		//deleting both shaders objects because we no longer need them

		glDeleteShader(vsObj);
		glDeleteShader(fsObj);
	}


	Shader::~Shader() {}


	void Shader::CheckForErrors(
		std::string pType, 
		GLuint pID
	)
	{

		if (pType == "program")
		{

			GLint success;
			glGetProgramiv(pID, GL_LINK_STATUS, &success);
			
			if (!success)
			{
				
				GLchar errInfo[512];
				glGetProgramInfoLog(pID, 512, 0, errInfo);
				//writing error to log file

				std::cout<<"Error :: Failed to link" + mName + " program :: " + std::string(errInfo);

			}

		}
		else
		{
			
			GLint success;
			glGetShaderiv(pID, GL_COMPILE_STATUS, &success);
			
			if (!success)
			{
			
				GLchar errInfo[512];
				glGetShaderInfoLog(pID, 512, 0, errInfo);

				std::cout<<"Error :: Failed to compile " + mName + " program :: " + std::string(errInfo);
		
			}
		
		}
	}


	void Shader::CreateShader(
		const char* pVertexShader,
		const char* pFragShader
	)

	{

		//Creating and Compiling shaders

		//Vertex shader

		GLuint vsObj = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vsObj, 1, &pVertexShader, 0);
		glCompileShader(vsObj);

		//Fragment shader
		GLuint fsObj = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fsObj, 1, &pFragShader, 0);
		glCompileShader(fsObj);



		//Creating,Attaching and linking shaders with program

		mProgramID = glCreateProgram();
		glAttachShader(mProgramID, vsObj);
		glAttachShader(mProgramID, fsObj);
		glLinkProgram(mProgramID);
	
		try
		{
			CheckForErrors(std::string("vertex shader"), vsObj);
			CheckForErrors(std::string("fragment shader"), fsObj);
			CheckForErrors(std::string("program"), mProgramID);
		}
		catch (std::runtime_error& e)
		{
			glDeleteShader(vsObj);
			glDeleteShader(fsObj);
			glDeleteProgram(mProgramID);


			throw e;
		}

		//deleting both shaders objects because we no longer need them

		glDeleteShader(vsObj);
		glDeleteShader(fsObj);
	}


	void Shader::Use()
	{
		glUseProgram(mProgramID);
	}


	void Shader::Set1i(
		const std::string& pName, 
		GLint pValue
	)
	{
		glUniform1i(glGetUniformLocation(mProgramID, pName.c_str()), pValue);
	}


	void Shader::Set1f(
		const std::string& pName, 
		GLfloat pValue
	)
	{
		glUniform1f(glGetUniformLocation(mProgramID, pName.c_str()), pValue);
	}


	void Shader::Set2fv(
		const std::string& pName, 
		const glm::vec2& pVector
	)
	{
		glUniform2f(glGetUniformLocation(mProgramID, pName.c_str()), pVector.x, pVector.y);
	}


	void Shader::Set3fv(
		const std::string& pName, 
		const glm::vec3& pVector
	)
	{
		glUniform3f(glGetUniformLocation(mProgramID, pName.c_str()), pVector.x, pVector.y, pVector.z);
	}


	void Shader::Set4fv(
		const std::string& pName, 
		const glm::vec4& pVector
	)
	{
		glUniform4f(glGetUniformLocation(mProgramID, pName.c_str()), 
			pVector.x, pVector.y, pVector.z, pVector.w);
	}


	void Shader::SetMat4(
		const std::string& pName, 
		const glm::mat4& pMat
	)
	{
		glUniformMatrix4fv(glGetUniformLocation(mProgramID, pName.c_str()),
			1, GL_FALSE, glm::value_ptr(pMat));
	}


}

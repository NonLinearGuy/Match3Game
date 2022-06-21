#ifndef INC_SHADY_ENGINE_TEXT_RENDERER_H
#define INC_SHADY_ENGINE_TEXT_RENDERER_H




//C++ headers
#include<iostream>
#include<map>
#include<string>
#include<cstdarg>
#include<memory>
#include<vector>


//Third party headers
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include"shader.h"
#include"texture2D.h"







namespace shady_engine
{


	class text_renderer
	{

	private:


		//rendering data

		struct character
		{
			glm::ivec2 position;
			glm::ivec2 size;
			glm::ivec2 offsets;
			int advanceX;

		};
		std::map<char, character> mCharacters;
		std::shared_ptr<texture2D> mTextureAtlas;
		std::shared_ptr<shader> mShader;
		GLuint mVAO;
		GLuint mVBO;


		//data needed for instancing 
		std::vector<glm::vec2> mOffsets;
		std::vector<glm::vec2> mScalers;
		std::vector<glm::vec4> mTexCoords;

		GLuint mVBOOffsets;
		GLuint mVBOTexCoords;
		GLuint mVBOScalers;


	public:
		
		//Constructors
		text_renderer();
		
		
		text_renderer(
			const std::shared_ptr<texture2D> pTextureAtlas,
			const std::string& pPath
		);


		//Destructor
		~text_renderer();
		
		
		
		/*
			initializes essential data for rendering text
		*/
		void init(
			const std::shared_ptr<texture2D> pTextureAtlas,
			const std::string& pPath
		);
		
		
		/*
			Renders text with a color
		*/
		void text(
			const glm::mat4& pProjection,
			const glm::mat4& pView,
			const glm::vec2& pPosition, 
			float pSize, 
			const glm::vec3& pColor,
			const char* pFormat, 
			...
		);


		/*
			Renders text with color sampled from a texture
		*/
		void textured_text(
			const glm::mat4& pProjection,
			const glm::mat4& pView,
			const glm::vec2& pPosition, 
			float pSize, 
			std::shared_ptr<texture2D> pTexture, 
			const char* pFormat, 
			...
		);
	
	
	};


}
#endif
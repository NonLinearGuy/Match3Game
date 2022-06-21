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

#include"Shader.h"
#include"Texture2D.h"








namespace Minimal2DEngine
{


	class TextRenderer
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
		std::shared_ptr<Texture2D> mTextureAtlas;
		std::shared_ptr<Shader> mShader;
		GLuint mVAO;
		GLuint mVBO;


		//data needed for instancing 
		std::vector<glm::vec2> mOffsets;
		std::vector<glm::vec2> mScalers;
		std::vector<glm::vec4> mTexCoords;

		GLuint mVBOOffsets;
		GLuint mVBOTexCoords;
		GLuint mVBOScalers;
        
        glm::mat4 mProjection;
        glm::mat4 mView;


	public:
		
		//Constructors
		TextRenderer();
		
		
		TextRenderer(const glm::mat4 pProjection,const glm::mat4 pView,
			const std::shared_ptr<Texture2D> pTextureAtlas,
			const std::string& pPath
		);


		//Destructor
		~TextRenderer();
		
		
		
		/*
			initializes essential data for rendering text
		*/
		void Init(
			const std::shared_ptr<Texture2D> pTextureAtlas,
			const std::string& pPath
		);
		
		
		/*
			Renders text with a color
		*/
		void Text(
			const glm::vec2& pPosition, 
			float pSize, 
			const glm::vec3& pColor,
			const char* pFormat, 
			...
		);


		/*
			Renders text with color sampled from a texture
		*/
		void TexturedText(
			const glm::vec2& pPosition,
			float pSize, 
			std::shared_ptr<Texture2D> pTexture,
			const char* pFormat, 
			...
		);
	
	
	};


}
#endif

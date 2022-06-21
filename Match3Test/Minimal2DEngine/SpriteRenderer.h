#ifndef INC_SPRITE_RENDERER_H
#define INC_SPRITE_RENDERER_H




//C++ headers
#include<memory>

//Third party headers
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>


//Engine headers

#include "IRenderer2D.hpp"

#include <glad/glad.h>
#include"smath/Math.h"
#include<vector>


namespace Minimal2DEngine
{

    class Shader;
    class Texture2D;

	class SpriteRenderer : public IRenderer2D
	{
	private:
        std::shared_ptr<Shader> mCircleShader;
        GLuint mVAO;
		GLuint mVBO;
	public:
		SpriteRenderer(const glm::mat4 pProjection,const glm::mat4 pView);
		~SpriteRenderer();

        void DrawQuad(const glm::vec2& pPos,const glm::vec2& pSize,const glm::vec4& pColor,float pRotationInRadians
		);
		
		void DrawCircle(const glm::vec2& pPosition,const glm::vec2& pSize,const glm::vec4& pColor);
		void DrawTexturedCircle(const glm::vec2& pPosition,const glm::vec2& pSize,std::shared_ptr<Minimal2DEngine::Texture2D> pTexture);
		void DrawImage(const std::shared_ptr<Texture2D> pTexture,const glm::vec2& pPos,const glm::vec2& pSize,float pRotationInRadians);
		void DrawImageRegion(const std::shared_ptr<Texture2D> pTexture,const glm::vec2& pSrcPos,const glm::vec2& pSrcDim, const glm::vec2& pPos,const glm::vec2& pSize,const glm::vec2& slicedSize);
	}; // End of class sprite_renderer


}// End of namespace


#endif

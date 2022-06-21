#ifndef INC_SPRITE_RENDERER_H
#define INC_SPRITE_RENDERER_H




//C++ headers
#include<memory>

//Third party headers
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>


//shady_engine headers
#include"shader.h"
#include"texture2D.h"
#include"smath/math.h"
#include<vector>




namespace shady_engine
{


	class sprite_renderer
	{


	private:

		std::shared_ptr<shader> mShader;
		std::shared_ptr<shader> mCircleShader;
		GLuint mVAO;
		GLuint mVBO;



		
	public:


		sprite_renderer();

	
		~sprite_renderer();

		
		void init();

		


		void draw_quad(
			const glm::mat4& pProjection,
			const glm::mat4& pView,
			const glm::vec2& pPos, 
			const glm::vec2& pSize, 
			const glm::vec4& pColor,
			float pRotationInRadians
		);
		
		void draw_circle(
			const glm::mat4& pProjection,
			const glm::mat4& pView,
			const glm::vec2& pPosition,
			const glm::vec2& pSize,
			const glm::vec4& pColor
		);

		void draw_textured_circle(
			const glm::mat4& pProjection,
			const glm::mat4& pView,
			const glm::vec2& pPosition,
			const glm::vec2& pSize,
			std::shared_ptr<shady_engine::texture2D> pTexture
		);
		
		void draw_image(
			const glm::mat4& pProjection,
			const glm::mat4& pView,
			const std::shared_ptr<texture2D> pTexture, 
			const glm::vec2& pPos,
			const glm::vec2& pSize,
			float pRotationInRadians
		);
		

		void draw_image_region(
			const glm::mat4& pProjection,
			const glm::mat4& pView,
			const std::shared_ptr<texture2D> pTexture, 
			const glm::vec2& pSrcPos, 
			const glm::vec2& pSrcDim, 
			const glm::vec2& pPos, 
			const glm::vec2& pSize
		);


		


	}; // End of class sprite_renderer


}// End of namespace shady_engine


#endif

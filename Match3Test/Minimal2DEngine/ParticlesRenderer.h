#ifndef INC_PARTICLE_RENDERER_H
#define INC_PARTICLE_RENDERER_H


//C++ Headers
#include<memory>
#include<vector>

//Third Party Headers
#include<glad/glad.h>
#include<glm/glm.hpp>

#include"Shader.h"
#include"Texture2D.h"

namespace Minimal2DEngine
{


	class ParticlesRenderer
	{

		
		private:

			std::shared_ptr<Shader> mShader;

			GLuint VAO;
			GLuint VBO;

			GLuint VBOcolors;
			GLuint VBOoffsets;
			GLuint VBOscalers;

	

		public:

			ParticlesRenderer();

			void init();

			void render(
				const glm::mat4& pProjection,
				const glm::mat4& pView,
				int num,
				const std::vector<glm::vec4>& colors,
				const std::vector<glm::vec2>& translations,
				const std::vector<glm::vec2>& scalers
			);


			~ParticlesRenderer();

	};	//End of class

} //End of Namespace
#endif


#ifndef INC_PARTICLE_RENDERER_H
#define INC_PARTICLE_RENDERER_H


//C++ Headers
#include<memory>
#include<vector>

//Third Party Headers
#include<glad/glad.h>
#include<glm/glm.hpp>

#include"shader.h"
#include"texture2D.h"

namespace shady_engine
{


	class particles_renderer
	{

		
		private:

			std::shared_ptr<shader> mShader;

			GLuint VAO;
			GLuint VBO;

			GLuint VBOcolors;
			GLuint VBOoffsets;
			GLuint VBOscalers;

	

		public:

			particles_renderer();

			void init();

			void render(
				const glm::mat4& pProjection,
				const glm::mat4& pView,
				int num,
				const std::vector<glm::vec4>& colors,
				const std::vector<glm::vec2>& translations,
				const std::vector<glm::vec2>& scalers
			);


			~particles_renderer();

	};	//End of class

} //End of Namespace
#endif


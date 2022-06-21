#ifndef INC_SHADY_ENGINE_RESOURCES_H
#define INC_SHADY_ENGINE_RESOURCES_H




//C++ headers
#include<map>
#include<memory>

//Third party libraries
#include<glad/glad.h>
#include<SOIL.h>

//shady_engine headers
#include"shader.h"
#include"texture2D.h"




namespace shady_engine
{
	

	class resources
	{

	public:
	
		
		static std::shared_ptr<resources> getInstance()
		{
			static std::shared_ptr<resources> instance(new resources);
			return instance;
		}


		std::shared_ptr<shader> load_shader(
			const std::string& pName,
			const std::string& pVSPath,
			const std::string& pFSPath
		);
		

		inline std::shared_ptr<shader> get_shader(const std::string& pName) 
		 { 
			 return shaders[pName]; 
		 }


		std::shared_ptr<shader> use_shader(const std::string& pName);
		
		
		 std::shared_ptr<texture2D> load_texture(
			 const std::string& pName, 
			 const std::string& pPath, 
			 GLenum pFormat
		 );

		
		 std::shared_ptr<texture2D> get_texture(const std::string& pName)
		 {
			 return textures[pName];
		 }
		

	private:


		std::map<std::string, std::shared_ptr<shader>> shaders;
		std::map<std::string, std::shared_ptr<texture2D>> textures;


		resources();

	};

}



#endif

#ifndef INC_SHADY_ENGINE_RESOURCES_H
#define INC_SHADY_ENGINE_RESOURCES_H




//C++ headers
#include<map>
#include<memory>

//Third party libraries
#include<glad/glad.h>
#include<SOIL.h>

//shady_engine headers






namespace Minimal2DEngine
{
	
    class Shader;
    class Texture2D;
    
	class AssetManager
	{

	public:
	
		
		static std::shared_ptr<AssetManager> GetInstance()
		{
			static std::shared_ptr<AssetManager> instance(new AssetManager);
			return instance;
		}


		std::shared_ptr<Shader> LoadShader(
			const std::string& pName,
			const std::string& pVSPath,
			const std::string& pFSPath
		);
		

		inline std::shared_ptr<Shader> GetShader(const std::string& pName) 
		 { 
			 return shaders[pName]; 
		 }


		std::shared_ptr<Shader> UseShader(const std::string& pName);
		
		
		 std::shared_ptr<Texture2D> load_texture(
			 const std::string& pName, 
			 const std::string& pPath, 
			 GLenum pFormat
		 );

		
		 std::shared_ptr<Texture2D> GetTexture(const std::string& pName)
		 {
			 return textures[pName];
		 }
		

	private:


		std::map<std::string, std::shared_ptr<Shader>> shaders;
		std::map<std::string, std::shared_ptr<Texture2D>> textures;


		AssetManager();

	};

}



#endif

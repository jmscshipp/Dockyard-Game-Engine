#ifndef _ShaderManager
#define _ShaderManager

#include "GraphicsCore.h"
#include <map>

class ShaderManager
{
private:
	static ShaderManager* instance; // set up as singleton

	// big four
	ShaderManager();
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator = (const ShaderManager&) = delete;
	~ShaderManager();

	static ShaderManager& Instance()
	{
		if (!instance)
			instance = new ShaderManager();
		return *instance;
	};

	//void PrivLoadShader(std::string shaderName, std::string shaderFileLocation);
	void PrivLoadShader(std::string shaderName, Shader* shader);
	Shader* PrivGetShader(std::string shaderName);
	void NonstaticDelete();
	static void Delete() { Instance().NonstaticDelete(); }; // so we don't delete before singleton is made

	// to allow Dockyard to Delete() singleton
	friend class ShaderManagerAttorney;

	const std::string defaultPath = "../Assets/Shaders/"; // need to include '/' for file path;

	Shader* defaultSpriteShader;
	const std::string spriteShaderDefaultKey = "defaultSpriteShader";

	std::map<std::string, Shader*> loadedShaders;

public:
	/// \brief Loads a shader from from specified file location
	/// \ingroup ASSETMANAGEMENT 
	/// 	
	/// Adds the new shader to the engine's collection of available to use shaders.	 
	/// If a shader has already been loaded with the given name, this function will throw an error
	///  		 
	/// \param shaderName	The name given to the shader when it's loaded. This is what will be passed to ShaderManager::GetShader to retrieve the shader later
	/// \param shaderFileLocation	The name of the shader file located in Assets/Shaders/ <b>excluding</b> the file extension
	/// 
	///  \par Example:
	/// Loading a shader from file
	///		\code
	///		void Dockyard::LoadResources()
	///		{
	///			// loading a new shader and calling it "TextureLight"
	///		ShaderManager::LoadShader("TextureLight", "textureLightRender");
	///		}
	///		\endcode
	/// \note In most cases, shaders should be loaded in Dockyard::LoadResources to be accessed elsewhere with ShaderManager::GetShader
	static void LoadShader(std::string shaderName, Shader* shader) { Instance().PrivLoadShader(shaderName, shader); }
	/// \brief Retrieve previously loaded shader by name
	/// \ingroup ASSETMANAGEMENT 
	/// 		 
	/// If a shader with the specified name hasn't been loaded, this function will throw an error
	/// 
	/// \param shaderName	The name of the shader to be retrieved, which was given when the shader was loaded
	/// 
	///  \par Example:
	/// Getting shaders to use with GraphicsObjects
	///		\code
	///		BackgroundProps::BackgroundProps()
	///		{
	///			// creating textured GraphicsObject with lighting
	///			Vect LightColor(1.50f, 1.50f, 1.50f, 1.0f);
	///			Vect LightPos(1.0f, 1.0f, 1.0f, 1.0f);
	///			gObjHouse = new GraphicsObject_TextureLight(ModelManager::GetModel("House"), ShaderManager::GetShader("TextureLight"), TextureManager::GetTexture("House"), LightColor, LightPos);
	///			
	///			// creating textured GraphicsObject without lighting (flat)
	///			gObjSun = new GraphicsObject_TextureFlat(ModelManager::GetModel("Sun"), ShaderManager::GetShader("Texture"), TextureManager::GetTexture("BurntOrange"));
	///		}
	///		\endcode
	/// \note shaders most be loaded with ShaderManager::LoadShader before being retrieved
	static Shader* GetShader(std::string shaderName) { return Instance().PrivGetShader(shaderName); }
};

#endif
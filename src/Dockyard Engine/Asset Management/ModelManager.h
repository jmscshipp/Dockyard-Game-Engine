#ifndef _ModelManager
#define _ModelManager

#include "AzulCore.h"
#include <map>

class ModelManager
{
private:
	static ModelManager* instance; // set up as singleton

	// big four
	ModelManager();
	ModelManager(const ModelManager&) = delete;
	ModelManager& operator = (const ModelManager&) = delete;
	~ModelManager();

	static ModelManager& Instance()
	{
		if (!instance)
			instance = new ModelManager();
		return *instance;
	};

	void PrivLoadModel(std::string modelName, std::string modelFileLocation);
	void PrivLoadModel(std::string modelName, Model::PreMadeModels premadeModel);
	Model* PrivGetModel(std::string modelName);
	void NonstaticDelete();
	static void Delete() { Instance().NonstaticDelete(); }; // so we don't delete before singleton is made

	// to allow Dockyard to Delete() singleton
	friend class ModelManagerAttorney;

	const std::string defaultPath = "Models/"; // need to include '/' for file path
	Model* defaultSpriteModel;
	const std::string spriteDefaultKey = "defaultSpriteModel";
	std::map<std::string, Model*> loadedModels;

public:
	/// \brief Loads a model from from specified file location
	/// \ingroup ASSETMANAGEMENT 
	/// 	
	/// Adds the new model to the engine's collection of available to use models.	 
	/// If a model has already been loaded with the given name, this function will throw an error
	///  		 
	/// \param modelName	The name given to the model when it's loaded. This is what will be passed to ModelManager::GetModel to retrieve the model later
	/// \param modelFileLocation	The name of the model file located in Assets/Models/ <b>including</b> the file extension
	/// 
	///  \par Example:
	/// Loading a model from file
	///		\code
	///		void Dockyard::LoadResources()
	///		{
	///			// loading a new model and calling it "House"
	///			ModelManager::LoadModel("House", "HouseModel.azul");
	///		}
	///		\endcode
	/// \note The model file being loaded must be in Azul (.azul) format to be loaded correctly.
	/// In most cases, models should be loaded in Dockyard::LoadResources to be accessed elsewhere with ModelManager::GetModel
	static void LoadModel(std::string modelName, std::string modelFileLocation) { Instance().PrivLoadModel(modelName, modelFileLocation); }
	/// \brief Loads a premade model made available by the engine
	/// \ingroup ASSETMANAGEMENT 
	/// 	
	/// Adds the new model to the engine's collection of available to use models.	 
	/// If a model has already been loaded with the given name, this function will throw an error
	/// 	 
	/// \param modelName	The name given to the model when it's loaded. This is what will be passed to ModelManager::GetModel to retrieve the model later
	/// \param premadeModel	Which premade model is being used- accessed with Model::PreMadeModels (must #include "AzulCore.h")
	/// 
	///  \par Example:
	/// Loading a premade model
	///		\code
	///		void Dockyard::LoadResources()
	///		{
	///			// loading a premade model and calling it "Sun"
	///			ModelManager::LoadModel("Sun", Model::PreMadeModels::UnitSphere);
	///		}
	///		\endcode
	/// \note In most cases, models should be loaded in Dockyard::LoadResources to be accessed elsewhere with ModelManager::GetModel
	static void LoadModel(std::string modelName, Model::PreMadeModels premadeModel) { Instance().PrivLoadModel(modelName, premadeModel); }
	/// \brief Retrieve previously loaded model by name
	/// \ingroup ASSETMANAGEMENT 
	/// 		 
	/// If a model with the specified name hasn't been loaded, this function will throw an error
	/// 
	/// \param modelName	The name of the model to be retrieved, which was given when the model was loaded
	/// 
	///  \par Example:
	/// Getting models to use with GraphicsObjects
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
	/// \note Models most be loaded with ModelManager::LoadModel before being retrieved
	static Model* GetModel(std::string modelName) { return Instance().PrivGetModel(modelName); }
};

#endif
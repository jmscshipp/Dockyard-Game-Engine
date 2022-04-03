#include "ImageManager.h"

ImageManager* ImageManager::instance = nullptr;

ImageManager::ImageManager()
{

}

ImageManager::~ImageManager()
{
	for (std::pair<std::string, Image*> element : loadedImages)
		delete(element.second);
}

void ImageManager::PrivLoad(std::string imageName, Texture* tex)
{
	if (loadedImages.count(imageName) > 0) // if a texture with this name has already been loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is already a loaded image named " + imageName + " !!!\n");
	}
	else
	{
		Image* newLoadedImage = new Image(tex, new Rect(0.0f, 0.0f, (float)tex->getWidth(), (float)tex->getHeight()));
		loadedImages.emplace(imageName, newLoadedImage);
	}
}

void ImageManager::PrivLoad(std::string imageName, Texture* tex, Rect* r)
{
	if (loadedImages.count(imageName) > 0) // if a texture with this name has already been loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is already a loaded image named " + imageName + " !!!\n");
	}
	else
	{
		Image* newLoadedImage = new Image(tex, r);
		loadedImages.emplace(imageName, newLoadedImage);
	}
}

Image* ImageManager::PrivGetImage(std::string imageName)
{
	std::map<std::string, Image*>::const_iterator findResult = loadedImages.find(imageName);
	if (findResult == loadedImages.end()) // if we have no texture of this name loaded
	{
		// THROW ERROR
		throw("!!! ERROR: There is no loaded image named " + imageName + " !!!\n");
		return nullptr;
	}
	else
	{
		return findResult->second;
	}
}

void ImageManager::NonstaticDelete()
{
	delete instance;
	instance = nullptr;
}
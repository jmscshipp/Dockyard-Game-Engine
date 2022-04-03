#include "DrawableManager.h"
#include "DrawableAttorney.h"

void DrawableManager::ProcessElements()
{
	// first pass for 3d
	for (StorageList::iterator it = storageList.begin(); it != storageList.end(); it++)
		DrawableAttorney::GameLoop::Draw(*it);
	// second pass for sprites
	for (StorageList::iterator it = storageList.begin(); it != storageList.end(); it++)
		DrawableAttorney::GameLoop::Draw2D(*it);
}

void DrawableManager::Register(Drawable* drbl, StorageListRef &ref)
{
	ref = storageList.insert(storageList.end(), drbl);
}

void DrawableManager::Deregister(StorageListRef ref)
{
	storageList.erase(ref);
}
#include "UpdatableManager.h"
#include "UpdatableAttorney.h"

void UpdatableManager::ProcessElements()
{
	for (StorageList::iterator it = storageList.begin(); it != storageList.end(); it++)
		UpdatableAttorney::GameLoop::Update(*it);
}

void UpdatableManager::Register(Updatable* up, StorageListRef &ref)
{
	ref = storageList.insert(storageList.end(), up);
}

void UpdatableManager::Deregister(StorageListRef ref)
{
	storageList.erase(ref);
}
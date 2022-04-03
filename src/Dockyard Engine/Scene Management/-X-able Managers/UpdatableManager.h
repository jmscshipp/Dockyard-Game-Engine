#ifndef _UpdatableManager
#define _UpdatableManager

#include <list>

// forward declaration
class Updatable;

class UpdatableManager
{
public:
	// big four
	UpdatableManager() = default;
	UpdatableManager(const UpdatableManager&) = delete;
	UpdatableManager& operator = (const UpdatableManager&) = delete;
	~UpdatableManager() = default;

	using StorageListRef = std::list<Updatable*>::iterator;

	void ProcessElements();
	void Register(Updatable* up, StorageListRef &ref);
	void Deregister(StorageListRef ref);

private:
	using StorageList = std::list<Updatable*>;
	StorageList storageList;
};

#endif
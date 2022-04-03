#ifndef _DrawableManager
#define _DrawableManager

#include <list>

// forward declaration
class Drawable;

class DrawableManager
{
public:
	// big four
	DrawableManager() = default;
	DrawableManager(const DrawableManager&) = delete;
	DrawableManager& operator = (const DrawableManager&) = delete;
	~DrawableManager() = default;

	using StorageListRef = std::list<Drawable*>::iterator;

	void ProcessElements();
	void Register(Drawable* drbl, StorageListRef &ref);
	void Deregister(StorageListRef ref);

private:
	using StorageList = std::list<Drawable*>;
	StorageList storageList;
};

#endif
#ifndef _SceneAttorney
#define _SceneAttorney

// forward declaration
#include "SceneManager.h"
#include "Scene.h"
#include "SceneRegistrationBroker.h"
#include "UpdatableManager.h"
#include "DrawableManager.h"
#include "ALarmableManager.h"
#include "InputableAttorney.h"
#include "KeyboardEventManager.h"
#include "CollisionManager.h"
#include "CollidableGroup.h"

class SceneAttorney
{
public:
	// big four
	SceneAttorney() = default;
	SceneAttorney(const SceneAttorney&) = delete;
	SceneAttorney& operator = (const SceneAttorney&) = delete;
	~SceneAttorney() = default;

	class General
	{
		friend class SceneManager;

		static void Update(Scene* scn) { scn->Update(); };
		static void Draw(Scene* scn) { scn->Draw(); };
	};

	class CommandSubmission
	{
		friend class Updatable;
		friend class Drawable;
		friend class Alarmable;
		friend class Inputable;
		friend class Collidable;
		friend class GameObject;

		static void SubmitCommand(SceneRegistrationCommand* command) { SceneManager::GetCurrentScene()->registrationBrkr->AddCommand(command); };
	};

	class Registration
	{
		friend class Updatable;
		friend class Drawable;
		friend class Alarmable;
		friend class Inputable;
		friend class Collidable;
		friend class GameObject;

	private:
		static void Register(Updatable* up, UpdatableManager::StorageListRef& ref) { SceneManager::GetCurrentScene()->updatableMgr->Register(up, ref); };
		static void Register(Drawable* drbl, DrawableManager::StorageListRef& ref) { SceneManager::GetCurrentScene()->drawableMgr->Register(drbl, ref); };
		static void Register(float t, AlarmableManager::ALARM_ID id, Alarmable* alrm, AlarmableManager::TimelineRef& ref) { SceneManager::GetCurrentScene()->alarmableMgr->Register(t, id, alrm, ref); };
		static void Register(Inputable* inp, AZUL_KEY k, InputableAttorney::EVENT_TYPE e, InputableAttorney::InputColRef& ref) { SceneManager::GetCurrentScene()->keyboardEventMgr->Register(inp, k, e, ref); };
		static void Register(Collidable* cldr, CollisionManager::DockyardTypeID id, CollidableGroup::CollidableCollectionRef& ref) { SceneManager::GetCurrentScene()->collisionMgr->GetColGroup(id)->Register(cldr, ref); };
		static void Deregister(UpdatableManager::StorageListRef ref) { SceneManager::GetCurrentScene()->updatableMgr->Deregister(ref); };
		static void Deregister(DrawableManager::StorageListRef ref) { SceneManager::GetCurrentScene()->drawableMgr->Deregister(ref); };
		static void Deregister(AlarmableManager::TimelineRef ref) { SceneManager::GetCurrentScene()->alarmableMgr->Deregister(ref); };
		static void Deregister(AZUL_KEY k, InputableAttorney::EVENT_TYPE e, InputableAttorney::InputColRef ref) { SceneManager::GetCurrentScene()->keyboardEventMgr->Deregister(k, e, ref); };
		static void Deregister(CollisionManager::DockyardTypeID id, CollidableGroup::CollidableCollectionRef& ref) { SceneManager::GetCurrentScene()->collisionMgr->GetColGroup(id)->Deregister(ref); };
		// called by collidable when setting its group
		static CollisionManager* GetCollisionMgr() { return SceneManager::GetCurrentScene()->collisionMgr; };
	};
};

#endif
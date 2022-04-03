#ifndef _SceneRegistrationState
#define _SceneRegistrationState

enum class SceneRegistrationState
{
	CURRENTLY_DEREGISTERED,
	PENDING_REGISTRATION,
	CURRENTLY_REGISTERED,
	PENDING_DEREGISTRATION
};

#endif
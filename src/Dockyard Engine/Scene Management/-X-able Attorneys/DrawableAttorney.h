#ifndef _DrawableAttorney
#define _DrawableAttorney

// forward declaration
#include "Drawable.h"

class DrawableAttorney
{
public:
	// big four
	DrawableAttorney() = default;
	DrawableAttorney(const DrawableAttorney&) = delete;
	DrawableAttorney& operator = (const DrawableAttorney&) = delete;
	~DrawableAttorney() = default;

	class GameLoop
	{
		friend class DrawableManager;
	private:
		static void Draw(Drawable* drbl) { drbl->Draw(); }
		static void Draw2D(Drawable* drbl) { drbl->Draw2D(); }
	};

	class Registration
	{
		friend class DrawRegistrationCommand;
		friend class DrawDeregistrationCommand;
	private:
		static void SceneRegistration(Drawable* drbl) { drbl->SceneRegistration(); }
		static void SceneDeregistration(Drawable* drbl) { drbl->SceneDeregistration(); }
	};
};

#endif
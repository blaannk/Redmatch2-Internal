#pragma once
#include "Module.h"

class WeaponMod : public SModule {
private:
	float testFloat = 1.f;
	bool rapidfire = false;
	bool noreload = false;
	bool infiniteammo = false;
public:
	WeaponMod();

	virtual void onEnable();
	virtual void onDisable();
	virtual void onFrame();
};
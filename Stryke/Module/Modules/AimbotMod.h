#pragma once
#include "Module.h"

class AimbotMod : public SModule {
private:
	float smooth = 1.f;
public:
	AimbotMod();

	virtual void onEnable();
	virtual void onDisable();
	virtual void onFrame();
};
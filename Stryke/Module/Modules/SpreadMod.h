#pragma once
#include "Module.h"

class SpreadMod : public SModule {
private:
	float testFloat = 1.f;
public:
	SpreadMod();

	virtual void onEnable();
	virtual void onDisable();
	virtual void onFrame();
};
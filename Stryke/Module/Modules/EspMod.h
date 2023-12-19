#pragma once
#include "Module.h"

#include "../../Draw/imgui.h"
#include "../../Draw/imgui_impl_dx11.h"
#include "../../Draw/imgui_impl_win32.h"

class EspMod : public SModule {
private:
	float line_len = 2.f;
public:
	EspMod();

	virtual void onEnable();
	virtual void onDisable();
	virtual void onFrame();
};
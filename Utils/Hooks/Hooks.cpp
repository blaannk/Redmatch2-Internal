#pragma once
#include "Hooks.h"

template <typename T>
bool elementInList(const std::list<T>& myList, const T& elementToFind) {
	auto it = std::find(myList.begin(), myList.end(), elementToFind);
	return (it != myList.end());
}

void(__stdcall* original_update)(CPlayer* __this);
void __stdcall PlayerUpdateHook(CPlayer* __this) {
	if (__this != nullptr) {
		if (!hook.isPlayerInList(__this)) {
			hook.addPlayer(__this);
		}
		if (!hook.isaPlayerInList(__this)) {
			hook.addaPlayer(__this);
		}
		hook.player = __this;
	}
	return original_update(__this);
}

void Hooks::AllHooks(bool enable) {
	if (enable) {
		//For Each Hook Template Defined Above, Create and Hook below.

		MH_CreateHook(this->CPLAYER_UPDATE_ADDR, &PlayerUpdateHook, (LPVOID*)&original_update);
		MH_EnableHook(this->CPLAYER_UPDATE_ADDR);

		return;
	}
	//If !Enable, Disable All Created Hooks.

	MH_DisableHook(MH_ALL_HOOKS);
}
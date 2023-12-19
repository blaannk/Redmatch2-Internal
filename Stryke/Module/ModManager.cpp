#include "ModManager.h"

#include "Modules/TestMod.h"
#include "Modules/EspMod.h"
#include "Modules/SpreadMod.h"
#include "Modules/AimbotMod.h"
#include "Modules/WeaponMod.h"

void ModManager::initMods() {
	this->mods.push_back(std::shared_ptr<SModule>(new EspMod()));
	this->mods.push_back(std::shared_ptr<SModule>(new SpreadMod()));
	this->mods.push_back(std::shared_ptr<SModule>(new AimbotMod()));
	this->mods.push_back(std::shared_ptr<SModule>(new WeaponMod()));
}

void ModManager::deInitMods() {

	for (auto& mod : this->mods)
		mod.get()->setEnabled(false);
	this->mods.clear();
}
#include "WeaponMod.h"
#include "Module.h"

WeaponMod::WeaponMod() : SModule("Weapons", Category::MISC, "Hacks for weapons") {
	this->addBoolSetting("Enabled", &this->enabled);
	this->addBoolSetting("RapidFire", &this->rapidfire);
	this->addBoolSetting("NoReload", &this->noreload);
	this->addBoolSetting("InfAmmo", &this->infiniteammo);
}

void WeaponMod::onEnable() {
	if (this->getBase().getPlayer() == nullptr) {
		this->setEnabled(false);
		return;
	}
}

void WeaponMod::onFrame() {
	if (this->getBase().getPlayer() == nullptr) {
		this->setEnabled(false);
		return;
	}
	PlayerController_o* local_player = nullptr;
	if (this->getBase().getPlayer()->klass != nullptr) {
		if (this->getBase().getPlayer()->klass->static_fields != nullptr) {
			local_player = this->getBase().getPlayer()->klass->static_fields->LocalInstance;
		}
	}
	if (local_player != nullptr) {
		if (local_player->fields.items != nullptr) {
			Item_array* items = local_player->fields.items;
			for (int i = 0; i < items->max_length; i++) {
				Item_o* current_item = items->m_Items[i];
				if (current_item != nullptr) {
					ItemInfo_o* item_infos = current_item->fields.info;
					if (item_infos != nullptr) {
						if (this->rapidfire) {
							item_infos->fields.useDelay = 0.1f;
						}
						if (this->noreload) {
							item_infos->fields.reloadTime = 0;
						}
						if (this->infiniteammo) {
							item_infos->fields.magazineSize = 1337;
							item_infos->fields.startingAmmo = 1337;
						}
					}
				}
			}
		}
	}
}

void WeaponMod::onDisable() {
}

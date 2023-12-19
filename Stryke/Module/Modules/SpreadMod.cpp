#include "SpreadMod.h"
#include "Module.h"

SpreadMod::SpreadMod() : SModule("NoSpread", Category::MISC, "No Spread for weapons") {
	this->addBoolSetting("Enabled", &this->enabled);
}

void SpreadMod::onEnable() {
	if (this->getBase().getPlayer() == nullptr) {
		this->setEnabled(false);
		return;
	}
}

void SpreadMod::onFrame() {
	if (this->getBase().getPlayer() == nullptr) {
		this->setEnabled(false);
		return;
	}
	this->getBase().getPlayer()->SetSpread();
}

void SpreadMod::onDisable() {
	
}

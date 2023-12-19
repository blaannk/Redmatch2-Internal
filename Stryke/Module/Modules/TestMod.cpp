#include "TestMod.h"
#include "Module.h"

TestMod::TestMod() : SModule("TestMod", Category::MISC, "A Test Mod As A Template") {
	this->addBoolSetting("Enabled", &this->enabled);
	this->addNumSetting("Test Float", &this->testFloat, 1.f, 5.f);
}

void TestMod::onEnable() {
	if (this->getBase().getPlayer() == nullptr) {
		this->setEnabled(false);
		return;
	}
}

void TestMod::onFrame() {
	if (this->getBase().getPlayer() == nullptr) {
		this->setEnabled(false);
		return;
	}
}

void TestMod::onDisable() {
}

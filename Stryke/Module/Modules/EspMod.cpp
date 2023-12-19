#include "EspMod.h"
#include "Module.h"

#include "../../Draw/imgui.h"
#include "../../Draw/imgui_impl_dx11.h"
#include "../../Draw/imgui_impl_win32.h"

EspMod::EspMod() : SModule("EspMod", Category::VISUAL, "PlayerESP") {
	this->addBoolSetting("Enabled", &this->enabled);
	this->addNumSetting("Size", &this->line_len, 1.f, 5.f);
}

void EspMod::onEnable() {
	if (!this) {
		return;
	}
	std::shared_ptr<std::mutex> mutex = this->getBase().getPlayerListMutex();
	std::lock_guard<std::mutex> lock(*mutex);

	if (this->getBase().getPlayerList()->empty()) {
		this->setEnabled(false);
	}
}

void EspMod::onFrame() {
	if (!this) {
		return;
	}
	else {
		
		auto player_list_ptr = this->getBase().getPlayerList();
		std::shared_ptr<std::mutex> mutex = this->getBase().getPlayerListMutex();
		std::lock_guard<std::mutex> lock(*mutex);
		std::vector<CPlayer*> toRemove;

		if (!player_list_ptr->empty()) {
			for (CPlayer* element : *player_list_ptr) {
				if (element == nullptr) {
					return;
				}

				UnityEngine_Vector3_o player_pos = element->GetRealPosition();
				if (player_pos.fields.x != 0 && player_pos.fields.y != 0 && player_pos.fields.z != 0) {
					if (player_pos.fields.z > 0) {
						ImVec2 FirstPoint = { player_pos.fields.x, ImGui::GetIO().DisplaySize.y - player_pos.fields.y };
						ImVec2 BottomOfScreen = { ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y };
						//ImVec2 RectBack = { player_pos.fields.x - 20, ImGui::GetIO().DisplaySize.y - player_pos.fields.y - 20 };
						//ImVec2 RectTop = { player_pos.fields.x + 20, ImGui::GetIO().DisplaySize.y - player_pos.fields.y + 20 };
						ImDrawList* DrawList = ImGui::GetForegroundDrawList();
						//DrawList->AddRect(RectBack, RectTop, ImColor(255, 0, 0, 255));
						DrawList->AddLine(BottomOfScreen, FirstPoint, ImColor(255, 0, 0, 255), this->line_len);
					}
				}
				else {
					toRemove.push_back(element);
				}
			}
		}
		for (CPlayer* element : toRemove) {
			this->getBase().removePlayer(element);
		}
	}
}

void EspMod::onDisable() {
}

#include "AimbotMod.h"
#include "Module.h"
#include "imgui.h"

struct Vector2 {
	float x, y;

	Vector2(float x, float y) : x(x), y(y) {}

	float distance(const Vector2& autre) const {
		return std::sqrt((x - autre.x) * (x - autre.x) + (y - autre.y) * (y - autre.y));
	}
};

bool isAimbot(const Vector2& centreCercle, float rayonCercle, const Vector2& pointTest) {
	float distanceAuCentre = centreCercle.distance(pointTest);

	return distanceAuCentre <= rayonCercle;
}

bool isAimbotkey() {
	return GetAsyncKeyState(VK_RBUTTON) & 0x8000;
}

void MoveMouse(float x, float y)
{
	float ScreenCenterX = ImGui::GetIO().DisplaySize.x / 2;
	float ScreenCenterY = ImGui::GetIO().DisplaySize.y / 2;
	float TargetX = 0;
	float TargetY = 0;
	if (x != 0)
	{
		if (x > ScreenCenterX)
		{
			TargetX = -(ScreenCenterX - x);
			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
		}

		if (x < ScreenCenterX)
		{
			TargetX = x - ScreenCenterX;
			if (TargetX + ScreenCenterX < 0) TargetX = 0;
		}
	}

	if (y != 0)
	{
		if (y > ScreenCenterY)
		{
			TargetY = -(ScreenCenterY - y);
			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
		}

		if (y < ScreenCenterY)
		{
			TargetY = y - ScreenCenterY;
			if (TargetY + ScreenCenterY < 0) TargetY = 0;
		}
	}
	mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);

}

AimbotMod::AimbotMod() : SModule("Aimbot", Category::PLAYER, "Aimbot") {
	this->addBoolSetting("Enabled", &this->enabled);
	this->addNumSetting("FOV", &this->smooth, 1.f, 200.f);
}

void AimbotMod::onEnable() {
	if (!this) {
		return;
	}
	std::shared_ptr<std::mutex> mutex = this->getBase().getaPlayerListMutex();
	std::lock_guard<std::mutex> lock(*mutex);

	if (this->getBase().getaPlayerList()->empty()) {
		this->setEnabled(false);
	}
}

void AimbotMod::onFrame() {
	if (!this) {
		return;
	}
	else {

		ImDrawList* DrawList = ImGui::GetForegroundDrawList();
		ImVec2 center = ImVec2(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2);
		DrawList->AddCircle(center, this->smooth, ImColor(85, 133, 255, 255), 50.0f, 1.0f);


		auto player_list_ptr = this->getBase().getaPlayerList();
		std::shared_ptr<std::mutex> mutex = this->getBase().getaPlayerListMutex();
		std::lock_guard<std::mutex> lock(*mutex);
		std::vector<CPlayer*> toRemove;
		Vector2 best_target(0, 0);
		float best_distance = 100000;

		if (!player_list_ptr->empty()) {
			for (CPlayer* element : *player_list_ptr) {
				if (element == nullptr) {
					return;
				}
				if (element->klass == nullptr) {
					return;
				}
				if (element->klass->static_fields == nullptr) {
					return;
				}
				PlayerController_o* localplayer = element->klass->static_fields->LocalInstance;
				if (localplayer == nullptr) {
					return;
				}
				if (localplayer != reinterpret_cast<PlayerController_o*>(element)) {
					UnityEngine_Vector3_o player_pos = element->GetRealPosition();
					if (player_pos.fields.x != 0 && player_pos.fields.y != 0 && player_pos.fields.z != 0) {
						Vector2 player_pos_screen(player_pos.fields.x, player_pos.fields.y);
						Vector2 crossair(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2);
						if (player_pos.fields.z > 0) {
							if (isAimbot(crossair, this->smooth, player_pos_screen)) {
								if (crossair.distance(player_pos_screen) < best_distance) {
									best_distance = crossair.distance(player_pos_screen);
									best_target = player_pos_screen;
								}
							}
						}
					}
					else {
						toRemove.push_back(element);
					}
				}
			}
			if (best_target.x != 0 && best_target.y != 0) {
				if (isAimbotkey()) {
					MoveMouse(best_target.x, ImGui::GetIO().DisplaySize.y - best_target.y);
				}
			}
		}
		for (CPlayer* element : toRemove) {
			this->getBase().removeaPlayer(element);
		}
	}
}

void AimbotMod::onDisable() {
}

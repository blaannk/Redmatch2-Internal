#pragma once

#include <memory>
#include <mutex>
#include <list>
#include <algorithm>

#include "../../MinHook/include/MinHook.h"

#include "../../SDK/SDK.h"

class Hooks {
public:
	CExample* example;
	CPlayer* player;
	std::list<CPlayer*> player_list2 = {};
	std::shared_ptr<std::list<CPlayer*>> player_list = std::make_shared<std::list<CPlayer*>>();
	std::shared_ptr<std::mutex> player_list_mutex = std::make_shared<std::mutex>();
	std::shared_ptr<std::list<CPlayer*>> aplayer_list = std::make_shared<std::list<CPlayer*>>();
	std::shared_ptr<std::mutex> aplayer_list_mutex = std::make_shared<std::mutex>();
private:
	LPVOID EXAMPLE_EXAMPLEHOOK_ADDR = reinterpret_cast<LPVOID*>(gAssm + (uintptr_t)0xD34DB33F); // Fake Address (RVA For Your Hook)
	LPVOID CPLAYER_UPDATE_ADDR = reinterpret_cast<LPVOID*>(gAssm + (uintptr_t)0x5258B0);
public:
	std::shared_ptr<std::mutex> getPlayerListMutex() {
		return player_list_mutex;
	}
	std::shared_ptr<std::mutex> getaPlayerListMutex() {
		return aplayer_list_mutex;
	}
	CPlayer* getPlayer() { if (this->player) return this->player; else return nullptr; }
	std::shared_ptr<std::list<CPlayer*>> getPlayerList() {
		return player_list;
	}
	std::shared_ptr<std::list<CPlayer*>> getaPlayerList() {
		return aplayer_list;
	}
	CExample* getExample() { if (this->example) return this->example; }
	void addPlayer(CPlayer* player) {
		std::lock_guard<std::mutex> lock(*player_list_mutex);
		player_list->push_back(player);
	}
	void addaPlayer(CPlayer* player) {
		std::lock_guard<std::mutex> lock(*aplayer_list_mutex);
		aplayer_list->push_back(player);
	}

	void removePlayer(CPlayer* player) {
		player_list->remove(player);
	}
	void removeaPlayer(CPlayer* player) {
		aplayer_list->remove(player);
	}

	bool isPlayerInList(CPlayer* player) {
		std::lock_guard<std::mutex> lock(*player_list_mutex);
		return std::find(player_list->begin(), player_list->end(), player) != player_list->end();
	}
	bool isaPlayerInList(CPlayer* player) {
		std::lock_guard<std::mutex> lock(*aplayer_list_mutex);
		return std::find(aplayer_list->begin(), aplayer_list->end(), player) != aplayer_list->end();
	}
public:
	void AllHooks(bool enable);
};

inline Hooks hook = Hooks();

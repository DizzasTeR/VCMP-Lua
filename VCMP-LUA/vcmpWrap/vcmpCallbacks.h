#pragma once
#include "utility.h"
#include "EventManager/EventManager.h"
#include "Timer/TimerManager.h"
#include "Classes/Player.h"
#include "Classes/Vehicle.h"

#define DEBUG_ENABLED
#undef DEBUG_ENABLED

extern PluginFuncs* g_Funcs;
extern PluginCallbacks* g_Calls;
extern sol::state Lua;

void RegisterVCMPCallbacks() {
	/*** Server ***/
	g_Calls->OnServerInitialise = [] () -> uint8_t {
#ifdef DEBUG_ENABLED
		std::cout << "onServerinitialise" << std::endl;
#endif
		try {
			auto handlers = EventManager::GetHandlers("onServerInit");
			for (auto fn : handlers) {
				fn();
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
		return (uint8_t) 1;
	};

	g_Calls->OnServerShutdown = []() -> void {
#ifdef DEBUG_ENABLED
		std::cout << "OnServerShutdown" << std::endl;
#endif
		try {
			auto handlers = EventManager::GetHandlers("onServerShutdown");
			for (auto fn : handlers) {
				fn();
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnServerFrame = [](float elapsedTime) -> void {
#ifdef DEBUG_ENABLED
		//std::cout << "OnServerFrame" << std::endl;
#endif
		TimerManager::OnFrame(elapsedTime);
		try {
			auto handlers = EventManager::GetHandlers("onServerFrame");
			for (auto fn : handlers) {
				fn(elapsedTime);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};
	
	g_Calls->OnPluginCommand = [](uint32_t commandIdentifier, const char* message) -> uint8_t {
#ifdef DEBUG_ENABLED
		std::cout << "OnPluginCommand" << std::endl;
#endif
		try {
			auto handlers = EventManager::GetHandlers("onPluginCommand");
			for (auto fn : handlers)
				fn(commandIdentifier, message);
			for (auto fn : handlers) {
				fn();
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
		return (uint8_t) 1;
	};

	g_Calls->OnIncomingConnection = [](char* playerName, size_t nameBufferSize, const char* userPassword, const char* ipAddress) -> uint8_t {
#ifdef DEBUG_ENABLED
		std::cout << "OnIncomingConnection" << std::endl;
#endif
		try {
			auto handlers = EventManager::GetHandlers("onPlayerConnection");
			for (auto fn : handlers)
				fn(playerName, nameBufferSize, userPassword, ipAddress);
			for (auto fn : handlers) {
				fn();
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
		return (uint8_t) 1;
	};

	/*** Player ***/
	g_Calls->OnClientScriptData = [](int32_t playerId, const uint8_t* data, size_t size) {
		
	};
	
	g_Calls->OnPlayerConnect = [](int32_t playerId) {
#ifdef DEBUG_ENABLED
		std::cout << "onPlayerConnect" << std::endl;
#endif
		Player* player = Player::Register(playerId);
		try {
			auto handlers = EventManager::GetHandlers("onPlayerConnect");
			for (auto fn : handlers)
				fn(player);
			for (auto fn : handlers) {
				fn();
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};
	
	g_Calls->OnPlayerDisconnect = [](int32_t playerId, vcmpDisconnectReason reason) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerDisconnect" << std::endl;
#endif
		Player* player = Player::Get(playerId);
		try {
			auto handlers = EventManager::GetHandlers("onPlayerDisconnect");
			for (auto fn : handlers)
				fn(player);
			for (auto fn : handlers) {
				fn();
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};
	g_Calls->OnPlayerModuleList = [](int32_t playerId, const char* list) {
		
	};

	g_Calls->OnPlayerRequestClass = [](int32_t playerId, int32_t offset) -> uint8_t {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerRequestClass" << std::endl;
#endif
		Player* player = Player::Get(playerId);
		uint8_t ret = 1;
		try {
			auto handlers = EventManager::GetHandlers("onPlayerRequestClass");
			for (auto fn : handlers) {
				fn(player);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					ret = 0;
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
		return ret;
	};

	g_Calls->OnPlayerRequestSpawn = [](int32_t playerId) -> uint8_t {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerRequestSpawn" << std::endl;
#endif
		Player* player = Player::Get(playerId);
		uint8_t ret = 1;
		try {
			auto handlers = EventManager::GetHandlers("onPlayerRequestSpawn");
			for (auto fn : handlers) {
				fn(player);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					ret = 0;
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
		return ret;
	};

	g_Calls->OnPlayerSpawn = [](int32_t playerId) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerSpawn" << std::endl;
#endif
		Player* player = Player::Get(playerId);
		try {
			auto handlers = EventManager::GetHandlers("onPlayerSpawn");
			for (auto fn : handlers) {
				fn(player);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerDeath = [](int32_t playerId, int32_t killerId, int32_t reason, vcmpBodyPart bodyPart) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerDeath" << std::endl;
#endif
		if (!g_Funcs->IsPlayerConnected(killerId)) {
			try {
				Player* player = Player::Get(playerId);
				auto handlers = EventManager::GetHandlers("onPlayerWasted");
				for (auto fn : handlers) {
					if (reason == 43 || reason == 50)
						reason = 43; // drowned
					else if (reason == 39 && bodyPart == 7)
						reason = 39; // car crash
					else if (reason == 39 || reason == 40 || reason == 44)
						reason = 44; // fell

					fn(player, reason);
					if (EventManager::m_bWasEventCancelled) {
						EventManager::cancelEvent();
						break;
					}
					return;
				}
			}
			catch (sol::error e) {
				OutputError(e.what());
			}
		}

		try {
			Player* player = Player::Get(playerId);
			Player* killer = Player::Get(killerId);
			auto handlers = EventManager::GetHandlers("onPlayerKill");
			for (auto fn : handlers) {
				fn(killer, player, reason, bodyPart);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerUpdate = [](int32_t playerId, vcmpPlayerUpdate updateType) {
#ifdef DEBUG_ENABLED
		//std::cout << "OnPlayerUpdate" << std::endl;
#endif
		Player* player = Player::Get(playerId);
		try {
			auto handlers = EventManager::GetHandlers("onPlayerUpdate");
			for (auto fn : handlers) {
				fn(player);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerRequestEnterVehicle = [](int32_t playerId, int32_t vehicleId, int32_t slotIndex) -> uint8_t {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerRequestEnterVehicle" << std::endl;
#endif
		uint8_t ret = 1;
		try {
			Player* player = Player::Get(playerId);
			Vehicle* vehicle = Vehicle::Get(vehicleId);
			auto handlers = EventManager::GetHandlers("onPlayerRequestEnterVehicle");
			for (auto fn : handlers) {
				fn(player, vehicle, vehicleId, slotIndex);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					ret = 0;
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
		return ret;
	};

	g_Calls->OnPlayerEnterVehicle = [](int32_t playerId, int32_t vehicleId, int32_t slotIndex) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerEnterVehicle" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			Vehicle* vehicle = Vehicle::Get(vehicleId);
			auto handlers = EventManager::GetHandlers("onPlayerEnterVehicle");
			for (auto fn : handlers) {
				fn(player, vehicle, slotIndex);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerExitVehicle = [](int32_t playerId, int32_t vehicleId) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerExitVehicle" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			Vehicle* vehicle = Vehicle::Get(vehicleId);
			auto handlers = EventManager::GetHandlers("onPlayerExitVehicle");
			for (auto fn : handlers) {
				fn(player, vehicle);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerNameChange = [](int32_t playerId, const char* oldName, const char* newName) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerNameChange" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerNameChange");
			for (auto fn : handlers) {
				fn(player, oldName, newName);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerStateChange = [](int32_t playerId, vcmpPlayerState oldState, vcmpPlayerState newState) {
#ifdef DEBUG_ENABLED
		//std::cout << "OnPlayerStateChange" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerStateChange");
			for (auto fn : handlers) {
				fn(player, oldState, newState);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerActionChange = [](int32_t playerId, int32_t oldAction, int32_t newAction) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerActionChange" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerActionChange");
			for (auto fn : handlers) {
				fn(player, oldAction, newAction);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerOnFireChange = [](int32_t playerId, uint8_t isOnFire) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerOnFireChange" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerFireChange");
			for (auto fn : handlers) {
				fn(player, isOnFire);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerCrouchChange = [](int32_t playerId, uint8_t isCrouching) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerCrouchChange" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerCrouchChange");
			for (auto fn : handlers) {
				fn(player, isCrouching);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerGameKeysChange = [](int32_t playerId, uint32_t oldKeys, uint32_t newKeys) {
#ifdef DEBUG_ENABLED
		//std::cout << "OnPlayerGameKeysChange" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerGameKeysChange");
			for (auto fn : handlers) {
				fn(player, oldKeys, newKeys);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerBeginTyping = [](int32_t playerId) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerBeginTyping" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerBeginTyping");
			for (auto fn : handlers) {
				fn(player);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerEndTyping = [](int32_t playerId) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerEndTyping" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerFinishTyping");
			for (auto fn : handlers) {
				fn(player);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerAwayChange = [](int32_t playerId, uint8_t isAway) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerAwayChange" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerAwayChange");
			for (auto fn : handlers) {
				fn(player, isAway);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerMessage = [](int32_t playerId, const char* message) -> uint8_t {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerMessage" << std::endl;
#endif
		uint8_t ret = 1;
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerMessage");
			for (auto fn : handlers) {
				fn(player, message);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					ret = 0;
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
		return ret;
	};

	g_Calls->OnPlayerCommand = [](int32_t playerId, const char* message) -> uint8_t {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerCommand" << std::endl;
#endif
		uint8_t ret = 1;
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerCommand");
				std::string data(message);
				std::vector<std::string> args = std::split(data, ' ');
			for (auto fn : handlers) {
				if (args.size() <= 0) { // No command at all? Pass nil
					fn(player, sol::lua_nil, sol::lua_nil);
					if (EventManager::m_bWasEventCancelled) {
						EventManager::cancelEvent();
						ret = 0;
						break;
					}
				}
				else {
					std::string command = args.at(0);
					args.erase(args.begin());
					if (args.size() > 0) {
						fn(player, command, sol::as_table_t<std::vector<std::string>>(args));
						if (EventManager::m_bWasEventCancelled) {
							EventManager::cancelEvent();
							ret = 0;
							break;
						}
					}
					else {
						fn(player, command, sol::lua_nil);
						if (EventManager::m_bWasEventCancelled) {
							EventManager::cancelEvent();
							ret = 0;
							break;
						}
					}
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
		return ret;
	};

	g_Calls->OnPlayerPrivateMessage = [](int32_t playerId, int32_t targetPlayerId, const char* message) -> uint8_t {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerPrivateMessage" << std::endl;
#endif
		uint8_t ret = 1;
		try {
			Player* player = Player::Get(playerId);
			Player* targetPlayer = Player::Get(targetPlayerId);
			auto handlers = EventManager::GetHandlers("onPlayerPM");
			for (auto fn : handlers) {
				fn(player, targetPlayer, message);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					ret = 0;
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
		return ret;
	};

	g_Calls->OnPlayerKeyBindDown = [](int32_t playerId, int32_t bindId) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerKeyBindDown" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerKeyDown");
			for (auto fn : handlers) {
				fn(player, bindId);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerKeyBindUp = [](int32_t playerId, int32_t bindId) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerKeyBindUp" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerKeyUp");
			for (auto fn : handlers) {
				fn(player, bindId);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerSpectate = [](int32_t playerId, int32_t targetPlayerId) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerSpectate" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			Player* targetPlayer = Player::Get(targetPlayerId);
			auto handlers = EventManager::GetHandlers("onPlayerSpectate");
			for (auto fn : handlers) {
				fn(player, targetPlayer);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnPlayerCrashReport = [](int32_t playerId, const char* report) {
#ifdef DEBUG_ENABLED
		std::cout << "OnPlayerCrashReport" << std::endl;
#endif
		try {
			Player* player = Player::Get(playerId);
			auto handlers = EventManager::GetHandlers("onPlayerCrashReport");
			for (auto fn : handlers) {
				fn(player, report);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};
	
	g_Calls->OnVehicleUpdate = [](int32_t vehicleId, vcmpVehicleUpdate updateType) {
#ifdef DEBUG_ENABLED
		std::cout << "OnVehicleUpdate" << std::endl;
#endif
		try {
			Vehicle* vehicle = Vehicle::Get(vehicleId);
			auto handlers = EventManager::GetHandlers("onVehicleUpdate");
			for (auto fn : handlers) {
				fn(vehicle);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnVehicleExplode = [](int32_t vehicleId) {
#ifdef DEBUG_ENABLED
		std::cout << "OnVehicleExplode" << std::endl;
#endif
		try {
			Vehicle* vehicle = Vehicle::Get(vehicleId);
			auto handlers = EventManager::GetHandlers("onVehicleExplode");
			for (auto fn : handlers) {
				fn(vehicle);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};

	g_Calls->OnVehicleRespawn = [](int32_t vehicleId) {
#ifdef DEBUG_ENABLED
		std::cout << "OnVehicleRespawn" << std::endl;
#endif
		try {
			Vehicle* vehicle = Vehicle::Get(vehicleId);
			auto handlers = EventManager::GetHandlers("onVehicleRespawn");
			for (auto fn : handlers) {
				fn(vehicle);
				if (EventManager::m_bWasEventCancelled) {
					EventManager::cancelEvent();
					break;
				}
			}
		}
		catch (sol::error e) {
			OutputError(e.what());
		}
	};










//	/*** Object ***/
//	g_Calls->OnObjectShot = [](int32_t objectId, int32_t playerId, int32_t weaponId) {
//#ifdef DEBUG_ENABLED
//		std::cout << "OnObjectShot" << std::endl;
//#endif
//		lua_getglobal(LUA, "onObjectShot");
//		if (lua_isfunction(LUA, -1)) {
//			lua_pushinteger(LUA, (lua_Integer) objectId);
//			lua_pushinteger(LUA, (lua_Integer) playerId);
//			lua_pushinteger(LUA, (lua_Integer) weaponId);
//			VerifyLua(LUA, lua_pcall(LUA, 3, 0, 0));
//		}
//		else { lua_pop(LUA, -1); }
//	};
//	g_Calls->OnObjectTouched = [](int32_t objectId, int32_t playerId) {
//#ifdef DEBUG_ENABLED
//		std::cout << "OnObjectTouched" << std::endl;
//#endif
//		lua_getglobal(LUA, "onObjectTouched");
//		if (lua_isfunction(LUA, -1)) {
//			lua_pushinteger(LUA, (lua_Integer) objectId);
//			lua_pushinteger(LUA, (lua_Integer) playerId);
//			VerifyLua(LUA, lua_pcall(LUA, 2, 0, 0));
//		}
//		else { lua_pop(LUA, -1); }
//	};
//
//	/*** Pickup ***/
//
//	g_Calls->OnPickupPickAttempt = [](int32_t pickupId, int32_t playerId) -> uint8_t {
//#ifdef DEBUG_ENABLED
//		std::cout << "OnPickupPickAttempt" << std::endl;
//#endif
//		lua_getglobal(LUA, "onPickupPickAttempt");
//		if (lua_isfunction(LUA, -1)) {
//			lua_pushinteger(LUA, (lua_Integer) pickupId);
//			lua_pushinteger(LUA, (lua_Integer) playerId);
//			if (VerifyLua(LUA, lua_pcall(LUA, 2, 0, 0))) {
//				lua_Integer returnValue = Lua::GetInteger();
//				return (returnValue == NULL ? 1 : (uint8_t) returnValue);
//			}
//		}
//		else { lua_pop(LUA, -1); }
//		return (uint8_t) 1;
//	};
//	g_Calls->OnPickupPicked = [](int32_t pickupId, int32_t playerId) {
//#ifdef DEBUG_ENABLED
//		std::cout << "OnPickupPicked" << std::endl;
//#endif
//		lua_getglobal(LUA, "onPickupPicked");
//		if (lua_isfunction(LUA, -1)) {
//			lua_pushinteger(LUA, (lua_Integer) pickupId);
//			lua_pushinteger(LUA, (lua_Integer) playerId);
//			VerifyLua(LUA, lua_pcall(LUA, 2, 0, 0));
//		}
//		else { lua_pop(LUA, -1); }
//	};
//	g_Calls->OnPickupRespawn = [](int32_t pickupId) {
//#ifdef DEBUG_ENABLED
//		std::cout << "OnPickupRespawn" << std::endl;
//#endif
//		lua_getglobal(LUA, "onPickupRespawn");
//		if (lua_isfunction(LUA, -1)) {
//			lua_pushinteger(LUA, (lua_Integer) pickupId);
//			VerifyLua(LUA, lua_pcall(LUA, 1, 0, 0));
//		}
//		else { lua_pop(LUA, -1); }
//	};
//
//	/*** Checkpoint ***/
//
//	g_Calls->OnCheckpointEntered = [](int32_t checkPointId, int32_t playerId) {
//#ifdef DEBUG_ENABLED
//		std::cout << "OnCheckpointEntered" << std::endl;
//#endif
//		lua_getglobal(LUA, "onCheckpointEntered");
//		if (lua_isfunction(LUA, -1)) {
//			lua_pushinteger(LUA, (lua_Integer) checkPointId);
//			lua_pushinteger(LUA, (lua_Integer) playerId);
//			VerifyLua(LUA, lua_pcall(LUA, 2, 0, 0));
//		}
//		else { lua_pop(LUA, -1); }
//	};
//	g_Calls->OnCheckpointExited = [](int32_t checkPointId, int32_t playerId) {
//#ifdef DEBUG_ENABLED
//		std::cout << "OnCheckpointExited" << std::endl;
//#endif
//		lua_getglobal(LUA, "onCheckpointExited");
//		if (lua_isfunction(LUA, -1)) {
//			lua_pushinteger(LUA, (lua_Integer) checkPointId);
//			lua_pushinteger(LUA, (lua_Integer) playerId);
//			VerifyLua(LUA, lua_pcall(LUA, 2, 0, 0));
//		}
//		else { lua_pop(LUA, -1); }
//	};
//
//	/*** Misc ***/
//
//	g_Calls->OnEntityPoolChange = [](vcmpEntityPool entityType, int32_t entityId, uint8_t isDeleted) {
//#ifdef DEBUG_ENABLED
//		std::cout << "OnEntityPoolChange" << std::endl;
//#endif
//		lua_getglobal(LUA, "onEntityPoolChange");
//		if (lua_isfunction(LUA, -1)) {
//			lua_pushinteger(LUA, (lua_Integer) entityType);
//			lua_pushinteger(LUA, (lua_Integer) entityId);
//			lua_pushinteger(LUA, (lua_Integer) isDeleted);
//			VerifyLua(LUA, lua_pcall(LUA, 3, 0, 0));
//		}
//		else { lua_pop(LUA, -1); }
//	};
//	g_Calls->OnServerPerformanceReport = [](size_t entryCount, const char** descriptions, uint64_t* times) {
//#ifdef DEBUG_ENABLED
//		std::cout << "OnServerPerformanceReport" << std::endl;
//#endif
//		lua_getglobal(LUA, "onServerPerformanceReport");
//		if (lua_isfunction(LUA, -1)) {
//			lua_pushinteger(LUA, (lua_Integer) entryCount);
//			lua_pushstring(LUA, *descriptions);
//			lua_pushinteger(LUA, (lua_Integer) entryCount);
//			VerifyLua(LUA, lua_pcall(LUA, 3, 0, 0));
//		}
//		else { lua_pop(LUA, -1); }
//	};
}
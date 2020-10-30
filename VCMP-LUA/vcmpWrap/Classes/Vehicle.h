#pragma once
#include "pch.h"
#include "../Constants.h"

#define MAX_VEHICLES 1000

class Player;

class Vehicle {
public:
	static std::vector<Vehicle*> s_Vehicles;

	static void Init(sol::state*);
	static void Register(Vehicle*);
	static Vehicle* Get(int32_t);
	static void Unregister(Vehicle*);

	/*** @Lua static ***/
	static inline const char* getStaticType() { return "Vehicle"; }

	/*** CONSTRUCTORS ***/
	Vehicle(int32_t, int32_t, float, float, float, float, int32_t = -1, int32_t = -1);
	Vehicle(int32_t, int32_t, sol::table, int32_t = -1, int32_t = -1);

	/*** DESTRUCTOR(S) ***/
	~Vehicle() { destroy(); };

	/*** METHODS ***/
	bool destroy();
	bool isStreamedForPlayer(Player*);
	bool getOption(vcmpVehicleOption) const;
	void setOption(vcmpVehicleOption, bool);
	sol::as_table_t<std::vector<float>> getSpeed(vcmpVehicleSpeed type = vcmpVehicleSpeed::Normal) const;
	sol::as_table_t<std::vector<float>> getSpeedEx() const;
	void setSpeed(vcmpVehicleSpeed, float, float, float, bool);
	void setSpeedDefault(float, float, float, bool);
	void setSpeedEx(vcmpVehicleSpeed, sol::table, bool);
	void setSpeedExDefault(sol::table, bool);

	/*** READ-ONLY ***/
	int32_t getID() const;
	int32_t getModel() const;
	
	/*** PROPERTIES ***/
	int32_t getWorld() const;
	int32_t getRadio() const;
	uint32_t getIdleRespawnTime() const;
	uint32_t getLightsData() const;
	uint32_t getDamage() const;
	float getHealth() const;
	sol::as_table_t<std::vector<float>> getSpawnPosition() const;
	sol::as_table_t<std::vector<float>> getSpawnRotation() const;
	sol::as_table_t<std::vector<int32_t>> getColor() const;

	void setWorld(int32_t);
	void setRadio(int32_t);
	void setIdleRespawnTime(uint32_t);
	void setLightsData(uint32_t);
	void setDamage(uint32_t);
	void setHealth(float);
	void setSpawnPosition(sol::table);
	void setSpawnRotation(sol::table);
	void setColor(sol::table);

	/*** COMMON PROPERTIES AMONGST ENTITIES ***/
	inline const char* getType() { return Vehicle::getStaticType(); }

	sol::as_table_t<std::vector<float>> getPosition() const;
	void setPosition(sol::table);

	sol::as_table_t<std::vector<float>> getRotation() const;
	void setRotation(sol::table);
	/******/
private:
	int32_t m_ID;
};
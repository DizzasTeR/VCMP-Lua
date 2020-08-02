#include "vcmpTimer.h"

vcmpTimer::vcmpTimer(sol::protected_function callback, unsigned int interval, int32_t repeat, sol::table args)
	: m_callback(callback), m_interval(interval), m_repeat(repeat), m_args(args)
{
	this->bIsValid = true;
}

void vcmpTimer::Init(sol::state* Lua) {}
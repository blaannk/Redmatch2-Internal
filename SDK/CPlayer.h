#pragma once

#include "SRC.h"

inline constexpr auto W2S_ADDR = 0x17F1D40;
inline constexpr auto GET_POSITION_ADDR = 0x169AA50;
inline constexpr auto GET_TRANSFORM_ADDR = 0x17F5100;
inline constexpr auto GET_MAIN_CAMERA_ADDR = 0x17F23B0;
inline constexpr auto GET_OBJECTS_ADDR = 0x1996FE0;
inline constexpr auto GET_OBJECT_TYPE_ADDR = 0x113EA00;

struct CPlayer {
	PlayerController_c* klass;
	void* monitor;
	PlayerController_Fields fields;

	UnityEngine_Vector3_o GetRealPosition();
	void SetSpread();
};

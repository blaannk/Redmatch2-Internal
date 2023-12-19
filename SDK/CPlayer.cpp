#include "CPlayer.h"

typedef UnityEngine_Transform_o* (__stdcall* GetTransformFunc)(void* instance);
GetTransformFunc get_transform = reinterpret_cast<GetTransformFunc>(gAssm + GET_TRANSFORM_ADDR);

typedef UnityEngine_Vector3_o(__stdcall* GetPositionFunc)(void* instance);
GetPositionFunc get_position = reinterpret_cast<GetPositionFunc>(gAssm + GET_POSITION_ADDR);

typedef UnityEngine_Vector3_o(__stdcall* W2SFunc)(UnityEngine_Camera_o* _this, UnityEngine_Vector3_o position);
W2SFunc w2spoint = reinterpret_cast<W2SFunc>(gAssm + W2S_ADDR);

typedef UnityEngine_Camera_o* (__stdcall* GetMainCamera)();
GetMainCamera get_main_camera = reinterpret_cast<GetMainCamera>(gAssm + GET_MAIN_CAMERA_ADDR);

UnityEngine_Camera_o* get_camera_safe() {
	__try {
		UnityEngine_Camera_o* camera = get_main_camera();
		return camera;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return nullptr;
	}
}

UnityEngine_Vector3_o get_position_safe(void* instance) {
	__try {
		UnityEngine_Vector3_o position = get_position(instance);
		return position;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return UnityEngine_Vector3_o{ UnityEngine_Vector3_Fields {0, 0, 0} };
	}
}

UnityEngine_Transform_o* get_transform_safe(void* instance) {
	__try {
		UnityEngine_Transform_o* transform = get_transform(instance);
		return transform;
	} __except (EXCEPTION_EXECUTE_HANDLER) {
		return nullptr;
	}
}

UnityEngine_Vector3_o w2s_safe(UnityEngine_Camera_o* camera, UnityEngine_Vector3_o position) {
	__try {
		UnityEngine_Vector3_o new_position = w2spoint(camera, position);
		return new_position;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return UnityEngine_Vector3_o{ UnityEngine_Vector3_Fields {0, 0, 0} };
	}
}

void CPlayer::SetSpread() {
	PlayerController_o* local_player = this->klass->static_fields->LocalInstance;
	if (local_player != nullptr) {
		local_player->fields.bulletSpread = 0;
	}
}

UnityEngine_Vector3_o CPlayer::GetRealPosition() {

	PlayerController_o* LocalPlayerInstance = nullptr;
	UnityEngine_Camera_o* LocalPlayerCamera = nullptr;
		LocalPlayerCamera = get_camera_safe();
		if (LocalPlayerCamera != nullptr) {
			UnityEngine_Transform_o* transform = get_transform_safe(this);
			if (transform != nullptr) {
				UnityEngine_Vector3_o player_pos = get_position_safe(transform);
				if (player_pos.fields.x != 0 && player_pos.fields.y != 0 && player_pos.fields.z != 0) {
					UnityEngine_Vector3_o player_pos_screen = w2s_safe(LocalPlayerCamera, player_pos);
					return player_pos_screen;
				}
				else {
					return UnityEngine_Vector3_o{ UnityEngine_Vector3_Fields {0, 0, 0} };
				}
			}
			else {
				return UnityEngine_Vector3_o{ UnityEngine_Vector3_Fields {0, 0, 0} };
			}
		}
		else {
			return UnityEngine_Vector3_o{ UnityEngine_Vector3_Fields {0, 0, 0} };
		}
}
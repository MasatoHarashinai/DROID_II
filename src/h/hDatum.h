#pragma once

#include "DxLib.h"

/* Macro */
const float PI					= 3.1415926535897932384626433832795f;
const float WARNING_TIME		= 6.85f;
const int red					= GetColor(255, 0, 0);
const int green					= GetColor(0, 255, 0);
const int blue					= GetColor(0, 0, 255);
const int yellow				= GetColor(255, 255, 0);
const int sky_blue				= GetColor(80, 80, 255);
const int black					= GetColor(0, 0, 0);

/* System */

const int MAX_LEVEL				= 50;
const int COMMON_NUM			= 15;
const int BEAM_NUM				= 30;
const int WARNING_INDEX			= 11;
const int BOSS_INDEX			= 12;
const int BOSS_WEAPON_BEAM		= 0;
const int BOSS_WEAPON_LASER		= 1;
const int WindowWidth			= 1280;
const int WindowHeight			= 960;
const int GameScreenWidth		= WindowWidth - 256;
const int GameScreenHeight		= WindowHeight - 61;

/* Resource Path */
#define RSC_IMG_PREFIX				"resource/image/"
#define RSC_SND_PREFIX				"resource/sound/"
#define RSC_PATH(prefix, file)		prefix ## file 

enum E_UPGRADE {
	NONE,
	RAPID,
	BULLET_SPEED,
	BARRIAR
};

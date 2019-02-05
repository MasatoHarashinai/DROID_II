#pragma once

#include "DxLib.h"

#define PI 3.1415926535897932384626433832795f

#define MAX_LEVEL 50
#define COMMON_NUM 15
#define BEAM_NUM 30

#define WARNING_INDEX 11
#define BOSS_INDEX 12
#define WARNING_TIME 6.85f

#define BOSS_WEAPON_BEAM 0
#define BOSS_WEAPON_LASER 1


const int WindowWidth = 1280;
const int WindowHeight = 960;
const int GameScreenWidth = WindowWidth - 256;
const int GameScreenHeight = WindowHeight - 61;


const int red = GetColor(255,0,0);
const int green = GetColor(0,255,0);
const int blue = GetColor(0,0,255);
const int yellow = GetColor(255,255,0);
const int sky_blue = GetColor(80,80,255);
const int black = GetColor(0,0,0);

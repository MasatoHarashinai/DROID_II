#pragma once
#include "hBeam.h"
#include "hBoss.h"
#include "hPlayer.h"

class cEnemyWeapon : public cBeam
{
private :
	double fire_dir; // ���x�v�Z�p���ˊp�x
	double angle; // �`�掞�p�p�x 
	int target_x; // �ڕW��X���W
	int target_y;
	int speed_x;
	int speed_y;

	int weapon_pattern;
	int laser_rest;
	int laser_count;
	int laser_location;
	int laser_wait;
	bool laser_max;

	int graph_beam;
	int graph_laser;
	int sound_beam;
	int sound_laser;
public:
	cEnemyWeapon(int x, int y, int weapon_pattern);

	bool GetLaserMax();

	void SetMovePattern(int weapon_pattern);
	void SetLaserLocation(int laser_location);

	void Fire(cPlayer *player);
	void Init(int x, int y);
	void Draw(cBoss *boss);
	void Move();
};
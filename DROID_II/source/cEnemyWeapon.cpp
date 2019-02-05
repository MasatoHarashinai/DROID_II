#include "hEnemyWeapon.h"
#include "DxLib.h"
#include "hPlayer.h"
#include <math.h>

cEnemyWeapon::cEnemyWeapon(int x, int y, int weapon_pattern) : cBeam(x,y)
{
	i_body = LoadGraph("image/Missile.png");
	s_fire = LoadSoundMem("sound/MissileFire.mp3");
	graph_beam = LoadGraph("image/Beam.png");
	graph_laser = LoadGraph("image/Laser.png");
	sound_beam = LoadSoundMem("sound/BeamFire.mp3");
	sound_laser = LoadSoundMem("sound/LaserFire.wav");
	GetGraphSize(i_body, &width, &height);
	ChangeVolumeSoundMem( 255 * 45 / 100, s_fire ) ;
	ChangeVolumeSoundMem( 255 * 45 / 100, s_hit ) ;
	this->weapon_pattern = weapon_pattern;
	speed = 12;
}

bool cEnemyWeapon::GetLaserMax(){ return laser_max; }

void cEnemyWeapon::SetMovePattern(int weapon_pattern){ this->weapon_pattern = weapon_pattern; }
void cEnemyWeapon::SetLaserLocation(int laser_location){ this->laser_location = laser_location; }

void cEnemyWeapon::Fire(cPlayer *player)  // 発射する
{
	if(CheckSoundMem(s_fire)) StopSoundMem(s_fire);
	PlaySoundMem(s_fire, DX_PLAYTYPE_BACK);
	active = true; // 生存フラグをTrueにする
	inited = false;
	target_x = (int)(player->GetX() + player->GetWidth() / 2 - x);
	target_y = (int)(player->GetY() + player->GetHeight() / 2 - y);
	fire_dir = atan2((double)target_y,(double)target_x);
	speed_x = (int)(cos(fire_dir) * speed);
	speed_y = (int)(sin(fire_dir) * speed);
}	
void cEnemyWeapon::Init(int x, int y)
{
	this->x = x;
	this->y = y;
	this->weapon_pattern = weapon_pattern;
	switch(weapon_pattern)
	{
	case 0:
		i_body = graph_beam;
		GetGraphSize(i_body, &width, &height);
		break;
	case 1:
		i_body = graph_laser;
		s_fire = sound_laser;
		ChangeVolumeSoundMem( 255 * 30 / 100, s_fire ) ;
		GetGraphSize(i_body, &width, &height);
		speed = 12;
		laser_rest = 60*3;
		laser_count = 0;
		laser_wait = 0;
		laser_max = false;
		height = laser_count;
		break;
	}
	active = false;
	inited = true;
}
void cEnemyWeapon::Draw(cBoss *boss)
{
	
	switch(weapon_pattern)
	{
	case 0:
		DrawRotaGraph(x,y,1,fire_dir -  PI / 2,i_body,true,false);
		break;
	case 1:
		if(laser_rest <= 0 && boss->GetStart())
		{
			if(laser_count == 0) PlaySoundMem(s_fire,DX_PLAYTYPE_LOOP);

			if(laser_location == 0) // 左の砲身から発射する
			{
				DrawRectGraph(boss->GetX() + (boss->GetWidth() * 1 / 3 - 18) - (width / 2),boss->GetY()+boss->GetHeight() / 3,
					0,0,width,laser_count,i_body,true,false);
			}
			else if(laser_location == 1) // 右の砲身から発射する
			{
				DrawRectGraph(boss->GetX() + (boss->GetWidth()* 2 / 3 + 18) - (width / 2),boss->GetY()+boss->GetHeight() / 3,
					0,0,width,laser_count,i_body,true,false);
			}
			if(laser_count < GameScreenHeight) 
			{
				laser_count += speed;
				height = laser_count;
			}
			else if(laser_wait < 60 * 2 )
			{
				laser_wait++;
			}
			else
			{
				laser_max = true;
			}
		}
		else
		{
			if(CheckSoundMem(s_fire)) StopSoundMem(s_fire); 
			laser_rest--;
		}

		break;
	}
}
void cEnemyWeapon::Move()
{
	switch(weapon_pattern)
	{
	case 0:
		x += speed_x;
		y += speed_y;
		break;
	case 1:
		break;
	}
}
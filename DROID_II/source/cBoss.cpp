#include "DxLib.h"
#include "hBoss.h"
#include "hDatum.h"

cBoss::cBoss()
{
	i_body = LoadGraph("image/LastBoss.png");
	GetGraphSize(i_body,&width,&height);
	x = GameScreenWidth / 2 - width / 2;
	y = -1 * height;
	fire_span = 40;
	speed = 6;
	hp = 100;
	count = 0;
	start = false;
	alive = false;	// 生存フラグを設定
}

int cBoss::GetFireSpan(){ return fire_span; }
bool cBoss::GetStart(){ return start; }

void cBoss:: SetFireSpan(int fire_span){ this->fire_span = fire_span; }

void cBoss::Move()
{
	switch(count)
	{
	case 0:
		if(y < 0) 
		{
			y++;
		}
		else
		{
			count = 1;
			move_count = 0;
		}
		break;
	case 1:
		if(move_count <= 90)
		{
			move_count++;
		}
		else
		{
			move_count = 0;
			start = true;
			count = 2;
		}
		break;
	case 2:
		if(x+width < GameScreenWidth)
		{
			if(move_count % 2 == 0)
			{
				x++;
			}
			move_count++;
		}
		else
		{
			count = 3;
		}
		break;
	case 3:
		if(x > 0)
		{
			if(move_count % 2 == 0)
			{
				x--;
			}
			move_count++;
		}
		else
		{
			count = 2;
		}
	}
}

void cBoss::Init()
{
	x = GameScreenWidth / 2 - width / 2;
	y = -1 * height;
	speed = 6;
	fire_span = 40;
	hp = 100;
	count = 0;
	start = false;
	alive = false;	// 生存フラグを設定
}

void cBoss::Draw()
{
	DrawGraph(x,y,i_body,true);
}
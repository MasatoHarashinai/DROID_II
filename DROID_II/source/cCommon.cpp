#include "hCommon.h"
#define ENEMY_SPAN 10
#define DROP_LITTLE 60

cCommon::cCommon()	// コンストラクタ
{
	i_body = LoadGraph("image/Common1.png"); // メモリに自機の画像を書き込む
	i_body2 = LoadGraph("image/Boss.png");
	s_dead = LoadSoundMem("sound/CommonDead.wav");	// メモリに倒された時の音を書き込む
	ChangeVolumeSoundMem( 255 * 40 / 100, s_dead ) ;	// 倒された時の音を50%の音量に設定
	GetGraphSize(i_body,&width,&height);	// 画像のサイズを取得して保存する

	speed = 6;
	hp = 1;
	drop_exp = DROP_LITTLE;
	start_x = x = 0;
	start_y = y = -1 * height;
	spawn_span = ENEMY_SPAN;
	angle = 0;

	// 速度を初期化
	alive = false;	// 生存フラグを設定
}

int cCommon::GetX(){ return x; }  // X座標を取得
int cCommon::GetY(){ return y; } // Y座標を取得
int cCommon::GetWidth(){ return width; }	// 画像の幅を取得する
int cCommon::GetHeight(){ return height; }	// 画像の高さを取得する
int cCommon::GetHP(){ return hp; }
int cCommon::GetDropExp(){ return drop_exp; }
int cCommon::GetPattern(){ return pattern; }
int cCommon::GetSpawnSpan(){ return spawn_span; }
bool cCommon::GetAlive(){ return alive; }	// 生存フラグを取得

void cCommon::SetSpeed(int _speed){ speed = _speed; }	// 速度を設定する
void cCommon::SetX(int _x){ x = _x; } // X座標を設定する
void cCommon::SetY(int _y){ y = _y; } // Y座標を設定する
void cCommon::Damage(int damage){ hp -= damage; }
void cCommon::SetPattern(int pattern){ this->pattern = pattern; }
void cCommon::SetAlive(bool alive){ this->alive = alive; }
void cCommon::SetSpawnSpan(int spawn_span){ this->spawn_span = spawn_span; }
void cCommon::Draw() 
{ 
	DrawRotaGraph(x + width / 2,y + height / 2,1,angle,i_body,true,false); //画像を回転させながら描画する
}
void cCommon::Init()
{
	switch(pattern)
	{
	case 0: // 左から斜めに降りる→途中で真下に降りる
		speed = 6;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = 0;
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN;
		break;
	case 1: // 右から斜めに降りる→途中で真下に降りる
		speed = 6;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = GameScreenWidth;
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN;
		break;
	case 2: // 真下に降りる→右に少し移動→上に戻る
		speed = 10;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = GameScreenWidth / 5;
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN;
		break;
	case 3:// 真下に降りる→左に少し移動→上に戻る
		speed = 10;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = GameScreenWidth - GameScreenWidth / 5;
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN;
		break;
	case 4: // 画面左半分にランダムで高速降下してくる
		speed = 13;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = GetRand((GameScreenWidth / 2) - width);
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN - 8;
		break;
	case 5: // 画面右半分にランダムで高速降下してくる
		speed = 13;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = (GameScreenWidth / 2) + GetRand((GameScreenWidth / 2) - width);
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN - 8;
		break;
	case 999:
		i_body = i_body2;
		GetGraphSize(i_body2,&width,&height);
		hp = 50;
		drop_exp = DROP_LITTLE * 10;
		speed = 1;
		start_x = x = GameScreenWidth / 2 - width / 2;
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN * 3;
		break;

	}
	count = 0;
	inited = true;
}

void cCommon::Spawn()
{ 
	alive = true; // ザコキャラを生成する
	inited = false; 
} 

void cCommon::Dead() // ザコキャラを死亡させる
{ 
	if(x + width > 0 && GameScreenWidth > x + width && y + height > 0 && GameScreenHeight > y + height)
	{
		if(CheckSoundMem(s_dead)) StopSoundMem(s_dead);	// 別のCommonが動いているかもしれないので音が鳴っていたら止める
		PlaySoundMem(s_dead, DX_PLAYTYPE_BACK);		// 撃破された音を鳴らす
	}

	alive = false;
}

void cCommon::Move()
{
	switch(pattern)
	{
	case 0: // 右斜めに移動し、画面1/3移動したら真下へ移動し始める
		if(x - start_x < (GameScreenWidth / 3)){
			x += speed;
			y += speed;
			angle = -45;
		}else{
			y += speed;
			angle = 0;
		}
		break;
	case 1: // 左斜めに移動し、画面1/3移動したら真下へ移動し始める
		if(start_x - x < (GameScreenWidth / 3)){
			x -= speed;
			y += speed;
			angle = 45;
		}else{
			y += speed;
			angle = 0;
		}
		break;
	case 2:
		switch(count)
		{
		case 0:
			if(y - start_y < GameScreenHeight - (GameScreenHeight * 3 / 5))
			{
				y += speed;
				angle = 0;
			}
			else
			{
				count = 1;
			}
			break;
		case 1:
			if(x < GameScreenWidth / 3)
			{
				x += speed;
				angle = -90;
			}
			else
			{
				count = 2;
			}
			break;
		case 2:
			y -= speed;
			angle = 180;
			break;
		}
		break;
	case 3:
		switch(count)
		{
		case 0:
			if(y - start_y < GameScreenHeight - (GameScreenHeight * 3 / 5))
			{
				y += speed;
				angle = 0;
			}
			else
			{
				count = 1;
			}
			break;
		case 1:
			if(x > GameScreenWidth * 2 / 3)
			{
				x -= speed;
				angle = 90;
			}
			else
			{
				count = 2;
			}
			break;
		case 2:
			y -= speed;
			angle = 180;
			break;
		}
		break;
	case 4:
		y += speed;
		angle = 0;
		break;
	case 5:
		y += speed;
		angle = 0;
		break;
	case 999:
		switch(count)
		{
		case 0:
			if(y < height*2)
			{
				y += speed;
				angle = 0;
			}
			else
			{
				count++;
			}
			break;
		case 1:
			if(x > GameScreenWidth / 5)
			{
				x -= speed;
			}else{
				count = 2;
			}
			break;
		case 2:
			if(x < GameScreenWidth * 4 / 5)
			{
				x += speed;
			}else{
				count = 1;
			}
			break;
		}
	}
}

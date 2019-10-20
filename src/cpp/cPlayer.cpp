#include "hPlayer.h"
#include "DxLib.h"
#include "hDatum.h"

#define LEVEL_NEXT_INC 300 // レベルが上がりにくくなった時の追加増分

cPlayer::cPlayer(int x, int y, int life)
{
	i_body = LoadGraph(RSC_PATH(RSC_IMG_PREFIX, "blueS01b.png"));	// プレイヤーの画像を設定する
	GetGraphSize(i_body, &width, &height);	// プレイヤー画像から幅と高さを取得して保存する
	s_damage = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "PlayerDamage.mp3")); // 
	ChangeVolumeSoundMem( 255 * 45 / 100, s_damage ) ; //
	s_dead = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "PlayerDead.mp3"));	  // 音声ファイルの識別番号を保存
	ChangeVolumeSoundMem( 255 * 45 / 100, s_dead );	  //			&	
	s_danger = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "PlayerDanger.mp3"));//　　　ボリュームの設定
	ChangeVolumeSoundMem( 255 * 65 / 100, s_danger ) ;//
	s_levelup = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "LevelUp.mp3"));	 //
	ChangeVolumeSoundMem( 255 * 35 / 100, s_levelup ) ;

	this->x = x;	// X座標
	this->y = y; // Y座標
	exp = 0;	// 経験値を初期化
	level = 1;	// レベルを初期化する
	this->life = life; // 耐久力を初期化する
	speed = 6;	// 速度を初期化
	rapid = 12;
	alive = true; // 生存フラグをtrueで初期化する
	god = false;	// 無敵モードのフラグを初期化
	need_exp[1] = 0;
	need_exp[2] = 200;	// レベル２の必要経験値を設定
		
}

int cPlayer::GetX(){ return x; } // X座標を取得する
int cPlayer::GetY(){ return y; } // Y座標を取得する
int cPlayer::GetWidth(){ return width; }	// 画像の幅を取得する
int cPlayer::GetHeight(){ return height; } // 画像の高さを取得する
int cPlayer::GetLife(){ return life; }	// 残り耐久力を取得する
int cPlayer::GetExp(){ return exp; } // 経験値を取得する
int cPlayer::GetLevel(){ return level; } // レベルを取得する
int cPlayer::GetSpeed(){ return speed; }	// 速度を取得する
int cPlayer::GetRapid(){ return rapid; }
int cPlayer::GetNeedExp(int level){ return need_exp[level]; } // 次のレベルアップに必要な経験値を取得する
bool cPlayer::GetAlive(){ return alive; }	// 生存フラグを取得する
bool cPlayer::GetGod(){ return god; } // 無敵モードの状態を取得する

void cPlayer::SetX(int _x){ x = _x; } // X座標を設定する
void cPlayer::SetY(int _y){ y = _y; } // Y座標を設定する
void cPlayer::SetExp(int exp){ this->exp = exp; }
void cPlayer::SetSpeed(int _speed){ speed = _speed; }	// 速度を設定する
void cPlayer::SetRapid(){ this->rapid -= 1; }
void cPlayer::SetUpgrades()
{
	upgrades[0] = NONE;
	upgrades[1] = NONE;
	upgrades[2] = RAPID;
	upgrades[3] = BULLET_SPEED;
	upgrades[4] = RAPID;
	upgrades[5] = BARRIAR;
	upgrades[6] = RAPID;
	upgrades[7] = BULLET_SPEED;
	upgrades[8] = RAPID;
	upgrades[9] = RAPID;
	upgrades[10] = BARRIAR;
	upgrades[11] = RAPID;
	upgrades[12] = BULLET_SPEED;
	upgrades[13] = RAPID;
	upgrades[14] = RAPID;
	upgrades[15] = BARRIAR;
}
void cPlayer::Draw(){ DrawGraph(x,y,i_body,1); } // 画像を描画する 
void cPlayer::SetLife(int _life)	// 耐久力を設定する
{ 
	if(!god)
	{
		if(_life < life)	// ダメージを受けた
		{
			if(CheckSoundMem(s_damage)) StopSoundMem(s_damage);	// 前回のダメージ音を停止させる
			PlaySoundMem(s_damage, DX_PLAYTYPE_BACK);	// ダメージ音を鳴らす
			if(life == 2)	PlaySoundMem(s_danger, DX_PLAYTYPE_BACK);	// 耐久度が1まで減ったときは警告音を鳴らす
		}
		else if(_life > life) // 回復した
		{
			// 回復の音 //
		}
			life = _life;
	}

}
E_UPGRADE cPlayer::AddExp(int _exp)
{ 
	exp += _exp;
	if(exp >= need_exp[level+1])
	{
		if(CheckSoundMem(s_levelup)) StopSoundMem(s_levelup);
		PlaySoundMem(s_levelup,DX_PLAYTYPE_BACK);
		level++;
		need_exp[level+1] = need_exp[level] + LEVEL_NEXT_INC;
		exp = 0;
		return upgrades[level];
	}
	return NONE;
}

void cPlayer::ToggleGodMode()	// 無敵モードのOnOffを切り替える
{
	if(god)
	{
		god = false;
	}
	else
	{
		god = true;
	}
}

void cPlayer::Dead()
{ 
	PlaySoundMem(s_dead, DX_PLAYTYPE_BACK);
	alive = false;
}

void cPlayer::MoveX(int speed)
{
	if( (x + speed > 0) && (x + width + speed < GameScreenWidth) ) x += speed;
}
void cPlayer::MoveY(int speed)
{
	if( (y + speed > 0) && (y + height + speed < GameScreenHeight) ) y += speed;
}


#include "hBeam.h"
#include "hDatum.h"
#include "DxLib.h"

cBeam::cBeam(int x, int y)	// 各パラメータを初期化する
{
	i_body = LoadGraph(RSC_PATH(RSC_IMG_PREFIX, "Beam.png"));
	GetGraphSize(i_body, &width, &height);
	s_fire = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "BeamFire.mp3"));
	ChangeVolumeSoundMem( 255 * 45 / 100, s_fire ) ;
	s_hit = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "BeamHit.mp3"));
	ChangeVolumeSoundMem( 255 * 45 / 100, s_hit ) ;

	this->x = x;
	this->y = y;
	speed = 12;
	active = false;
	inited = true;
}

int cBeam::GetX(){ return x; }	// x座標を返す
int cBeam::GetY(){ return y; }	// y座標を返す
int cBeam::GetWidth(){ return width; }	// 画像の幅を返す
int cBeam::GetHeight(){ return height; }	// 画像の高さを返す
int cBeam::GetSpeed(){ return speed; }
bool cBeam::GetActive(){	return active;	}	// 生存フラグを返す

void cBeam::SetX(int _x){ x = _x; }	// x座標を指定する
void cBeam::SetY(int _y){ y = _y; }	// y座標を指定する
void cBeam::SetSpeed(int speed)
{
	this->speed = speed;
}
void cBeam::Draw() { DrawGraph(x, y, i_body, 1); }
void cBeam::Fire()  // 発射する
{
	if(CheckSoundMem(s_fire)) StopSoundMem(s_fire);
	PlaySoundMem(s_fire, DX_PLAYTYPE_BACK);
	active = true; // 生存フラグをTrueにする
	inited = false;
}	
void cBeam::Delete() 
{
	if(y > 0 && y + height < GameScreenHeight && x > 0 && x + width < GameScreenWidth)	// 画面の中で消された場合(敵と衝突したとき)のみ音を鳴らす
	{
		if(CheckSoundMem(s_hit))StopSoundMem(s_hit);
		PlaySoundMem(s_hit, DX_PLAYTYPE_BACK);
	}
	active = false; // 生存フラグをFalseにする
}	

void cBeam::Init(int _x, int _y)
{
	x = _x;
	y = _y;
	active = false;
	inited = true;
}

void cBeam::Move()
{
    if(active)
    {
        y -= speed;    
    }
}
#include "hBarriar.h"
#include "DxLib.h"

#define PI 3.1415926535897932384626433832795f // ‰~Žü—¦

cBarriar::cBarriar(cPlayer p)
{
	i_body[0] = LoadGraph(RSC_PATH(RSC_IMG_PREFIX, "Barriar1.png"));
	i_body[1] = LoadGraph(RSC_PATH(RSC_IMG_PREFIX, "Barriar2.png"));
	i_body[2] = LoadGraph(RSC_PATH(RSC_IMG_PREFIX, "Barriar3.png"));
	s_create = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "BarriarCreate.mp3"));
	ChangeVolumeSoundMem( 255 * 45 / 100, s_create ) ;
	GetGraphSize(i_body[1], &width, &height);
	x = p.GetX() + p.GetWidth() / 2 - width / 2;
	y = p.GetY() + p.GetHeight() / 2 - height / 2;
	angle = 0;
	hp = 0;
	alive = false;
}

int cBarriar::GetX(){ return x; }
int cBarriar::GetY(){ return y; }
int cBarriar::GetWidth(){ return width; }
int cBarriar::GetHeight(){ return height; }
int cBarriar::GetHP(){ return hp; }
bool cBarriar::GetAlive(){ return alive; }

void cBarriar::UpdateLocation(cPlayer p)
{
	x = p.GetX() + p.GetWidth() / 2 - width / 2;
	y = p.GetY() + p.GetHeight() / 2 - height / 2;
}

void cBarriar::Damage(int damage){ hp -= damage; }
void cBarriar::Draw()
{
	if(alive)
	{
		if(angle == 360) angle=0;	// 360“x‰ñ“]‚µ‚½‚ç0“x‚É–ß‚·
		DrawRotaGraph(x + width / 2,y + height / 2,1,angle,i_body[hp - 1],true,false); //‰æ‘œ‚ð‰ñ“]‚³‚¹‚È‚ª‚ç•`‰æ‚·‚é
		angle++; // ŽŸ‰ñ‚Ì•`‰æ‚É”õ‚¦‚ÄŠp“x‚ð1“x‚¸‚ç‚·
	}
}
void cBarriar::Create()
{ 
	hp++;
	if(!alive) alive = true; 
	if(CheckSoundMem(s_create)) StopSoundMem(s_create);
	PlaySoundMem(s_create,DX_PLAYTYPE_BACK);
}
void cBarriar::Delete(){ alive = false; }
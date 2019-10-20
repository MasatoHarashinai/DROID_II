#include "hBeam.h"
#include "hDatum.h"
#include "DxLib.h"

cBeam::cBeam(int x, int y)	// �e�p�����[�^������������
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

int cBeam::GetX(){ return x; }	// x���W��Ԃ�
int cBeam::GetY(){ return y; }	// y���W��Ԃ�
int cBeam::GetWidth(){ return width; }	// �摜�̕���Ԃ�
int cBeam::GetHeight(){ return height; }	// �摜�̍�����Ԃ�
int cBeam::GetSpeed(){ return speed; }
bool cBeam::GetActive(){	return active;	}	// �����t���O��Ԃ�

void cBeam::SetX(int _x){ x = _x; }	// x���W���w�肷��
void cBeam::SetY(int _y){ y = _y; }	// y���W���w�肷��
void cBeam::SetSpeed(int speed)
{
	this->speed = speed;
}
void cBeam::Draw() { DrawGraph(x, y, i_body, 1); }
void cBeam::Fire()  // ���˂���
{
	if(CheckSoundMem(s_fire)) StopSoundMem(s_fire);
	PlaySoundMem(s_fire, DX_PLAYTYPE_BACK);
	active = true; // �����t���O��True�ɂ���
	inited = false;
}	
void cBeam::Delete() 
{
	if(y > 0 && y + height < GameScreenHeight && x > 0 && x + width < GameScreenWidth)	// ��ʂ̒��ŏ����ꂽ�ꍇ(�G�ƏՓ˂����Ƃ�)�̂݉���炷
	{
		if(CheckSoundMem(s_hit))StopSoundMem(s_hit);
		PlaySoundMem(s_hit, DX_PLAYTYPE_BACK);
	}
	active = false; // �����t���O��False�ɂ���
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
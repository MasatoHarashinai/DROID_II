#include "hCommon.h"
#define ENEMY_SPAN 10
#define DROP_LITTLE 60

cCommon::cCommon()	// �R���X�g���N�^
{
	i_body = LoadGraph("image/Common1.png"); // �������Ɏ��@�̉摜����������
	i_body2 = LoadGraph("image/Boss.png");
	s_dead = LoadSoundMem("sound/CommonDead.wav");	// �������ɓ|���ꂽ���̉�����������
	ChangeVolumeSoundMem( 255 * 40 / 100, s_dead ) ;	// �|���ꂽ���̉���50%�̉��ʂɐݒ�
	GetGraphSize(i_body,&width,&height);	// �摜�̃T�C�Y���擾���ĕۑ�����

	speed = 6;
	hp = 1;
	drop_exp = DROP_LITTLE;
	start_x = x = 0;
	start_y = y = -1 * height;
	spawn_span = ENEMY_SPAN;
	angle = 0;

	// ���x��������
	alive = false;	// �����t���O��ݒ�
}

int cCommon::GetX(){ return x; }  // X���W���擾
int cCommon::GetY(){ return y; } // Y���W���擾
int cCommon::GetWidth(){ return width; }	// �摜�̕����擾����
int cCommon::GetHeight(){ return height; }	// �摜�̍������擾����
int cCommon::GetHP(){ return hp; }
int cCommon::GetDropExp(){ return drop_exp; }
int cCommon::GetPattern(){ return pattern; }
int cCommon::GetSpawnSpan(){ return spawn_span; }
bool cCommon::GetAlive(){ return alive; }	// �����t���O���擾

void cCommon::SetSpeed(int _speed){ speed = _speed; }	// ���x��ݒ肷��
void cCommon::SetX(int _x){ x = _x; } // X���W��ݒ肷��
void cCommon::SetY(int _y){ y = _y; } // Y���W��ݒ肷��
void cCommon::Damage(int damage){ hp -= damage; }
void cCommon::SetPattern(int pattern){ this->pattern = pattern; }
void cCommon::SetAlive(bool alive){ this->alive = alive; }
void cCommon::SetSpawnSpan(int spawn_span){ this->spawn_span = spawn_span; }
void cCommon::Draw() 
{ 
	DrawRotaGraph(x + width / 2,y + height / 2,1,angle,i_body,true,false); //�摜����]�����Ȃ���`�悷��
}
void cCommon::Init()
{
	switch(pattern)
	{
	case 0: // ������΂߂ɍ~��遨�r���Ő^���ɍ~���
		speed = 6;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = 0;
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN;
		break;
	case 1: // �E����΂߂ɍ~��遨�r���Ő^���ɍ~���
		speed = 6;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = GameScreenWidth;
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN;
		break;
	case 2: // �^���ɍ~��遨�E�ɏ����ړ�����ɖ߂�
		speed = 10;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = GameScreenWidth / 5;
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN;
		break;
	case 3:// �^���ɍ~��遨���ɏ����ړ�����ɖ߂�
		speed = 10;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = GameScreenWidth - GameScreenWidth / 5;
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN;
		break;
	case 4: // ��ʍ������Ƀ����_���ō����~�����Ă���
		speed = 13;
		hp = 1;
		drop_exp = DROP_LITTLE;
		start_x = x = GetRand((GameScreenWidth / 2) - width);
		start_y = y = -1 * height;
		spawn_span = ENEMY_SPAN - 8;
		break;
	case 5: // ��ʉE�����Ƀ����_���ō����~�����Ă���
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
	alive = true; // �U�R�L�����𐶐�����
	inited = false; 
} 

void cCommon::Dead() // �U�R�L���������S������
{ 
	if(x + width > 0 && GameScreenWidth > x + width && y + height > 0 && GameScreenHeight > y + height)
	{
		if(CheckSoundMem(s_dead)) StopSoundMem(s_dead);	// �ʂ�Common�������Ă��邩������Ȃ��̂ŉ������Ă�����~�߂�
		PlaySoundMem(s_dead, DX_PLAYTYPE_BACK);		// ���j���ꂽ����炷
	}

	alive = false;
}

void cCommon::Move()
{
	switch(pattern)
	{
	case 0: // �E�΂߂Ɉړ����A���1/3�ړ�������^���ֈړ����n�߂�
		if(x - start_x < (GameScreenWidth / 3)){
			x += speed;
			y += speed;
			angle = -45;
		}else{
			y += speed;
			angle = 0;
		}
		break;
	case 1: // ���΂߂Ɉړ����A���1/3�ړ�������^���ֈړ����n�߂�
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

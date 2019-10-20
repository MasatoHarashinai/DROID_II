#include "hPlayer.h"
#include "DxLib.h"
#include "hDatum.h"

#define LEVEL_NEXT_INC 300 // ���x�����オ��ɂ����Ȃ������̒ǉ�����

cPlayer::cPlayer(int x, int y, int life)
{
	i_body = LoadGraph(RSC_PATH(RSC_IMG_PREFIX, "blueS01b.png"));	// �v���C���[�̉摜��ݒ肷��
	GetGraphSize(i_body, &width, &height);	// �v���C���[�摜���畝�ƍ������擾���ĕۑ�����
	s_damage = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "PlayerDamage.mp3")); // 
	ChangeVolumeSoundMem( 255 * 45 / 100, s_damage ) ; //
	s_dead = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "PlayerDead.mp3"));	  // �����t�@�C���̎��ʔԍ���ۑ�
	ChangeVolumeSoundMem( 255 * 45 / 100, s_dead );	  //			&	
	s_danger = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "PlayerDanger.mp3"));//�@�@�@�{�����[���̐ݒ�
	ChangeVolumeSoundMem( 255 * 65 / 100, s_danger ) ;//
	s_levelup = LoadSoundMem(RSC_PATH(RSC_SND_PREFIX, "LevelUp.mp3"));	 //
	ChangeVolumeSoundMem( 255 * 35 / 100, s_levelup ) ;

	this->x = x;	// X���W
	this->y = y; // Y���W
	exp = 0;	// �o���l��������
	level = 1;	// ���x��������������
	this->life = life; // �ϋv�͂�����������
	speed = 6;	// ���x��������
	rapid = 12;
	alive = true; // �����t���O��true�ŏ���������
	god = false;	// ���G���[�h�̃t���O��������
	need_exp[1] = 0;
	need_exp[2] = 200;	// ���x���Q�̕K�v�o���l��ݒ�
		
}

int cPlayer::GetX(){ return x; } // X���W���擾����
int cPlayer::GetY(){ return y; } // Y���W���擾����
int cPlayer::GetWidth(){ return width; }	// �摜�̕����擾����
int cPlayer::GetHeight(){ return height; } // �摜�̍������擾����
int cPlayer::GetLife(){ return life; }	// �c��ϋv�͂��擾����
int cPlayer::GetExp(){ return exp; } // �o���l���擾����
int cPlayer::GetLevel(){ return level; } // ���x�����擾����
int cPlayer::GetSpeed(){ return speed; }	// ���x���擾����
int cPlayer::GetRapid(){ return rapid; }
int cPlayer::GetNeedExp(int level){ return need_exp[level]; } // ���̃��x���A�b�v�ɕK�v�Ȍo���l���擾����
bool cPlayer::GetAlive(){ return alive; }	// �����t���O���擾����
bool cPlayer::GetGod(){ return god; } // ���G���[�h�̏�Ԃ��擾����

void cPlayer::SetX(int _x){ x = _x; } // X���W��ݒ肷��
void cPlayer::SetY(int _y){ y = _y; } // Y���W��ݒ肷��
void cPlayer::SetExp(int exp){ this->exp = exp; }
void cPlayer::SetSpeed(int _speed){ speed = _speed; }	// ���x��ݒ肷��
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
void cPlayer::Draw(){ DrawGraph(x,y,i_body,1); } // �摜��`�悷�� 
void cPlayer::SetLife(int _life)	// �ϋv�͂�ݒ肷��
{ 
	if(!god)
	{
		if(_life < life)	// �_���[�W���󂯂�
		{
			if(CheckSoundMem(s_damage)) StopSoundMem(s_damage);	// �O��̃_���[�W�����~������
			PlaySoundMem(s_damage, DX_PLAYTYPE_BACK);	// �_���[�W����炷
			if(life == 2)	PlaySoundMem(s_danger, DX_PLAYTYPE_BACK);	// �ϋv�x��1�܂Ō������Ƃ��͌x������炷
		}
		else if(_life > life) // �񕜂���
		{
			// �񕜂̉� //
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

void cPlayer::ToggleGodMode()	// ���G���[�h��OnOff��؂�ւ���
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


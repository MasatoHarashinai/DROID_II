#pragma once
#include "hDatum.h"

class cPlayer
{	
private : 
	int x;	// X���W
	int y;	// Y���W
	int width;	// �摜�̕�
	int height;	// �摜�̍���
	int life;	// ���@�̑ϋv�x
	int exp;	// �o���l
	int level; // ���x��
	int speed;
	int rapid; // �A�˗�
	char *upgrades[MAX_LEVEL]; // �������e(�Y�����͒m�肽�����x��)
	int need_exp[101]; // ���x���A�b�v�ɕK�v�Ȍo���l��ۑ����邽�߂̔z��(�Y�����͌o���l���m�肽�����x��������);
	bool god; // ���G���[�h�̃t���O
	bool alive;	// ���@�̐����t���O

public :
	int i_body;	//�摜�̃n���h��
	int s_damage; // �_���[�W���̃n���h��	
	int s_dead;	// ���Ă��ꂽ���̃n���h��
	int s_danger; // �x�����̃n���h��
	int s_levelup;

	cPlayer(int _x, int _y, int _life);	// �R���X�g���N�^

	int GetX(); // �v���C���[��X���W���擾����
	int GetY();	// �v���C���[��Y���W���擾����
	int GetWidth();	// �摜�̕����擾����
	int GetHeight(); //�@�摜�̍������擾����
	int GetLife();	// �v���C���[�̑ϋv�x���擾����
	int GetExp();	// �v���C���[�̌o���l���擾����
	int GetLevel();	// �v���C���[�̃��x�����擾����
	int GetSpeed(); // �v���C���[�̃X�s�[�h���擾����
	int GetRapid(); // �v���C���[�̘A�˗͂��擾����
	int GetNeedExp(int level); // ���̃��x���A�b�v�ɕK�v�Ȍo���l���擾����
	bool GetAlive(); // �t���O���擾����
	bool GetGod(); // ���G���[�h�̏�Ԃ��擾����

	void SetX(int _x);	// �v���C���[��X���W���w�肷��
	void SetY(int _y);	// �v���C���[��Y���W���w�肷��
	void SetSpeed(int _speed);	// �v���C���[�̑��x��ݒ�
	void SetLife(int _life); // �v���C���[�̃��C�t���w�肷��
	void SetExp(int exp);
	void SetRapid();
	void SetUpgrades();
	char *AddExp(int _Exp); // �v���C���[�̌o���l���w�蕪��������������
	void Draw();
	void ToggleGodMode(); // ���G���[�h��OnOff��؂�ւ���

	void Dead(); // ���S������
	void MoveX(int speed);
	void MoveY(int speed);
};



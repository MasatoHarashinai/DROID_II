#pragma once

#include "hPlayer.h"
#define MAX_HP 3

class cBarriar
{
private:
	int i_body[MAX_HP];	// �摜�̎��ʔԍ���ۑ�����ϐ�
	int s_create; // 
	int hp;
	int x;	// �w���W
	int y;	// Y���W
	int width;	 // �摜�̕�
	int height;	// �摜�̍���
	double angle; // �o���A�̉�]�p�x
	bool alive;	// �o���A���W�J����Ă��邩
public:
	cBarriar(cPlayer p);	// �R���X�g���N�^
	int GetX();	// X���W���擾����
	int GetY();	// Y���W���擾����
	int GetWidth();	// �摜�̕����擾����
	int GetHeight();	// �摜�̍������擾����
	int GetHP();
	bool GetAlive();	// �o���A���W�J����Ă��邩��_���^�Ŏ擾����

	void UpdateLocation(cPlayer p);	// �o���A�̍��W���X�V����
	void Damage(int damage);
	void Draw();	// �o���A��`�悷��
	void Create();	// �o���A��W�J������
	void Delete();	// �o���A��j�󂷂�
};
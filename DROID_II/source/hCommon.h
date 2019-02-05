#pragma once

#include "DxLib.h"
#include "hDatum.h"

class cCommon
{
private :

protected:
	int x;	// X���W
	int y;	// Y���W
	int start_x; // �X�^�[�g�n�_�̂����W
	int start_y; // �X�^�[�g�n�_�̂����W
	int width;	// �摜�̕�
	int height;	// �摜�̍��� 
	int hp;
	int drop_exp;
	int speed;	// �ړ����x
	int pattern; // �����̎��
	int spawn_span; // �o�����鎞�ԊԊu���~���b�P�ʂŕۑ�����
	int count; // �ړ�����p�J�E���^
	double angle; // �G�L�����̌���
	bool alive;	// �G����ʏ�ɑ��݂��Ă��邩�̃t���O

public :
	int i_body;	// �摜�̃n���h��
	int i_body2;
	int s_dead; // �G���|���ꂽ���̃n���h��
	bool inited; // ���������Ă��邩�ǂ���

	cCommon();	// �R���X�g���N�^

	int GetImage(); // �摜�̃n���h�����擾����
	int GetX();	// X���W���擾����
	int GetY();	// Y���W���擾����
	int GetWidth();	// �G�摜�̕����擾����
	int GetHeight();	// �G�摜�̍������擾����
	int GetHP();
	int GetDropExp();
	int GetPattern();
	int GetSpawnSpan(); // 
	bool GetAlive();	// �t���O���擾����
	
	void SetImage(int); // �摜�̃n���h����ݒ�
	void SetX(int);	// X���W��ݒ�
	void SetY(int);	// Y���W��ݒ�
	void SetSpeed(int); // ���x��ݒ�
	void Damage(int damage);
	void SetPattern(int); // �ړ��p�^�[����ݒ�
	void SetAlive(bool);
	void SetSpawnSpan(int spawn_span);
	void virtual Draw(); // �U�R�L������`��
	void virtual Init();	// ����������

	void Spawn();
	void virtual Dead();
	void virtual Move(); // �ړ�������
};
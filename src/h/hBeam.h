#pragma once

class cBeam
{
private:
protected:
	int x;	// X���W
	int y;	// Y���W
	int speed; // ���x
	bool active;	// �����t���O
	int width;	// �摜�̕�
	int height;	// �摜�̍���

public :
	int i_body;	// �r�[���̉摜
	int s_fire;	// ���ˉ�
	int s_hit;	// �q�b�g��
	bool inited; // ���������Ă��邩�ǂ���

	cBeam(int _x, int _y);	// �R���X�g���N�^
	
	int GetImage(); // �摜�̃n���h�����擾����
	int GetX();	// X���W���擾����
	int GetY();	// Y���W���擾����
	int GetSpeed(); // ���x���擾����
	int GetWidth(); // �摜�̕����擾����
	int GetHeight(); // �摜�̍������擾����
	bool GetActive();	// �����t���O���擾����

	void SetX(int x);	// X���W���w�肷��
	void SetY(int y);	// Y���W���w�肷��
	void SetSpeed(int speed); // ���x��ݒ肷��
	void virtual Draw();	// �`�悷��
	void virtual Fire();	// �r�[���𔭎˂���(�t���O��True�ɐ؂�ւ���)
	void Delete();	// ���˂����r�[�����폜����(�t���O��False�ɐ؂�ւ���)
	void virtual Init(int x, int y);
	void virtual Move();
};
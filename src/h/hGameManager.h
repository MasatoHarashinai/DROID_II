#pragma once

#include "DxLib.h"
#include "hPlayer.h"
#include "hCommon.h"
#include "hBoss.h"
#include "hBeam.h"
#include "hEnemyWeapon.h"
#include "hBarriar.h"
#include "hTimeManager.h"
#include "hDatum.h"

#define PATTERN_MAX 30 // �G�̍s���p�^�[��

class cGameManager
{

private:
	int now; // �Q�[���J�n���牽�t���[���o�߂�����
	int scene; // �Q�[���V�[���萔
	int pattern_group1; // �G�L�����p�^�[���̒萔
	int pattern_group2; // �G�L�����p�^�[���̒萔
	int selected; // �^�C�g����ʂ̑I�����ꂽ����(0:�I�𖳂�,1:�X�^�[�g)
	int select;
	int boss_wait;
	int bgm_vol;
	int count; // �ėp�J�E���^
	int count2;
	bool frag; // �ėp�t���O
	bool frag2;
	int fade_count;
	int pattern_lengths[PATTERN_MAX]; // �G�̃p�^�[�����ǂ̂��炢������(�b/60)
	int spawn_group_count;
	int debug_index; // �f�o�b�O��ʗp�̃C���f�b�N�X(0:Off 1:�v���C���[ 2:�G�L���� 3:�r�[��)
	bool GameFrag; // �Q�[���̌p���t���O
	bool DebugMode;// �f�o�b�O���[�h��on off
	bool active_group1;
	bool active_group2;
	bool warning_frag;
	bool boss_frag;
	
	// �摜���ʕϐ�
	int i_TitleLabel;
	int i_StartLabel;
	int i_Warning;
	int i_SelectStartLabel;
	int i_ExitLabel;
	int i_SelectExitLabel;
	int i_sidebar;
	int i_underbar;
	int i_HPLabel1;
	int i_HPLabel2;
	int i_HPLabel3;
	int i_LevelLavel;
	int i_star;
	int i_numbers[10];
	int i_background;
	int i_background_title;

	// �������ʕϐ�
	int s_bgm; // BGM
	int s_boss_bgm; // �{�X��
	int s_warning;
	int s_title_bgm; // �^�C�g����BGM(�Q�[���J�n���ɂ����Đ����邽��Public��)
	int s_decide; // ���j���[���艹
	int s_move_cursor; // �J�[�\���ړ���

public:
	// �C���X�^���X
	cPlayer *p;	// �v���C���[
	cBeam *beam[BEAM_NUM];	// �r�[��
	cEnemyWeapon *enemy_weapon_beam[BEAM_NUM];
	cEnemyWeapon *enemy_weapon_laser[2];
	cCommon *common1[COMMON_NUM];	// �G���L�����O���[�v�P
	cCommon *common2[COMMON_NUM]; // �G���L�����O���[�v�Q
	cBoss *boss;
	cBarriar *barriar;	// �o���A
	cTimeManager *time;

	// �R���X�g���N�^
	cGameManager();
	
	void SetScene(int);
	void SetEnemy(int pattern_group);
	void SetGameFrag(bool GameFrag);
	void SetPatternLengths();

	bool GetGameFrag();
	int GetScene();
	int GetSelected();
	
	void Init(); // �Q�[���̏���������
	void TitleProcess(); // �^�C�g����ʂ̏���
	void GameProcess(); // �P�t���[���P�ʂ̃Q�[���̏���
	void StartProcess();
	void GameOver();
	void ToggleFunction();

	void close(); // �Q�[���I��
	bool checkHit(int x1, int y1, int w1 , int h1, int x2, int y2, int w2, int h2, int margin1, int margin2); // �����蔻��𒲂ׂ�
	void showDebugScreen();
	void Draw();
	int GetPlace(int value); // ������Ԃ��֐�
};
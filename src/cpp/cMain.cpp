#include "DxLib.h"
#include "hGameManager.h"

// �萔
#define COMMON_MAX_SPAWN_TIME 30 // �U�R�L�������o��������Ԋu�̍ő�l
#define KEY_WAIT_TIME 110 // �L�[���͂̑҂�����

//// �v���g�^�C�v�錾 //
bool setScreen();

// ���C���֐�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	// ��ʂ̐ݒ�ADX���C�u�����̏������̂����ꂩ�Ŏ��s������A�v�����I������ //
	if(!setScreen() || DxLib_Init() || SetDrawScreen(DX_SCREEN_BACK) ){
		return -1;
	}

	cGameManager *game = new cGameManager();
	game->Init();
	

	while(game->GetGameFrag() && !ProcessMessage())
	{
		switch(game->GetScene()){
		case 0:	// �^�C�g��
			game->TitleProcess();
			switch (game->GetSelected()) {
			case 1:
				game->SetScene(1);
				break;
			case 2:
				game->close();
				break;
			default:
				break;
			}
			break;
		case 1: // �Q�[�����
			game->GameProcess();
			break;
		}
		
	}
	

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}

bool setScreen(){

	// �E�B���h�E���[�h�ł̋N���A��ʂ̑傫���ƃJ���[�r�b�g�̐ݒ�𐬌�������true��Ԃ� //
	if( (ChangeWindowMode(true) == DX_CHANGESCREEN_OK) & 
		(SetGraphMode(1280,960,32) == DX_CHANGESCREEN_OK) &
		(SetWindowSizeExtendRate(0.8) == DX_CHANGESCREEN_OK)){
		return true;
	}

	return false;
}


#include "DxLib.h"
#include "hGameManager.h"

// �萔
#define COMMON_MAX_SPAWN_TIME 30 // �U�R�L�������o��������Ԋu�̍ő�l
#define KEY_WAIT_TIME 110 // �L�[���͂̑҂�����

//// �v���g�^�C�v�錾 //
bool setScreen();
//bool checkHit(int x1, int y1, int w1 , int h1, int x2, int y2, int w2, int h2, int margin);	// �摜���m�̏Փ˂𒲂ׂ�֐�(margin : ������ǂ̂��炢�キ���邩)
//void showDebugScreen(cPlayer p, cCommon c[], cBeam b[], int SpwnTime, int LastSpawn);

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

//void showDebugScreen(cPlayer p, cCommon c[], cBeam b[], int SpawnTime, int LastSpawn)
//{
//	// ���[�J���ϐ�
//	int red = GetColor(255,0,0);
//	int green = GetColor(0,255,0);
//	int blue = GetColor(0,0,255);
//	int sky_blue = GetColor(80,80,255);
//	char bState = 'F';
//	char cState_alive = 'F';
//	char cState_god = 'F';
//	const TCHAR *debug_common = "cCommon[%d] -> FRAG:%c X:%d   Y:%d";
//	const TCHAR *debug_beam = "cBeam[%d] -> FRAG:%c";
//
//	// �v���C���[�̃X�e�[�^�X
//	DrawFormatString(10,10,green,"Player -> X:%d",p.getX());
//	DrawFormatString(10,30,green,"Player -> Y:%d",p.getY());
//	DrawFormatString(10,50,green,"Player -> Life:%d",p.getLife());
//	DrawFormatString(10,70,green,"Player -> Exp:%d (NextLevel:%dexp)", p.getExp(),p.getNeedExp());
//	DrawFormatString(10,90,green,"Player -> Level:%d", p.getLevel());
//	
//	if(p.getGod())
//	{
//		cState_god = 'T';
//	}
//	else
//	{
//		cState_god = 'F';
//	}
//	DrawFormatString(10,110,green,"Player -> GodMode:%c", cState_god);
//		
//	// �r�[���̃X�e�[�^�X
//	for(int i = 0; i < BEAM_NUM ; i++)
//	{
//		if(b[i].getAlive())
//		{
//			bState = 'T';
//		}
//		else
//		{
//			bState = 'F';
//		}
//
//		DrawFormatString(10,130 + (20 * i),sky_blue, debug_beam ,i + 1 ,bState);
//	}
//
//	//// �U�R�L�����̃X�e�[�^�X
//	//for(int i = 0 ; i < COMMON_NUM; i++)
//	//{
//	//	if(c[i].getAlive())
//	//	{
//	//		cState = 'T';
//	//	}
//	//	else
//	//	{
//	//		cState = 'F';
//	//	}
//
//	//	if(i < 20)
//	//	{
//	//		DrawFormatString(10,70 + (20 * BEAM_NUM) + (20 * i), red, debug_common,
//	//						 i + 1 ,cState, c[i].getX(), c[i].getY());
//	//	}
//	//	else
//	//	{
//	//		DrawFormatString(wWIDTH - GetDrawStringWidth(debug_common, strlen(debug_common)), 10 + (20 * (i - 20)), red, debug_common,
//	//						 i + 1, cState, c[i].getX(), c[i].getY());
//	//	}
//
//	//}
//
//	//// �U�R�L�����̎��̏o������
//	//int RemainTime = (SpawnTime - (GetNowCount() - LastSpawn)) / 1000 + 1;
//	//DrawFormatString(10, 70 + (20 * BEAM_NUM) + (20 * COMMON_NUM), red,"NextSpawn -> %dsec",RemainTime);
//
//}
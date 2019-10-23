#include "DxLib.h"
#include "hGameManager.h"

// 定数
#define COMMON_MAX_SPAWN_TIME 30 // ザコキャラを出現させる間隔の最大値
#define KEY_WAIT_TIME 110 // キー入力の待ち時間

//// プロトタイプ宣言 //
bool setScreen();

// メイン関数
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	// 画面の設定、DXライブラリの初期化のいずれかで失敗したらアプリを終了する //
	if(!setScreen() || DxLib_Init() || SetDrawScreen(DX_SCREEN_BACK) ){
		return -1;
	}

	cGameManager *game = new cGameManager();
	game->Init();
	

	while(game->GetGameFrag() && !ProcessMessage())
	{
		switch(game->GetScene()){
		case 0:	// タイトル
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
		case 1: // ゲーム画面
			game->GameProcess();
			break;
		}
		
	}
	

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}

bool setScreen(){

	// ウィンドウモードでの起動、画面の大きさとカラービットの設定を成功したらtrueを返す //
	if( (ChangeWindowMode(true) == DX_CHANGESCREEN_OK) & 
		(SetGraphMode(1280,960,32) == DX_CHANGESCREEN_OK) &
		(SetWindowSizeExtendRate(0.8) == DX_CHANGESCREEN_OK)){
		return true;
	}

	return false;
}


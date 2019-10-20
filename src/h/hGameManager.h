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

#define PATTERN_MAX 30 // 敵の行動パターン

class cGameManager
{

private:
	int now; // ゲーム開始から何フレーム経過したか
	int scene; // ゲームシーン定数
	int pattern_group1; // 敵キャラパターンの定数
	int pattern_group2; // 敵キャラパターンの定数
	int selected; // タイトル画面の選択された項目(0:選択無し,1:スタート)
	int select;
	int boss_wait;
	int bgm_vol;
	int count; // 汎用カウンタ
	int count2;
	bool frag; // 汎用フラグ
	bool frag2;
	int fade_count;
	int pattern_lengths[PATTERN_MAX]; // 敵のパターンがどのくらい続くか(秒/60)
	int spawn_group_count;
	int debug_index; // デバッグ画面用のインデックス(0:Off 1:プレイヤー 2:敵キャラ 3:ビーム)
	bool GameFrag; // ゲームの継続フラグ
	bool DebugMode;// デバッグモードのon off
	bool active_group1;
	bool active_group2;
	bool warning_frag;
	bool boss_frag;
	
	// 画像識別変数
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

	// 音声識別変数
	int s_bgm; // BGM
	int s_boss_bgm; // ボス戦
	int s_warning;
	int s_title_bgm; // タイトルのBGM(ゲーム開始時にだけ再生するためPublicに)
	int s_decide; // メニュー決定音
	int s_move_cursor; // カーソル移動音

public:
	// インスタンス
	cPlayer *p;	// プレイヤー
	cBeam *beam[BEAM_NUM];	// ビーム
	cEnemyWeapon *enemy_weapon_beam[BEAM_NUM];
	cEnemyWeapon *enemy_weapon_laser[2];
	cCommon *common1[COMMON_NUM];	// 雑魚キャラグループ１
	cCommon *common2[COMMON_NUM]; // 雑魚キャラグループ２
	cBoss *boss;
	cBarriar *barriar;	// バリア
	cTimeManager *time;

	// コンストラクタ
	cGameManager();
	
	void SetScene(int);
	void SetEnemy(int pattern_group);
	void SetGameFrag(bool GameFrag);
	void SetPatternLengths();

	bool GetGameFrag();
	int GetScene();
	int GetSelected();
	
	void Init(); // ゲームの初期化処理
	void TitleProcess(); // タイトル画面の処理
	void GameProcess(); // １フレーム単位のゲームの処理
	void StartProcess();
	void GameOver();
	void ToggleFunction();

	void close(); // ゲーム終了
	bool checkHit(int x1, int y1, int w1 , int h1, int x2, int y2, int w2, int h2, int margin1, int margin2); // 当たり判定を調べる
	void showDebugScreen();
	void Draw();
	int GetPlace(int value); // 桁数を返す関数
};
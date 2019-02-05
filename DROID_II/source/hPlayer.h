#pragma once
#include "hDatum.h"

class cPlayer
{	
private : 
	int x;	// X座標
	int y;	// Y座標
	int width;	// 画像の幅
	int height;	// 画像の高さ
	int life;	// 自機の耐久度
	int exp;	// 経験値
	int level; // レベル
	int speed;
	int rapid; // 連射力
	char *upgrades[MAX_LEVEL]; // 強化内容(添え字は知りたいレベル)
	int need_exp[101]; // レベルアップに必要な経験値を保存するための配列(添え字は経験値が知りたいレベルを入れる);
	bool god; // 無敵モードのフラグ
	bool alive;	// 自機の生存フラグ

public :
	int i_body;	//画像のハンドル
	int s_damage; // ダメージ音のハンドル	
	int s_dead;	// 撃墜された音のハンドル
	int s_danger; // 警告音のハンドル
	int s_levelup;

	cPlayer(int _x, int _y, int _life);	// コンストラクタ

	int GetX(); // プレイヤーのX座標を取得する
	int GetY();	// プレイヤーのY座標を取得する
	int GetWidth();	// 画像の幅を取得する
	int GetHeight(); //　画像の高さを取得する
	int GetLife();	// プレイヤーの耐久度を取得する
	int GetExp();	// プレイヤーの経験値を取得する
	int GetLevel();	// プレイヤーのレベルを取得する
	int GetSpeed(); // プレイヤーのスピードを取得する
	int GetRapid(); // プレイヤーの連射力を取得する
	int GetNeedExp(int level); // 次のレベルアップに必要な経験値を取得する
	bool GetAlive(); // フラグを取得する
	bool GetGod(); // 無敵モードの状態を取得する

	void SetX(int _x);	// プレイヤーのX座標を指定する
	void SetY(int _y);	// プレイヤーのY座標を指定する
	void SetSpeed(int _speed);	// プレイヤーの速度を設定
	void SetLife(int _life); // プレイヤーのライフを指定する
	void SetExp(int exp);
	void SetRapid();
	void SetUpgrades();
	char *AddExp(int _Exp); // プレイヤーの経験値を指定分だけ増加させる
	void Draw();
	void ToggleGodMode(); // 無敵モードのOnOffを切り替える

	void Dead(); // 死亡させる
	void MoveX(int speed);
	void MoveY(int speed);
};



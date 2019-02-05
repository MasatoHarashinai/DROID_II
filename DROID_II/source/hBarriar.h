#pragma once

#include "hPlayer.h"
#define MAX_HP 3

class cBarriar
{
private:
	int i_body[MAX_HP];	// 画像の識別番号を保存する変数
	int s_create; // 
	int hp;
	int x;	// Ｘ座標
	int y;	// Y座標
	int width;	 // 画像の幅
	int height;	// 画像の高さ
	double angle; // バリアの回転角度
	bool alive;	// バリアが展開されているか
public:
	cBarriar(cPlayer p);	// コンストラクタ
	int GetX();	// X座標を取得する
	int GetY();	// Y座標を取得する
	int GetWidth();	// 画像の幅を取得する
	int GetHeight();	// 画像の高さを取得する
	int GetHP();
	bool GetAlive();	// バリアが展開されているかを論理型で取得する

	void UpdateLocation(cPlayer p);	// バリアの座標を更新する
	void Damage(int damage);
	void Draw();	// バリアを描画する
	void Create();	// バリアを展開させる
	void Delete();	// バリアを破壊する
};
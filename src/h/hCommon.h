#pragma once

#include "DxLib.h"
#include "hDatum.h"

class cCommon
{
private :

protected:
	int x;	// X座標
	int y;	// Y座標
	int start_x; // スタート地点のｘ座標
	int start_y; // スタート地点のｙ座標
	int width;	// 画像の幅
	int height;	// 画像の高さ 
	int hp;
	int drop_exp;
	int speed;	// 移動速度
	int pattern; // 動きの種類
	int spawn_span; // 出現する時間間隔をミリ秒単位で保存する
	int count; // 移動制御用カウンタ
	double angle; // 敵キャラの向き
	bool alive;	// 敵が画面上に存在しているかのフラグ

public :
	int i_body;	// 画像のハンドル
	int i_body2;
	int s_dead; // 敵が倒された音のハンドル
	bool inited; // 初期化してあるかどうか

	cCommon();	// コンストラクタ

	int GetImage(); // 画像のハンドルを取得する
	int GetX();	// X座標を取得する
	int GetY();	// Y座標を取得する
	int GetWidth();	// 敵画像の幅を取得する
	int GetHeight();	// 敵画像の高さを取得する
	int GetHP();
	int GetDropExp();
	int GetPattern();
	int GetSpawnSpan(); // 
	bool GetAlive();	// フラグを取得する
	
	void SetImage(int); // 画像のハンドルを設定
	void SetX(int);	// X座標を設定
	void SetY(int);	// Y座標を設定
	void SetSpeed(int); // 速度を設定
	void Damage(int damage);
	void SetPattern(int); // 移動パターンを設定
	void SetAlive(bool);
	void SetSpawnSpan(int spawn_span);
	void virtual Draw(); // ザコキャラを描画
	void virtual Init();	// 初期化する

	void Spawn();
	void virtual Dead();
	void virtual Move(); // 移動させる
};
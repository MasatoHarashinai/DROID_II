#pragma once

class cBeam
{
private:
protected:
	int x;	// X座標
	int y;	// Y座標
	int speed; // 速度
	bool active;	// 生存フラグ
	int width;	// 画像の幅
	int height;	// 画像の高さ

public :
	int i_body;	// ビームの画像
	int s_fire;	// 発射音
	int s_hit;	// ヒット音
	bool inited; // 初期化してあるかどうか

	cBeam(int _x, int _y);	// コンストラクタ
	
	int GetImage(); // 画像のハンドルを取得する
	int GetX();	// X座標を取得する
	int GetY();	// Y座標を取得する
	int GetSpeed(); // 速度を取得する
	int GetWidth(); // 画像の幅を取得する
	int GetHeight(); // 画像の高さを取得する
	bool GetActive();	// 生存フラグを取得する

	void SetX(int x);	// X座標を指定する
	void SetY(int y);	// Y座標を指定する
	void SetSpeed(int speed); // 速度を設定する
	void virtual Draw();	// 描画する
	void virtual Fire();	// ビームを発射する(フラグをTrueに切り替える)
	void Delete();	// 発射したビームを削除する(フラグをFalseに切り替える)
	void virtual Init(int x, int y);
	void virtual Move();
};
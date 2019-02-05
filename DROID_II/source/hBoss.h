#pragma once

#include "hCommon.h"

class cBoss : public cCommon
{
private:
	int move_count;
	int fire_span;
	bool start;
public:

	cBoss();

	int GetFireSpan();
	bool GetStart();

	void SetFireSpan(int fire_span);

	void Move();
	void Init();
	void Draw();
};
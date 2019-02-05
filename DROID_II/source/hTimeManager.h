#pragma once

class cTimeManager
{
private : 
	// �Ō�ɏ������s��������
	int last_fire;
	int last_spawn_common1;
	int last_spawn_common2;
	int last_change_enemy_pattern;
	

public:
	cTimeManager();

	// �Ō�ɏ������s�������Ԃ��擾���郁�\�b�h
	int GetLastFire();
	int GetLastSpawnCommon1();
	int GetLastSpawnCommon2();
	int GetLastChangeEnemyPattern();

	void UpdateLastFire(int now);
	void UpdateLastSpawnCommon1(int now);
	void UpdateLastSpawnCommon2(int now);
	void UpdateLastChangeEnemyPattern(int now);
};
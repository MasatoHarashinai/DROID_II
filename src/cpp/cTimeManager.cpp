#include "DxLib.h"
#include "hTimeManager.h"


cTimeManager::cTimeManager()
{
	last_fire = 1;
	last_spawn_common1 = 1;
	last_spawn_common2 = 1;
	last_change_enemy_pattern = 0;
}

int cTimeManager::GetLastFire(){ return last_fire; }
int cTimeManager::GetLastSpawnCommon1(){ return last_spawn_common1; }
int cTimeManager::GetLastSpawnCommon2(){ return last_spawn_common2; }
int cTimeManager::GetLastChangeEnemyPattern(){ return last_change_enemy_pattern; }

void cTimeManager::UpdateLastFire(int now){ last_fire = now; }
void cTimeManager::UpdateLastSpawnCommon1(int now){ last_spawn_common1 = now; }
void cTimeManager::UpdateLastSpawnCommon2(int now){ last_spawn_common2 = now; }
void cTimeManager::UpdateLastChangeEnemyPattern(int now){ last_change_enemy_pattern = now; }
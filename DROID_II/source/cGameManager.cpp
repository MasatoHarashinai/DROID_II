#include "hGameManager.h"
#include "hDatum.h"

#define ADD_SPEED 8
#define MENU_ITEM 2
#define KEY_WAITTIME 8
#define REST_TIME 4 

cGameManager::cGameManager()
{
	i_TitleLabel = LoadGraph("image/Label_TITLE.png");
	i_background = LoadGraph("image/BackGround.png");
	i_background_title = LoadGraph("image/BackGround_Title.png");
	i_Warning = LoadGraph("image/Warning.png");
	i_StartLabel = LoadGraph("image/Label_START.png");
	i_SelectStartLabel = LoadGraph("image/Label_START_SELECT.png");
	i_ExitLabel = LoadGraph("image/Label_EXIT.png");
	i_SelectExitLabel = LoadGraph("image/Label_EXIT_SELECT.png");
	i_sidebar = LoadGraph("image/SideBar.png");
	i_underbar = LoadGraph("image/UnderBar.png");
	i_HPLabel1 = LoadGraph("image/HP1.png");
	i_HPLabel2 = LoadGraph("image/HP2.png");
	i_HPLabel3 = LoadGraph("image/HP3.png");
	i_LevelLavel = LoadGraph("image/Label_Level.png");
	i_star = LoadGraph("image/Star.png");
	i_numbers[0] = LoadGraph("image/n2_0.png");
	i_numbers[1] = LoadGraph("image/n2_1.png");
	i_numbers[2] = LoadGraph("image/n2_2.png");
	i_numbers[3] = LoadGraph("image/n2_3.png");
	i_numbers[4] = LoadGraph("image/n2_4.png");
	i_numbers[5] = LoadGraph("image/n2_5.png");
	i_numbers[6] = LoadGraph("image/n2_6.png");
	i_numbers[7] = LoadGraph("image/n2_7.png");
	i_numbers[8] = LoadGraph("image/n2_8.png");
	i_numbers[9] = LoadGraph("image/n2_9.png");
	s_bgm = LoadSoundMem("sound/BGM4.mp3");
	ChangeVolumeSoundMem( 255 * 30 / 100, s_bgm );
	s_boss_bgm = LoadSoundMem("sound/BossBGM.mp3");
	ChangeVolumeSoundMem( 255 * 35 / 100, s_boss_bgm);
	s_title_bgm = LoadSoundMem("sound/BGM6.mp3");
	ChangeVolumeSoundMem( 255 * 30 / 100, s_title_bgm );
	s_warning = LoadSoundMem("sound/Warning.wav");
	ChangeVolumeSoundMem( 255 * 30 / 100, s_warning );
	s_decide = LoadSoundMem("sound/Decide.mp3");
	ChangeVolumeSoundMem( 255 * 50 / 100, s_decide );
	s_move_cursor = LoadSoundMem("sound/MoveCursor.mp3");
	ChangeVolumeSoundMem( 255 * 50 / 100, s_move_cursor );

	scene = 0; // ゲームシーンをタイトルにセットする
	fade_count = 0;
	selected = 0;
	select = 1;
	count = 0;
	count2 = 0;
	frag = false;
	frag2 = false;
	DebugMode = false;
	boss_frag = false;
	warning_frag = false;
}

bool cGameManager::GetGameFrag(){ return GameFrag; }
int cGameManager::GetScene(){ return scene; }
int cGameManager::GetSelected(){ return selected; }

void cGameManager::SetScene(int scene){ this->scene = scene; }
void cGameManager::SetEnemy(int pattern_group1)
{
	// 敵キャラインスタンス
	for(int i = 0; i < COMMON_NUM ; i++){
		common1[i]->SetPattern(pattern_group1); // パターン1の雑魚敵
	}
}
void cGameManager::SetGameFrag(bool GameFrag){ this->GameFrag = GameFrag; }
void cGameManager::SetPatternLengths()
{
	pattern_lengths[0] = 60 * 5; 
	pattern_lengths[1] = 60 * REST_TIME; // 休憩
	pattern_lengths[2] = 60 * 5;
	pattern_lengths[3] = 60 * REST_TIME; // 休憩
	pattern_lengths[4] = 60 * 5;
	pattern_lengths[5] = 60 * REST_TIME; // 休憩
	pattern_lengths[6] = 60 * 10;
	pattern_lengths[7] = 60 * REST_TIME; // 休憩
	pattern_lengths[8] = 60 * 10;
	pattern_lengths[9] = 60 * REST_TIME; // 休憩
	pattern_lengths[10] = 60 * 18; 
	pattern_lengths[11] = 60 * REST_TIME; // 休憩
	pattern_lengths[12] = 60 * 5; 
	pattern_lengths[13] = 60 * REST_TIME; // 休憩
	pattern_lengths[14] = 60 * 5;
	pattern_lengths[15] = 60 * REST_TIME; // 休憩
}

void cGameManager::GameOver()
{
	StopSoundMem(s_bgm);
	StopSoundMem(s_boss_bgm);
	StopSoundMem(p->s_danger);

	int start = GetNowCount();
	const TCHAR *go = "GAME OVER";

	int go_w = GetDrawStringWidth(go,strlen(go));
	SetFontSize(0); // フォントサイズをリセットする
	for(int i = 0 ; GetNowCount() - start < 5000 ; i++)
	{
		ClearDrawScreen();
		if(i < 150)	SetFontSize(i);
		go_w = GetDrawStringWidth(go,strlen(go));
		if(i <= 255)
		{
			DrawString(GameScreenWidth / 2  - (go_w / 2), GameScreenHeight / 2,"GAME OVER",GetColor(255 - i,0,0),1);
		}
		else
		{
			DrawString(GameScreenWidth / 2  - (go_w / 2), GameScreenHeight / 2,"GAME OVER",GetColor(0,0,0),1);
		}

		DrawGraph(WindowWidth - 256, 0, i_sidebar,true);
		DrawGraph(0,WindowHeight - 61,i_underbar,true);
		ScreenFlip();
	}
	scene = 0;		// ESCAPEキーを押したらゲームを終了させる
	this->Init();
}
void cGameManager::ToggleFunction()
{
	// Pが押されたらデバッグ画面のモードを切り替える
	if(CheckHitKey(KEY_INPUT_P) == 1 && now % KEY_WAITTIME == 0)
	{
		debug_index++;
		if(debug_index >= 4) debug_index = 0;
	}

	// Kキーが押されたら自滅する
	if(CheckHitKey(KEY_INPUT_K) == 1) 
	{
		p->Dead();
		GameOver();
	}

	// プレイヤーの操作
	if(p->GetAlive() && scene == 2)
	{
		if(CheckHitKey(KEY_INPUT_A) == 1 || CheckHitKey(KEY_INPUT_LEFT) == 1) p->MoveX(p->GetSpeed() * -1);	// LEFTキーを押したらプレイヤーを左へ移動させる		
		if(CheckHitKey(KEY_INPUT_D) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1) p->MoveX(p->GetSpeed());		// RIGHTキーを押したらプレイヤーを右へ移動させる
		if(CheckHitKey(KEY_INPUT_W) == 1 || CheckHitKey(KEY_INPUT_UP) == 1) p->MoveY(p->GetSpeed() * -1);		// UPキーを押したらプレイヤーを上へ移動させる
		if(CheckHitKey(KEY_INPUT_S) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1) p->MoveY(p->GetSpeed());		// UPキーを押したらプレイヤーを上へ移動させる
		barriar->UpdateLocation(*p);
	}

	// Lキーが押されたらレベルを強制的に上げる
	if(CheckHitKey(KEY_INPUT_L) && now % KEY_WAITTIME == 0)
	{
		char *str;
		if(p->GetLevel() == 1) p->SetExp(p->GetNeedExp(p->GetLevel()) - p->GetExp());

		str = p->AddExp(p->GetNeedExp(p->GetLevel() + 1) - p->GetExp());
		if(str == "rapid") p->SetRapid();
		if(str == "barriar") barriar->Create();
		for(int i = 0;i < BEAM_NUM ; i++)
		{
			if(str == "bullet_speed")
			{
				beam[i]->SetSpeed(beam[i]->GetSpeed() + ADD_SPEED);				
			}
		}
	}

	if(CheckHitKey(KEY_INPUT_ESCAPE)) close(); // escapeが押されたらゲームを終了する
}
void cGameManager::close(){ GameFrag = false; }
void cGameManager::Init()
{
	// 各変数、データを初期化する
	pattern_group1 = 0;
	pattern_group2 = 0;
	active_group1 = true;
	active_group2 = false;
	spawn_group_count = 0;
	bgm_vol = 30;
	now = 0;
	count = 0;
	count2 = 0;
	boss_wait = 0;
	fade_count = 0;
	selected = 0;
	select = 1;
	debug_index = 0;
	frag = false;
	frag2 = false;
	GameFrag = true;
	boss_frag = false;
	warning_frag = false;


	// プレイヤーインスタンス
	p = new cPlayer(GameScreenWidth / 2 - (62 / 2), GameScreenHeight - 100,3);
	p->SetUpgrades();

	// バリアインスタンス
	barriar = new cBarriar(*p);

	// 敵キャラインスタンス
	for(int i = 0; i < COMMON_NUM ; i++){
		common1[i] = new cCommon(); // パターン1の雑魚敵
		common1[i]->SetPattern(pattern_group1);
		common1[i]->Init();
		common2[i] = new cCommon();
		common2[i]->SetPattern(pattern_group2);
		common2[i]->Init();
	}

	// ボスインスタンス
	boss = new cBoss();
	boss->Init();

	// 武器インスタンス
	for(int i = 0; i < BEAM_NUM ; i++)
	{
		beam[i] = new cBeam(p->GetX(),p->GetY());
		enemy_weapon_beam[i] = new cEnemyWeapon(boss->GetX(),boss->GetY(),BOSS_WEAPON_BEAM);
	}
	enemy_weapon_laser[0] = new cEnemyWeapon(boss->GetX(),boss->GetY(),BOSS_WEAPON_LASER);
	enemy_weapon_laser[1] = new cEnemyWeapon(boss->GetX(),boss->GetY(),BOSS_WEAPON_LASER);
	enemy_weapon_laser[0]->Init(boss->GetX(),boss->GetY());
	enemy_weapon_laser[1]->Init(boss->GetX(),boss->GetY());
	enemy_weapon_laser[0]->SetLaserLocation(0);
	enemy_weapon_laser[1]->SetLaserLocation(1);

	// 時間管理クラスのインスタンス
	time = new cTimeManager();

	// 敵の出現パターンの制限時間を設定する
	this->SetPatternLengths();

	// タイトル画面用のBGMを流す
	if(CheckSoundMem(s_title_bgm) == 0 && scene == 0) PlaySoundMem(s_title_bgm,DX_PLAYTYPE_BACK);
}

void cGameManager::TitleProcess()
{
	// 各カウンタを進める
	now++;
	count += 8;
	if(!frag)
	{
		if(fade_count < 255)
		{
			fade_count++;
		}
		else
		{
			fade_count = 255;
		}
	}

	
	// フェードイン処理のために彩度を調整
	SetDrawBright(fade_count,fade_count,fade_count);

	ClearDrawScreen();

	// 背景を動かす
	if(count > WindowWidth) count = 0;
	DrawGraph(count,0,i_background_title,true);
	DrawGraph((WindowWidth * -1) + count ,0,i_background_title,true);

	// 上下キーが押されたらメニューの選択項目を切り替える
	if(CheckHitKey(KEY_INPUT_DOWN) == 1 && now % KEY_WAITTIME == 0){
		if(CheckSoundMem(s_move_cursor)) StopSoundMem(s_move_cursor);
		PlaySoundMem(s_move_cursor,DX_PLAYTYPE_BACK);

		if(select % MENU_ITEM == 0) 
		{
			select = 1;
		}
		else
		{
			select++;
		}
	}
	if(CheckHitKey(KEY_INPUT_UP) == 1 && now % KEY_WAITTIME == 0){
		if(CheckSoundMem(s_move_cursor)) StopSoundMem(s_move_cursor);
		PlaySoundMem(s_move_cursor,DX_PLAYTYPE_BACK);

		if(select <= 1) 
		{
			select = MENU_ITEM;
		}
		else
		{
			select--;
		}
	}

	// 各メニュー項目のラベルを描画

	switch(select)
	{
	case 1:
		DrawGraph(WindowWidth / 2 - 150,WindowHeight / 2 + 100,i_SelectStartLabel,true);
		DrawGraph(WindowWidth / 2 - 160,WindowHeight / 2 + 100 + 150,i_ExitLabel,true);
		break;
	case 2:
		DrawGraph(WindowWidth / 2 - 150,WindowHeight / 2 + 100,i_StartLabel,true);
		DrawGraph(WindowWidth / 2 - 160,WindowHeight / 2 + 100 + 150,i_SelectExitLabel,true);
		break;
	}

	// タイトルのラベルを描画
	DrawGraph(100, 100,i_TitleLabel,true);

	// SPACEキーで現在選択されている項目に決定する
	if(now > 60)
	{
		if(CheckHitKey(KEY_INPUT_SPACE) || frag)
		{
			if(!frag)
			{
				if(CheckSoundMem(s_decide)) StopSoundMem(s_decide);
				if(CheckSoundMem(s_title_bgm)) StopSoundMem(s_title_bgm);
				PlaySoundMem(s_decide,DX_PLAYTYPE_BACK);
			}

			frag = true;

			if(fade_count > 0)
			{
				fade_count-=3;
				SetDrawBright(fade_count,fade_count,fade_count);
			}
			else
			{
				selected = select;
				fade_count = 255;
				SetDrawBright(fade_count,fade_count,fade_count);
				frag = false;
				now = 0;
				count = 0;
			}
		}
	}


	ScreenFlip();
}

void cGameManager::StartProcess()
{
	ClearDrawScreen();
	now++;

	barriar->UpdateLocation(*p);
	if(now / (60 * 2) < 1)
	{
		Draw();
		p->MoveY(-1);
		p->Draw();
	}
	else if(now / (60 * 5) < 1)
	{
		Draw();
		p->Draw();	
	}
	else
	{
		scene = 2;
		now = 0;
		time->UpdateLastChangeEnemyPattern(now);
		PlaySoundMem(s_bgm, DX_PLAYTYPE_BACK);
	}

	ToggleFunction();

	ScreenFlip();
}

void cGameManager::GameProcess()
{
	ClearDrawScreen();	// 画面の描画情報を全て削除
	now++; // ゲームカウントを進める

	ToggleFunction();


	// 現在の出現パターンの時間が終わったら次のパターンに切り替える
	if(now - time->GetLastChangeEnemyPattern() > pattern_lengths[spawn_group_count])
	{
		if(!boss_frag) spawn_group_count++;
		switch(spawn_group_count)
		{
		case 2:
			time->UpdateLastChangeEnemyPattern(now);
			pattern_group1 = 1;
			active_group1 = true;
			active_group2 = false;
			break;
			break;
		case 4:
			time->UpdateLastChangeEnemyPattern(now);
			pattern_group1 = 0;
			pattern_group2 = 1;
			active_group1 = true;
			active_group2 = true;
			break;
		case 6:
			time->UpdateLastChangeEnemyPattern(now);
			pattern_group1 = 4;
			active_group1 = true;
			active_group2 = false;
			break;
		case 8:
			time->UpdateLastChangeEnemyPattern(now);
			pattern_group2 = 5;
			active_group1 = false;
			active_group2 = true;
			break;
		case 10:
			time->UpdateLastChangeEnemyPattern(now);
			pattern_group1 = 4;
			pattern_group2 = 5;
			active_group1 = true;
			active_group2 = true;
			break;
		case 12:
			boss_frag = true;
			if(boss->GetAlive() == false)
			{
				if(boss_wait < 3 * 60)
				{
					boss_wait++;
					if(boss_wait % 6 == 0) 
					{	
						bgm_vol--;
						if(bgm_vol < 30) ChangeVolumeSoundMem( 255 * bgm_vol / 100, s_bgm );
					}
				}
				else if(boss_wait < WARNING_TIME * 60)
				{
					warning_frag = true;
					boss_wait++;
					if(!CheckSoundMem(s_warning)) PlaySoundMem(s_warning,DX_PLAYTYPE_LOOP);
					if(boss_wait < 60 * 8) // 右の条件式はWARNINGの画像がいきなり消えるのを防ぐため
					{
						if(frag2 == false)
						{
							fade_count += 6;
							if(fade_count >= 200) frag2 = true;
						}
						else
						{
							fade_count -= 6;
							if(fade_count <= 0) frag2 = false;
						}
					}
				}
				else
				{
					warning_frag = false;
					fade_count = 0;
					boss_wait = 0;
					boss->Spawn();
					StopSoundMem(s_bgm);
					StopSoundMem(s_warning);
					if(!CheckSoundMem(s_boss_bgm))PlaySoundMem(s_boss_bgm,DX_PLAYTYPE_LOOP);
				}
			}
			break;
		case 14:

			break;
		default:
			// 何もしない
			active_group1 = false;
			active_group2 = false;
			time->UpdateLastChangeEnemyPattern(now);
		}

	}

	/* 敵キャラグループの移動パターンを変更する */
	for(int i = 0; i < COMMON_NUM && !boss_frag ; i++)
	{
		// グループ１がアクティブかつ、出現していない敵のパターンを変更する
		if(common1[i]->GetAlive() == false && active_group1 == true)
		{
			common1[i]->SetPattern(pattern_group1);
			common1[i]->Init();
		}

		// グループ２がアクティブかつ、出現していない敵のパターンを変更する
		if(common2[i]->GetAlive() == false && active_group2 == true)
		{
			common2[i]->SetPattern(pattern_group2);
			common2[i]->Init();
		}
	}

	/*** ビームの生成処理 ***/
	/*** 自機のビーム ***/
	if(CheckHitKey(KEY_INPUT_SPACE)  && p->GetAlive() && now % p->GetRapid() == 0)
	{
		for(int i = 0 ; i < BEAM_NUM ; i++)
		{
			if(beam[i]->GetActive() == false)
			{
				beam[i]->Init( p->GetX() + (p->GetWidth() / 2 - beam[i]->GetWidth() / 2),p->GetY());
				beam[i]->Fire();
				break;
			}
		}
	}
	/*** ボスのビーム ***/
	if(boss->GetAlive() && boss->GetStart())
	{
		if(now % boss->GetFireSpan() == 0)
		{
			for(int i = 0; i < BEAM_NUM; i++)
			{
				if(enemy_weapon_beam[i]->GetActive() == false)
				{
					enemy_weapon_beam[i]->Fire(p);
					break;
				}
			}
		}

		if(enemy_weapon_laser[0]->GetLaserMax() || enemy_weapon_laser[0]->GetLaserMax())
		{
			enemy_weapon_laser[0]->Init(boss->GetX(),boss->GetY());
			enemy_weapon_laser[1]->Init(boss->GetX(),boss->GetY());
		}
	}
	
	/*** ビームの移動処理 ***/
	for(int i = 0; i < BEAM_NUM ; i++)
	{
		if(beam[i]->GetActive() == true)
		{
			// ビームを1フレーム分動かす
			beam[i]->Move();
		}
		else
		{
			//　ビームの座標を自機の座標へリセットする
			beam[i]->SetX( (p->GetX() + p->GetWidth() / 2) - (beam[i]->GetWidth() / 2) );
			beam[i]->SetY( (p->GetY() + p->GetHeight() / 2) - (beam[i]->GetHeight() / 2) );
		}

		/*** ボスのビーム ***/
		if(enemy_weapon_beam[i]->GetActive() == true)
		{
			enemy_weapon_beam[i]->Move();
		}
		else
		{
			//　ビームの座標を自機の座標へリセットする
			enemy_weapon_beam[i]->SetX( (boss->GetX() + boss->GetWidth() / 2) - (enemy_weapon_beam[i]->GetWidth() / 2) );
			enemy_weapon_beam[i]->SetY( (boss->GetY() + boss->GetHeight() / 2) - (enemy_weapon_beam[i]->GetHeight() / 2) );
		}
	}



	// ザコキャラの処理
	for(int i = 0 ; i < COMMON_NUM && !boss_frag ; i++)
	{
		if(active_group1)
		{
			if( (common1[i]->GetAlive() == false) && (now % common1[i]->GetSpawnSpan() == 0) && (now - time->GetLastSpawnCommon1() > common1[i]->GetSpawnSpan()) && boss_frag == false )
			{
				common1[i]->Spawn();
				time->UpdateLastSpawnCommon1(now);
				break;
			}
		}
		if(active_group2)
		{
			if( (common2[i]->GetAlive() == false) && (now % common2[i]->GetSpawnSpan() == 0) && (now - time->GetLastSpawnCommon2() > common2[i]->GetSpawnSpan()) && boss_frag == false )
			{
				common2[i]->Spawn();
				time->UpdateLastSpawnCommon2(now);
				break;
			}
		}
	}

	// ボスの処理
	if(boss_frag && boss->GetAlive())
	{
		boss->Move();
	}

	/***	衝突判定	***/
	// ビームの処理
	for(int i = 0; i < BEAM_NUM ; i++)
	{
		// 衝突せずに画面外に出て行ったらビームを消す
		if(beam[i]->GetY() < 0) beam[i]->Delete();
		if(enemy_weapon_beam[i]->GetY() > GameScreenHeight) enemy_weapon_beam[i]->Delete();

		// ザコキャラとビームが衝突したら
		for(int j = 0; j < COMMON_NUM && !boss_frag ; j++)
		{
			// グループ１との検査
			if(checkHit(beam[i]->GetX(), beam[i]->GetY(), beam[i]->GetWidth(), beam[i]->GetHeight(),
				common1[j]->GetX(), common1[j]->GetY(), common1[j]->GetWidth(), common1[j]->GetHeight(),5,0) && beam[i]->GetActive() && common1[j]->GetAlive())
			{
				char *str = "null";

				common1[j]->Damage(1);
				str = p->AddExp(2);
				if(str == "rapid") p->SetRapid();
				if(str == "barriar") barriar->Create();
				if(str == "bullet_speed")
				{
					for(int k = 0; k < BEAM_NUM;k++)
					{
						beam[k]->SetSpeed(beam[k]->GetSpeed() + ADD_SPEED);				
					}
				}
				beam[i]->Delete();

				if(common1[j]->GetHP() <= 0)
				{
					if(common1[j]->GetPattern() == 999) boss_frag = false;
					common1[j]->Dead();
					common1[j]->Init();
					str = p->AddExp(common1[j]->GetDropExp());
					if(str == "rapid") p->SetRapid();
					if(str == "barriar") barriar->Create();
					if(str == "bullet_speed")
					{
						for(int k = 0; k < BEAM_NUM;k++)
						{
							beam[k]->SetSpeed(beam[k]->GetSpeed() + ADD_SPEED);				
						}
					}
				}
				else
				{
					beam[i]->Delete();
				}

			}

			// グループ２との検査
			if(checkHit(beam[i]->GetX(), beam[i]->GetY(), beam[i]->GetWidth(), beam[i]->GetHeight(),
				common2[j]->GetX(), common2[j]->GetY(), common2[j]->GetWidth(), common2[j]->GetHeight(),5,0) && beam[i]->GetActive() && common2[j]->GetAlive())
			{
				char *str = "null";

				common2[j]->Damage(1);
				str = p->AddExp(2);
				if(str == "rapid") p->SetRapid();
				if(str == "barriar") barriar->Create();
				if(str == "bullet_speed")
				{
					for(int k = 0; k < BEAM_NUM;k++)
					{
						beam[k]->SetSpeed(beam[k]->GetSpeed() + ADD_SPEED);				
					}
				}
				beam[i]->Delete();

				if(common2[j]->GetHP() <= 0)
				{
					if(common2[j]->GetPattern() == 999) boss_frag = false;
					common2[j]->Dead();
					common2[j]->Init();
					str = p->AddExp(common2[j]->GetDropExp());
					if(str == "rapid") p->SetRapid();
					if(str == "barriar") barriar->Create();
					if(str == "bullet_speed")
					{
						for(int k = 0; k < BEAM_NUM;k++)
						{
							beam[k]->SetSpeed(beam[k]->GetSpeed() + ADD_SPEED);				
						}
					}
				}
				else
				{
					beam[i]->Delete();
				}
			}
		}

		// グループ１との検査
		if(checkHit(beam[i]->GetX(), beam[i]->GetY(), beam[i]->GetWidth(), beam[i]->GetHeight(),
			boss->GetX(), boss->GetY(), boss->GetWidth(), boss->GetHeight(),5,40) && beam[i]->GetActive() && boss->GetAlive())
		{
			char *str = "null";

			boss->Damage(1);
			str = p->AddExp(2);
			if(str == "rapid") p->SetRapid();
			if(str == "barriar") barriar->Create();
			if(str == "bullet_speed")
			{
				for(int k = 0; k < BEAM_NUM;k++)
				{
					beam[k]->SetSpeed(beam[k]->GetSpeed() + ADD_SPEED);				
				}
			}

			if(boss->GetHP() <= 0)
			{
				boss->Dead();
				boss->Init();
				//str = p->AddExp(common1[j]->GetDropExp());
				//if(str == "rapid") p->SetRapid();
				//if(str == "barriar") barriar->Create();
				//if(str == "bullet_speed")
				//{
				//	for(int k = 0; k < BEAM_NUM;k++)
				//	{
				//		beam[k]->SetSpeed(beam[k]->GetSpeed() + ADD_SPEED);				
				//	}
				//}
			}
			beam[i]->Delete();

		}


	}

	for(int i = 0 ; i < COMMON_NUM && !boss_frag ; i++)
	{
		// 自機とザコキャラが衝突したら
		if(checkHit(p->GetX(), p->GetY(), p->GetWidth(), p->GetHeight(),
			common1[i]->GetX(), common1[i]->GetY(), common1[i]->GetWidth(), common1[i]->GetHeight(),4,4) && common1[i]->GetAlive() && p->GetAlive())
		{
			if(barriar->GetAlive())
			{
				if(barriar->GetHP() > 1) 
				{
					barriar->Damage(1);
				} 
				else
				{ 
					barriar->Damage(1);
					barriar->Delete();
				}
			}
			else
			{
				if(p->GetLife() > 1) 
				{
					p->SetLife(p->GetLife() - 1);
				} 
				else
				{ 
					p->SetLife(0);
					p->Dead();
				}
			}

			common1[i]->Dead();
			common1[i]->Init();
		}
		if(checkHit(p->GetX(), p->GetY(), p->GetWidth(), p->GetHeight(),
			common2[i]->GetX(), common2[i]->GetY(), common2[i]->GetWidth(), common2[i]->GetHeight(),4,4) && common2[i]->GetAlive() && p->GetAlive())
		{
			if(barriar->GetAlive())
			{
				if(barriar->GetHP() > 1) 
				{
					barriar->Damage(1);
				} 
				else
				{ 
					barriar->Damage(1);
					barriar->Delete();
				}
			}
			else
			{
				if(p->GetLife() > 1) 
				{
					p->SetLife(p->GetLife() - 1);
				} 
				else
				{ 
					p->SetLife(0);
					p->Dead();
				}
			}
			common2[i]->Dead();
			common2[i]->Init();
		}
	}

	/*** 描画処理 ***/
	Draw();

	/*** 終了の処理 ***/
	if(!p->GetAlive()) GameOver();

	ScreenFlip(); // バッファー画面の描画内容を表画面に反映

}

bool cGameManager::checkHit(int x1, int y1, int w1 , int h1, int x2, int y2, int w2, int h2, int margin1,int margin2)
{
	if((x1 + margin1 > x2 + margin2 && x1 + margin1 < x2 + w2 - margin2) || (x2 + margin2 > x1 + margin1 && x2 + margin2 < x1 + w1 - margin1))
	{
		if((y1 + margin1 > y2 + margin2 && y1 + margin1 < y2 + h2 - margin2) || (y2 + margin2  > y1 + margin1 && y2 + margin2 < y1 + h1 - margin1))
		{
			return true;
		}
	}

	return false;
}

void cGameManager::showDebugScreen()
{
	char bState = 'F';
	char cState = 'F';

	SetFontSize(20);


	switch(debug_index)
	{
	case 0: // 何も表示しない
		break;
	case 1: // プレイヤーの情報を表示
		DrawFormatString(10,10,green,"cPlayer -> X:%d",p->GetX());
		DrawFormatString(10,30,green,"cPlayer -> Y:%d",p->GetY());
		DrawFormatString(10,50,green,"cPlayer -> Life:%d",p->GetLife());
		DrawFormatString(10,70,green,"cPlayer -> Level:%d",p->GetLevel());
		DrawFormatString(10,90,green,"WAVE : %d",spawn_group_count);
		break;
	case 2: // 敵キャラ
		for(int i = 0 ; i < COMMON_NUM && !boss_frag; i++)
		{
			if(common1[i]->GetAlive() == true)
			{
				cState = 'T';
			}
			else
			{
				cState = 'F';
			}

			DrawFormatString(10,20 * i,red,"Common1[%d] -> FRAG:%c(HP:%d) X:%d Y:%d Pattern:%d",
				i + 1 ,cState,common1[i]->GetHP() ,common1[i]->GetX(), common1[i]->GetY(),common1[i]->GetPattern());

			if(common2[i]->GetAlive() == true)
			{
				cState = 'T';
			}
			else
			{
				cState = 'F';
			}

			DrawFormatString(GameScreenWidth - 300 ,20 * i,red,"Common2[%d] -> FRAG:%c(HP:%d) X:%d Y:%d Pattern:%d",
				i + 1 ,cState,common2[i]->GetHP() ,common2[i]->GetX(), common2[i]->GetY(),common2[i]->GetPattern());
		}
		break;

	case 3: // ビーム
		for(int i = 0; i < BEAM_NUM ; i++)
		{
			if(beam[i]->GetActive() == true)
			{
				bState = 'T';
			}
			else
			{
				bState = 'F';
			}

			DrawFormatString(10,20 * i,sky_blue,"cBeam[%d] -> FRAG:%c",i + 1 ,bState);
		}
		break;
	}
}

void cGameManager::Draw()
{
	if(count > GameScreenHeight) count = 0;
	DrawGraph(0,count,i_background,true);
	DrawGraph(0,(GameScreenHeight * -1) + count,i_background,true);
	count += 4;

	// ビームを描画する
	for(int i = 0; i < BEAM_NUM; i++)
	{
		if(beam[i]->GetActive()) beam[i]->Draw();
		if(enemy_weapon_beam[i]->GetActive()) enemy_weapon_beam[i]->Draw(boss);
	}

	// ボスのレーザーを描画する
	for(int i = 0; i < 2 ; i++)
	{
		if(boss->GetAlive()) enemy_weapon_laser[i]->Draw(boss);
	}

	// プレイヤーを描画する
	if(barriar->GetAlive()) barriar->Draw();
	if(p->GetAlive()) p->Draw();

	//ザコキャラを描画する
	for(int i = 0 ; i < COMMON_NUM && !boss_frag ; i++)
	{
		// グループ１
		if( (common1[i]->GetY() > GameScreenHeight) || (common1[i]->GetY() + common1[i]->GetHeight() * 2 < 0) || 
			(common1[i]->GetX() > GameScreenWidth) || (common1[i]->GetX() + common1[i]->GetWidth() < 0) )
		{
			common1[i]->Dead();
			common1[i]->Init();
		}

		if(common1[i]->GetAlive() == true)
		{
			common1[i]->Move();
			common1[i]->Draw();
		}

		// グループ２
		if( (common2[i]->GetY() > GameScreenHeight) || (common2[i]->GetY() + common2[i]->GetHeight() * 2 < 0) || 
			(common2[i]->GetX() > GameScreenWidth) || (common2[i]->GetX() + common2[i]->GetWidth() < 0) )
		{
			common2[i]->Dead();
			common2[i]->Init();
		}

		if(common2[i]->GetAlive() == true)
		{
			common2[i]->Move();
			common2[i]->Draw();
		}
	}
	if(boss->GetAlive()) boss->Draw();

	DrawGraph(WindowWidth - 256, 0, i_sidebar,true); // サイドバーの描画

	DrawBox(0,WindowHeight - 61,1026,WindowHeight+1,black,true);
	if(p->GetLevel() > 1)
	{
		DrawBox(0,WindowHeight - 61,(int)(1026 * ( (double)p->GetExp() / (double)p->GetNeedExp(p->GetLevel() + 1)) ),WindowHeight+1,yellow,true);
	}
	else
	{
		DrawBox(0,WindowHeight - 61,(int)(1026 * ((double)p->GetExp() / (double)p->GetNeedExp(p->GetLevel() + 1))),WindowHeight+1,yellow,true);
	}

	DrawGraph(0,WindowHeight - 61,i_underbar,true);

	switch(p->GetLife())
	{
	case 1:
		DrawGraph(WindowWidth - 257,90,i_HPLabel1,true);
		break;
	case 2:
		DrawGraph(WindowWidth - 257,90,i_HPLabel2,true);
		break;
	case 3:
		DrawGraph(WindowWidth - 257,90,i_HPLabel3,true);
		break;
	}


	DrawGraph(WindowWidth - 250,210,i_LevelLavel,true);

	int place = GetPlace(p->GetLevel());
	int startx =  WindowWidth - 175; // 1桁だったとき
	if(place == 2) startx = WindowWidth - 150; // ２桁だったとき

	for(int i = 0,level = p->GetLevel(); i < place; i++)
	{
		DrawGraph(startx - i * 55,270,i_numbers[level % 10],true);
		level /= 10;
	}

	if(warning_frag)
	{
		SetDrawBright(fade_count,fade_count,fade_count);
		DrawGraph(0,0,i_Warning,true);
		SetDrawBright(255,255,255);
	}

	// デバッグ画面の描画
	showDebugScreen();

}

int cGameManager::GetPlace(int value)
{
	int place; // 整数の桁数を保存する変数
	int buffer = 10;
	for(place = 1; value >= buffer ; place++)
	{
		buffer += buffer * 10;
	}

	return place;
}
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework {
	int CGameState::initialize = 1;   // 需要初始化
	int CGameState::level;
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////
	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
		isMusicLoaded = false;									// 尚未載入音樂
		isPlayed = false;
		showingCtrl = false;
		showingSkill = false;
	}

	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0);									// 一開始的loading進度為0%
																//
																// 開始載入資料
																//
		menu.LoadBitmap(IDB_MENU);									 // 載入遊戲選單
		control.LoadBitmap(IDB_CONTROL);							 // 載入按鍵設置圖
		leftsign.LoadBitmap(IDB_LEFTSIGN, RGB(0, 0, 0));			 // 載入左符號
		rightsign.LoadBitmap(IDB_RIGHTSIGN, RGB(0, 0, 0));			 // 載入右符號
		backToMenu1.LoadBitmap(IDB_BACKTOMENU1, RGB(0, 0, 0));		 // 返回選單
		backToMenu2.LoadBitmap(IDB_BACKTOMENU2, RGB(0, 0, 0));		 // hover返回選單
		scroll1.LoadBitmap(IDB_SCROLL1, RGB(255, 255, 255));		 // 閉卷軸
		scroll2.LoadBitmap(IDB_SCROLL2, RGB(255, 255, 255));		 // 開卷軸
		skills.LoadBitmap(IDB_SKILLS);								 // 密技圖
		ShowInitProgress(11);									// 一開始的loading進度為11%
	}

	void CGameStateInit::OnBeginState()
	{
		if (!isMusicLoaded) {											 // 如果未載入音樂
			CAudio::Instance()->Load(AUDIO_MENU, "sounds\\menu.wav");	 // 載入背景音樂
			CAudio::Instance()->Load(AUDIO_HOVER, "sounds\\hover.wav");  // hover音效
			isMusicLoaded = true;										 // 已載入音樂
		}
		CAudio::Instance()->Play(AUDIO_MENU, true);						 // 播放音樂
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		downMouseX = point.x;														 // 取得滑鼠X座標
		downMouseY = point.y;														 // 取得滑鼠Y座標
		if (showingCtrl) {															 // 正在看按鍵圖
			if (0 < downMouseX && downMouseX < 640 && 0 < downMouseY && downMouseY < 480)
				showingCtrl = false;
		}
		else if (showingSkill) {													 // 正在看密技圖
			if (0 < downMouseX && downMouseX < 640 && 0 < downMouseY && downMouseY < 480)
				showingSkill = false;
		}
		else if (280 < point.x && point.x < 350 && 255 < point.y && point.y < 275) { // 點擊開始遊戲
			switch (level) {
			case 0:
				GotoGameState(GAME_STATE_RUN);										 // 切換至GAME_STATE_RUN
				break;
			case 1:
				GotoGameState(GAME_STATE_RUN1);										 // 切換至GAME_STATE_RUN1
				break;
			default:
				GotoGameState(GAME_STATE_RUN);										 // 切換至GAME_STATE_RUN
				break;
			}
			CAudio::Instance()->Stop(AUDIO_MENU);
		}
		else if (280 < point.x && point.x < 350 && 325 < point.y && point.y < 345) { // 點擊關卡選擇
			GotoGameState(GAME_STATE_SELECT);
		}
		else if (280 < point.x && point.x < 350 && 365 < point.y && point.y < 385) { // 點擊結束遊戲
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);					 // 關閉遊戲
		}
	}

	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		moveMouseX = point.x;	//取得滑鼠X座標
		moveMouseY = point.y;	//取得滑鼠Y座標
	}

	void CGameStateInit::OnShow()
	{
		menu.SetTopLeft(0, 58);
		menu.ShowBitmap();
		scroll1.SetTopLeft(30, 350); //閉卷軸
		scroll1.ShowBitmap();

		if (280 < downMouseX && downMouseX < 350 && 295 < downMouseY && downMouseY < 315) {		//////////////////
			showingCtrl = true;																	//				//
			control.SetTopLeft(0, 60);															//			    //	
			control.ShowBitmap();																//			    //
			backToMenu1.SetTopLeft(0, 420);														//				//
			backToMenu1.ShowBitmap();															//顯示按鍵設定圖 //
			if (0 < moveMouseX && moveMouseX < 160 && 420 < moveMouseY && moveMouseY < 480) {   //              //
				backToMenu2.SetTopLeft(0, 420);													//				//
				backToMenu2.ShowBitmap();														//				//
			}																					//				//
		}																						//////////////////
		else if (30 < downMouseX && downMouseX < 95 && 350 < downMouseY && downMouseY < 390) {  //////////////////
			showingSkill = true;																//				//
			skills.SetTopLeft(0, 60);															//			    //	
			skills.ShowBitmap();																//	  秘技圖		//
		}																						//////////////////
		else if (280 < moveMouseX && moveMouseX < 350 && 255 < moveMouseY && moveMouseY < 275) {//////////////////
			if (isPlayed == false) {															//				//
				CAudio::Instance()->Play(AUDIO_HOVER, false);									//				//
				isPlayed = true;																//已經撥放過音效 //
			}																					//				//
			leftsign.SetTopLeft(225, 235);														//	 開始遊戲	//
			leftsign.ShowBitmap();																// 顯示左右符號  //
			rightsign.SetTopLeft(330, 235);														//              //
			rightsign.ShowBitmap();																//////////////////
		}
		else if (280 < moveMouseX && moveMouseX < 350 && 295 < moveMouseY && moveMouseY < 315) {//////////////////
			if (isPlayed == false) {															//				//
				CAudio::Instance()->Play(AUDIO_HOVER, false);									//				//
				isPlayed = true;																//已經撥放過音效 //
			}																					//				//
			leftsign.SetTopLeft(225, 265);														//	 鍵盤操做	//
			leftsign.ShowBitmap();																// 顯示左右符號  //
			rightsign.SetTopLeft(330, 265);														//              //
			rightsign.ShowBitmap();																//////////////////
		}
		else if (280 < moveMouseX && moveMouseX < 350 && 325 < moveMouseY && moveMouseY < 345) {//////////////////
			if (isPlayed == false) {															//				//
				CAudio::Instance()->Play(AUDIO_HOVER, false);									//				//
				isPlayed = true;																//已經撥放過音效 //
			}																					//				//
			leftsign.SetTopLeft(225, 300);														//	 關卡選擇	//
			leftsign.ShowBitmap();																// 顯示左右符號  //
			rightsign.SetTopLeft(330, 300);														//              //
			rightsign.ShowBitmap();																//////////////////
		}
		else if (280 < moveMouseX && moveMouseX < 350 && 365 < moveMouseY && moveMouseY < 385) {//////////////////
			if (isPlayed == false) {															//				//
				CAudio::Instance()->Play(AUDIO_HOVER, false);									//				//
				isPlayed = true;																//已經撥放過音效 //
			}																					//				//
			leftsign.SetTopLeft(225, 340);														//	 離開遊戲	//
			leftsign.ShowBitmap();																// 顯示左右符號  //
			rightsign.SetTopLeft(330, 340);														//              //
			rightsign.ShowBitmap();																//////////////////
		}
		else if (30 < moveMouseX && moveMouseX < 95 && 350 < moveMouseY && moveMouseY < 390) {	// 開卷軸
			if (isPlayed == false) {
				CAudio::Instance()->Play(AUDIO_HOVER, false);
				isPlayed = true;
			}
			scroll2.SetTopLeft(30, 350);
			scroll2.ShowBitmap();
		}
		else{
			isPlayed = false;
		}
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}

	void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
	{
		if (0 < point.x && point.x < 640 && 0 < point.y && point.y < 480) {			 // 左鍵回到目錄
			GotoGameState(GAME_STATE_INIT);											 // 切換至GAME_STATE_RUN
		}
	}

	void CGameStateOver::OnMove()
	{
	}

	void CGameStateOver::OnBeginState()
	{
	}

	void CGameStateOver::OnInit()
	{
		ShowInitProgress(22);	// 接個前一個狀態的進度，此處進度視為22%
		gameover.LoadBitmap(IDB_HK_GAMEOVER); //載入結束圖片
	}

	void CGameStateOver::OnShow()
	{
		gameover.SetTopLeft(0, 0);
		gameover.ShowBitmap();
	}

	///////////////////////////////////////////////////////////////////////////// 
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////
	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g)
	{

	}

	CGameStateRun::~CGameStateRun()
	{

	}

	void CGameStateRun::OnBeginState()
	{
		CAudio::Instance()->Play(AUDIO_INGAME, true);			 // 遊戲背景音樂
		CAudio::Instance()->Play(AUDIO_MONSTERSTILLALIVE, true); // 怪物聲音
		if (initialize == 1) {				// 如果需要初始化
			knight.Initialize();			// 主角初始化
			map.Initialize(level);			// 地圖初始化
			weapon.Initialize(&knight);		// 武器初始化
			monster.Initialize();			// 怪物初始化
			initialize = 0;
		}
	}

	void CGameStateRun::OnMove()
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));		// 鼠標
		map.OnMove(&knight);								// 地圖
		knight.OnMove(&map);								// 主角
		weapon.OnMove(&knight);								// 武器
		monster.OnMove(&knight);							// 怪物
		knight.SetTouchMonster(&monster);					// 主角是否被怪物碰到

		if (knight.isDeath(&map)) {							// 如果角色死亡		
			initialize = 1;									// 需要初始化
			CAudio::Instance()->Stop(AUDIO_INGAME);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
			CAudio::Instance()->Stop(AUDIO_MONSTERSTILLALIVE);
			CAudio::Instance()->Stop(AUDIO_JUMP);
			CAudio::Instance()->Stop(AUDIO_SHOOT);
			CAudio::Instance()->Stop(AUDIO_PICK);
			CAudio::Instance()->Stop(AUDIO_SLASH);
			CAudio::Instance()->Stop(AUDIO_HURT);
			GotoGameState(GAME_STATE_OVER);
		}
		if (knight.isWin(&map)) {							// 如果勝利
			CAudio::Instance()->Stop(AUDIO_INGAME);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
			CAudio::Instance()->Stop(AUDIO_MONSTERSTILLALIVE);
			CAudio::Instance()->Stop(AUDIO_JUMP);
			CAudio::Instance()->Stop(AUDIO_SHOOT);
			CAudio::Instance()->Stop(AUDIO_PICK);
			CAudio::Instance()->Stop(AUDIO_SLASH);
			CAudio::Instance()->Stop(AUDIO_HURT);
			level += 1;										// 換下一關
			initialize = 1;									// 需要初始化
			GotoGameState(GAME_STATE_WIN);
		}
		if (monster.hitleft <= 0 || map.x3 <= 385) {
			CAudio::Instance()->Stop(AUDIO_MONSTERSTILLALIVE);
		}
		if(monster.hitleft>0 && monster.isHit)
			CAudio::Instance()->Play(AUDIO_HOWL, false);
		if (knight.isTouch)
			CAudio::Instance()->Play(AUDIO_HURT, false);
	}

	void CGameStateRun::OnInit()
	{
		ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
		CAudio::Instance()->Load(AUDIO_INGAME, "sounds\\inGame.wav");
		CAudio::Instance()->Load(AUDIO_FOOTSTEPS, "sounds\\footsteps.wav");
		CAudio::Instance()->Load(AUDIO_JUMP, "sounds\\jump.wav");
		CAudio::Instance()->Load(AUDIO_MONSTERSTILLALIVE, "sounds\\monsterStillAlive.wav");
		CAudio::Instance()->Load(AUDIO_PICK, "sounds\\pick.wav");
		CAudio::Instance()->Load(AUDIO_SHOOT, "sounds\\shoot.wav");
		CAudio::Instance()->Load(AUDIO_HOWL, "sounds\\howl.wav");
		CAudio::Instance()->Load(AUDIO_SLASH, "sounds\\slash.wav");
		CAudio::Instance()->Load(AUDIO_HURT, "sounds\\hurt.wav");
		map.LoadBitmap();
		knight.LoadBitmap();
		monster.LoadBitmap();
		weapon.LoadBitmap();
		tomb.LoadBitmap(IDB_TOMB1, RGB(255, 255, 255));
	}

	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25;  // keyboard左箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char SPACE = 0x20;	 // keyboard空白鍵
		const char A = 0x41;		 // keyboard A
		const char S = 0x53;		 // keyboard S
		const char D = 0x44;		 // keyboard D
		const char F = 0x46;		 // keyboard F	
		const char ESC = 0x1B;		 // keyboard ESC
		const char Z = 0x5A;		 // keyboard Z
		const char O = 0x4F;		 // keyboard O
		const char P = 0x50;		 // keyboard P

		if (nChar == KEY_LEFT) {
			if (map.messageTimer >= 80 || map.messageTimer < 0) { // 顯示訊息時不能動
				knight.SetMovingLeft(true);
				CAudio::Instance()->Play(AUDIO_FOOTSTEPS, true);
			}
		}
		if (nChar == KEY_RIGHT) {
			if (map.messageTimer >= 80 || map.messageTimer < 0) { // 顯示訊息時不能動
				knight.SetMovingRight(true);
				CAudio::Instance()->Play(AUDIO_FOOTSTEPS, true);
			}
		}
		if (nChar == SPACE) {
			if (knight.velocity == 15) {		//當角色到地面時才能再跳
				CAudio::Instance()->Play(AUDIO_JUMP, false);
				knight.SetJumping(true);
			}
		}
		if (nChar == A) {
			CAudio::Instance()->Play(AUDIO_SLASH, true);
			knight.SetAttacking(true);
		}
		if (nChar == S) {
			if (!weapon.isShootingLeft && !weapon.isShootingRight) { //當左右射擊都結束時
				weapon.Initialize(&knight);
				weapon.SetShootingLeft(true);
				CAudio::Instance()->Play(AUDIO_SHOOT, false);
			}
		}
		if (nChar == D) {
			if (!weapon.isShootingLeft && !weapon.isShootingRight) { //當左右射擊都結束時
				weapon.Initialize(&knight);
				weapon.SetShootingRight(true);
				CAudio::Instance()->Play(AUDIO_SHOOT, false);
			}
		}
		if (nChar == F) {
			CAudio::Instance()->Play(AUDIO_PICK, false);
			knight.SetCatch(true);
		}
		if (nChar == ESC) {
			knight.isMovingLeft = knight.isMovingRight = false;
			GotoGameState(GAME_STATE_PAUSE);
		}
		if (map.flowerIsCatch) {
			if (nChar == Z) {
				knight.SetMovingFast(true);
				map.SetMovingFast(true);
			}
		}
		if (nChar == P) { // 作弊按鈕
			CAudio::Instance()->Stop(AUDIO_INGAME);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
			CAudio::Instance()->Stop(AUDIO_MONSTERSTILLALIVE);
			CAudio::Instance()->Stop(AUDIO_JUMP);
			CAudio::Instance()->Stop(AUDIO_SHOOT);
			CAudio::Instance()->Stop(AUDIO_PICK);
			CAudio::Instance()->Stop(AUDIO_SLASH);
			level += 1;										// 換下一關
			initialize = 1;									// 需要初始化
			GotoGameState(GAME_STATE_WIN);
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_RIGHT = 0x27;// keyboard右箭頭
		const char SPACE = 0x20;	// keyboard空白鍵
		const char A = 0x41;		// keyboard A
		const char F = 0x46;		// keyboard F
		const char Z = 0x5A;		// keyboard Z
		if (nChar == KEY_LEFT) {
			knight.SetMovingLeft(false);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);

		}
		if (nChar == KEY_RIGHT) {
			knight.SetMovingRight(false);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);

		}
		if (nChar == A) {
			CAudio::Instance()->Stop(AUDIO_SLASH);
			knight.SetAttacking(false);
		}
		if (nChar == F) {
			knight.SetCatch(false);
		}
		if (nChar == Z) {
			knight.SetMovingFast(false);
			map.SetMovingFast(false);
		}
	}

	void CGameStateRun::OnShow()
	{
		map.OnShow();						// 顯示地圖
		if (monster.hitleft <= 0) {
			tomb.SetTopLeft(monster.M_x, monster.M_y);
			tomb.ShowBitmap();				// 顯示墳墓
		}
		knight.OnShow();					// 顯示knight
		weapon.OnShow();					// 顯示武器
		monster.SetisHit(&weapon);			// 偵測是否被攻擊中
		monster.OnShow();					// 顯示怪物
	}

	///////////////////////////////////////////////////////////////////////////// 
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////
	CGameStateRun1::CGameStateRun1(CGame *g)
		: CGameState(g)
	{

	}

	CGameStateRun1::~CGameStateRun1()
	{

	}

	void CGameStateRun1::OnBeginState()
	{
		CAudio::Instance()->Play(AUDIO_INGAME2, true);
		if (initialize == 1) {				// 如果需要初始化
			knight.Initialize();			// 主角初始化
			map.Initialize(level);			// 地圖初始化
			weapon.Initialize(&knight);		// 武器初始化
			monster.Initialize(level);
			initialize = 0;
		}
	}

	void CGameStateRun1::OnMove()							// 移動遊戲元素
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));		// 鼠標
		map.OnMove(&knight);								// 地圖
		knight.OnMove(&map);								// 主角
		weapon.OnMove(&knight);								// 武器
		monster.OnMove(&knight, &map);						// 怪物
		knight.SetTouchFire(&monster);						// 主角是否被火球砸到
		knight.SetTouchMonster2(&monster);					// 主角是否被怪物碰到

		if (knight.isDeath(&map)) {							// 如果角色死亡		
			initialize = 1;									// 需要初始化
			CAudio::Instance()->Stop(AUDIO_INGAME2);
			CAudio::Instance()->Stop(AUDIO_JUMP);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
			CAudio::Instance()->Stop(AUDIO_SHOOT);
			CAudio::Instance()->Stop(AUDIO_PICK);
			CAudio::Instance()->Stop(AUDIO_SLASH);
			CAudio::Instance()->Stop(AUDIO_HITFOOD);
			CAudio::Instance()->Stop(AUDIO_HURT);
			GotoGameState(GAME_STATE_OVER);
		}
		if (map.messageTimer1==-1) {						// 跳到第二關的魔王state
			initialize = 1;									// 需要初始化
			CAudio::Instance()->Stop(AUDIO_INGAME2);
			CAudio::Instance()->Stop(AUDIO_JUMP);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
			CAudio::Instance()->Stop(AUDIO_SHOOT);
			CAudio::Instance()->Stop(AUDIO_PICK);
			CAudio::Instance()->Stop(AUDIO_SLASH);
			CAudio::Instance()->Stop(AUDIO_HITFOOD);
			CAudio::Instance()->Stop(AUDIO_HURT);
			level += 1;
			GotoGameState(GAME_STATE_RUN1_2);
		}
		if (map.foodLife == 59|| map.foodLife == 50 || map.foodLife == 40 || map.foodLife == 30 || 
			map.foodLife == 20 || map.foodLife == 10 || map.foodLife == 0) {
			CAudio::Instance()->Play(AUDIO_HITFOOD,false);
		}
		if (knight.isBurn)
			CAudio::Instance()->Play(AUDIO_HURT, false);
	}

	void CGameStateRun1::OnInit()  							// 遊戲的初值及圖形設定
	{
		ShowInitProgress(44);	// 接個前一個狀態的進度，此處進度視為44%
		CAudio::Instance()->Load(AUDIO_HITFOOD, "sounds\\hitFood.wav");
		CAudio::Instance()->Load(AUDIO_INGAME2, "sounds\\inGame2.wav");
		map.LoadBitmap();
		knight.LoadBitmap();
		weapon.LoadBitmap();
		monster.LoadBitmap();
	}

	void CGameStateRun1::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25;		// keyboard左箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		const char SPACE = 0x20;		// keyboard空白鍵
		const char A = 0x41;			// keyboard A
		const char S = 0x53;			// keyboard S
		const char D = 0x44;			// keyboard D
		const char F = 0x46;			// keyboard F
		const char ESC = 0x1B;			// keyboard ESC
		const char Z = 0x5A;			// keyboard SHIFT
		const char O = 0x4F;			// keyboard O
		const char P = 0x50;			// keyboard P

		if (nChar == KEY_LEFT) {
			if (map.messageTimerJ >= 80 || map.messageTimerJ < 0) { // 顯示訊息時不能動
				knight.SetMovingLeft(true);
				CAudio::Instance()->Play(AUDIO_FOOTSTEPS, true);
			}
		}
		if (nChar == KEY_RIGHT) {
			if (map.messageTimerJ >= 80 || map.messageTimerJ < 0) { // 顯示訊息時不能動
				knight.SetMovingRight(true);
				CAudio::Instance()->Play(AUDIO_FOOTSTEPS, true);
			}
		}
		if (nChar == SPACE) {
			if (map.flower1IsCatch) {
				if (knight.velocity != 15 && canDoubleJump) { //騰空時可以二段跳
					CAudio::Instance()->Play(AUDIO_JUMP, false);
					canDoubleJump = false;
					knight.velocity = 15;
					knight.SetJumping(true);
				}
				else if (knight.velocity == 15) {		//當角色到地面時才能再跳
					canDoubleJump = true;
					CAudio::Instance()->Play(AUDIO_JUMP, false);
					knight.SetJumping(true);
				}
			}
			else {
				if (knight.velocity == 15) {		//當角色到地面時才能再跳
					CAudio::Instance()->Play(AUDIO_JUMP, false);
					knight.SetJumping(true);
				}
			}
		}
		if (nChar == A) {
			CAudio::Instance()->Play(AUDIO_SLASH, true);
			knight.SetAttacking(true);
		}
		if (nChar == S) {
			if (!weapon.isShootingLeft && !weapon.isShootingRight) { //當左右射擊都結束時
				weapon.Initialize(&knight);
				weapon.SetShootingLeft(true);
				CAudio::Instance()->Play(AUDIO_SHOOT, false);
			}
		}
		if (nChar == D) {
			if (!weapon.isShootingLeft && !weapon.isShootingRight) { //當左右射擊都結束時
				weapon.Initialize(&knight);
				weapon.SetShootingRight(true);
				CAudio::Instance()->Play(AUDIO_SHOOT, false);
			}
		}
		if (nChar == F) {
			CAudio::Instance()->Play(AUDIO_PICK, false);
			knight.SetCatch(true);
		}
		if (nChar == ESC) {
			knight.isMovingLeft = knight.isMovingRight = false;
			GotoGameState(GAME_STATE_PAUSE);
		}
		if (nChar == Z) {
			knight.SetMovingFast(true);
			map.SetMovingFast(true);
		}
		if (nChar == O) { // 作弊按鈕
			knight.lifeLeft += 40;
		}
		if (nChar == P) { // 作弊按鈕
			CAudio::Instance()->Stop(AUDIO_INGAME2);
			CAudio::Instance()->Stop(AUDIO_JUMP);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
			CAudio::Instance()->Stop(AUDIO_SHOOT);
			CAudio::Instance()->Stop(AUDIO_PICK);
			CAudio::Instance()->Stop(AUDIO_SLASH);
			CAudio::Instance()->Stop(AUDIO_HITFOOD);
			CAudio::Instance()->Stop(AUDIO_HURT);
			initialize = 1;
			level = 2;
			GotoGameState(GAME_STATE_RUN1_2);
		}
	}

	void CGameStateRun1::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25;		// keyboard左箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		const char SPACE = 0x20;		// keyboard空白鍵
		const char A = 0x41;			// keyboard A
		const char S = 0x53;			// keyboard S
		const char D = 0x44;			// keyboard D
		const char F = 0x46;			// keyboard F
		const char Z = 0x5A;			// keyboard SHIFT
		if (nChar == KEY_LEFT) {
			knight.SetMovingLeft(false);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
		}
		if (nChar == KEY_RIGHT) {
			knight.SetMovingRight(false);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
		}
		if (nChar == A) {
			CAudio::Instance()->Stop(AUDIO_SLASH);
			knight.SetAttacking(false);
		}
		if (nChar == F) {
			knight.SetCatch(false);
		}
		if (nChar == Z) {
			knight.SetMovingFast(false);
			map.SetMovingFast(false);
		}
	}

	void CGameStateRun1::OnShow()
	{
		map.OnShow();						// 顯示地圖
		if(map.x8>0)
			knight.OnShow();				// 顯示knight
		weapon.OnShow();
		monster.OnShow();
	}

	///////////////////////////////////////////////////////////////////////////// 
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////
	CGameStateRun1_2::CGameStateRun1_2(CGame *g)
		:CGameState(g)
	{

	}

	CGameStateRun1_2::~CGameStateRun1_2()
	{

	}

	void CGameStateRun1_2::OnBeginState()
	{
		CAudio::Instance()->Play(AUDIO_FINALBOSS, true);
		if (initialize == 1) {				// 如果需要初始化
			weapon.Initialize(&knight);		// 武器初始化
			knight.Initialize();			// 主角初始化
			map.Initialize(level);			// 地圖初始化
			monster.Initialize(level);		// 怪物初始化
			initialize = 0;
		}
	}

	void CGameStateRun1_2::OnInit()
	{
		ShowInitProgress(55);	// 接個前一個狀態的進度，此處進度視為55%
		CAudio::Instance()->Load(AUDIO_FINALBOSS, "sounds\\finalBoss.wav");
		map.LoadBitmap();
		knight.LoadBitmap();
		weapon.LoadBitmap();
		monster.LoadBitmap();
		tomb.LoadBitmap(IDB_TOMB1,RGB(255, 255, 255));
	}

	void CGameStateRun1_2::OnMove()
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));		// 鼠標
		map.OnMove(&knight);
		knight.OnMove(&map);
		knight.SetTouchMonster2(&monster);					// 主角是否被怪物碰到
		weapon.OnMove(&knight);
		monster.OnMove(&knight, &map);
		monster.SetisHit(&weapon);							// 怪物被武器碰到
		if (knight.lifeLeft < 0) {							// 如果主角血量<0, 失敗
			level = 1;										// 回到第二關
			initialize = 1;
			CAudio::Instance()->Stop(AUDIO_FINALBOSS);
			CAudio::Instance()->Stop(AUDIO_JUMP);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
			CAudio::Instance()->Stop(AUDIO_SHOOT);
			CAudio::Instance()->Stop(AUDIO_PICK);
			CAudio::Instance()->Stop(AUDIO_SLASH);
			CAudio::Instance()->Stop(AUDIO_HITFOOD);
			CAudio::Instance()->Stop(AUDIO_HURT);
			GotoGameState(GAME_STATE_OVER);
		}
		if (monster.hitleft <= 0 && !weapon.isShootingLeft && !weapon.isShootingRight) {							// 如果怪物血量<0, 勝利
			level = 0;										// 下一關轉成第一關
			initialize = 1;									// 需要初始化
			CAudio::Instance()->Stop(AUDIO_FINALBOSS);
			CAudio::Instance()->Stop(AUDIO_JUMP);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
			CAudio::Instance()->Stop(AUDIO_SHOOT);
			CAudio::Instance()->Stop(AUDIO_PICK);
			CAudio::Instance()->Stop(AUDIO_SLASH);
			CAudio::Instance()->Stop(AUDIO_HITFOOD);
			CAudio::Instance()->Stop(AUDIO_HURT);
			Sleep(1500);
			GotoGameState(GAME_STATE_END);
		}
		if (knight.isTouch2)
			CAudio::Instance()->Play(AUDIO_HURT, false);
	}

	void CGameStateRun1_2::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25;		// keyboard左箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		const char SPACE = 0x20;		// keyboard空白鍵
		const char A = 0x41;			// keyboard A
		const char S = 0x53;			// keyboard S
		const char D = 0x44;			// keyboard D
		const char F = 0x46;			// keyboard F
		const char ESC = 0x1B;			// keyboard ESC
		const char O = 0x4F;			// keyboard O
		const char P = 0x50;			// keyboard P
		const char Z = 0x5A;			// keyboard Z

		if (nChar == KEY_LEFT) {
			knight.SetMovingLeft(true);
			CAudio::Instance()->Play(AUDIO_FOOTSTEPS, true);
		}
		if (nChar == KEY_RIGHT) {
			knight.SetMovingRight(true);
			CAudio::Instance()->Play(AUDIO_FOOTSTEPS, true);
		}
		if (nChar == SPACE) {
			if (knight.velocity != 15 && canDoubleJump) { //騰空時可以二段跳
				CAudio::Instance()->Play(AUDIO_JUMP, false);
				canDoubleJump = false;
				knight.velocity = 15;
				knight.SetJumping(true);
			}
			else if (knight.velocity == 15) {		//當角色到地面時才能再跳
				canDoubleJump = true;
				CAudio::Instance()->Play(AUDIO_JUMP, false);
				knight.SetJumping(true);
			}
		}
		if (nChar == A) {
			CAudio::Instance()->Play(AUDIO_SLASH, true);
			knight.SetAttacking(true);
		}
		if (nChar == S) {
			if (!weapon.isShootingLeft && !weapon.isShootingRight) { //當左右射擊都結束時
				weapon.Initialize(&knight);
				weapon.SetShootingLeft(true);
				CAudio::Instance()->Play(AUDIO_SHOOT, false);
			}
		}
		if (nChar == D) {
			if (!weapon.isShootingLeft && !weapon.isShootingRight) { //當左右射擊都結束時
				weapon.Initialize(&knight);
				weapon.SetShootingRight(true);
				CAudio::Instance()->Play(AUDIO_SHOOT, false);
			}
		}
		if (nChar == F) {
			CAudio::Instance()->Play(AUDIO_PICK, false);
			knight.SetCatch(true);
		}
		if (nChar == ESC) {
			knight.isMovingLeft = knight.isMovingRight = false;
			GotoGameState(GAME_STATE_PAUSE);
		}
		if (nChar == O) { // 作弊按鈕
			knight.lifeLeft += 40;
		}
		if (nChar == P) { // 作弊按鈕
			monster.hitleft = 10;
		}
		if (nChar == Z) {
			knight.SetMovingFast(true);
			map.SetMovingFast(true);
		}
	}

	void CGameStateRun1_2::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25;		// keyboard左箭頭
		const char KEY_RIGHT = 0x27;	// keyboard右箭頭
		const char SPACE = 0x20;		// keyboard空白鍵
		const char A = 0x41;			// keyboard A
		const char S = 0x53;			// keyboard S
		const char D = 0x44;			// keyboard D
		const char F = 0x46;			// keyboard F
		const char Z = 0x5A;			// keyboard Z
		if (nChar == KEY_LEFT) {
			knight.SetMovingLeft(false);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
		}
		if (nChar == KEY_RIGHT) {
			knight.SetMovingRight(false);
			CAudio::Instance()->Stop(AUDIO_FOOTSTEPS);
		}
		if (nChar == A) {
			CAudio::Instance()->Stop(AUDIO_SLASH);
			knight.SetAttacking(false);
		}
		if (nChar == F) {
			knight.SetCatch(false);
		}
		if (nChar == Z) {
			knight.SetMovingFast(false);
			map.SetMovingFast(false);
		}
	}

	void CGameStateRun1_2::OnShow()
	{
		map.OnShow();
		if (monster.hitleft <= 0) {
			tomb.SetTopLeft(monster.M_x, 270);
			tomb.ShowBitmap();
		}
		knight.OnShow();
		if(monster.hitleft>0)
			weapon.OnShow();
		monster.OnShow();
	}

	////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的過關狀態(Game Win)
	////////////////////////////////////////////////////////////////////////////
	CGameStateWin::CGameStateWin(CGame *g)
		:CGameState(g)
	{
		
	}

	void CGameStateWin::OnBeginState()
	{
		CAudio::Instance()->Play(AUDIO_CONGRAT, true);
		isPlayed = false;
	}

	void CGameStateWin::OnInit()
	{
		ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
		CAudio::Instance()->Load(AUDIO_CONGRAT, "sounds\\congrat.wav");
		congrats.LoadBitmap(IDB_HK_CONGRATS);
		congrats1.LoadBitmap(IDB_HK_CONGRATS1);
		congrats2.LoadBitmap(IDB_HK_CONGRATS2);
	}

	void CGameStateWin::OnLButtonDown(UINT nFlag, CPoint point)
	{
		if (point.x > 10 && point.x < 150 && point.y > 415 && point.y < 440) { ///////Click///////
			initialize = 1;													   //   需要初始化   //
			CAudio::Instance()->Stop(AUDIO_CONGRAT);					       //    停止音樂    //
			GotoGameState(GAME_STATE_INIT);									   // Back to Menu  //
		}																	   ///////////////////
		if (point.x > 505 && point.x < 625 && point.y > 415 && point.y < 440) { ///////Click//////
			switch (level) {													//  Next Level  // 
			case 1:																//////////////////
				initialize = 1;													//   需要初始化  //
				GotoGameState(GAME_STATE_RUN1);									//   Level 1    //
				break;															//////////////////
			default:
				initialize = 1;					// 需要初始化
				GotoGameState(GAME_STATE_INIT); // 回主選單
			}
			CAudio::Instance()->Stop(AUDIO_CONGRAT);									  // 停止音樂
		}
	}

	void CGameStateWin::OnMouseMove(UINT nFlag, CPoint point)
	{
		moveMouseX = point.x;
		moveMouseY = point.y;
	}

	void CGameStateWin::OnMove()
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));	// 鼠標
	}

	void CGameStateWin::OnShow()
	{
		congrats.SetTopLeft(0, 0);
		congrats.ShowBitmap();			// 顯示過關選單
		if (moveMouseX > 10 && moveMouseX < 150 && moveMouseY > 415 && moveMouseY < 440) { ////////////////
			congrats1.SetTopLeft(0, 0);													   //    Hover   //
			congrats1.ShowBitmap();														   //Back to Menu//
			if (isPlayed == false) {													   // 如果沒放音效//
				CAudio::Instance()->Play(AUDIO_HOVER);									   //  播放音效   //
				isPlayed = true;														   // 已播放過音效//
			}																			   ////////////////
		}
		else if (moveMouseX > 505 && moveMouseX < 625 && moveMouseY > 415 && moveMouseY < 440) {//////////////// 
			congrats2.SetTopLeft(0, 0);															//    Hover   //
			congrats2.ShowBitmap();																// Next Level //	
			if (isPlayed == false) {															// 如果沒放音效//
				CAudio::Instance()->Play(AUDIO_HOVER);											//  播放音效   //
				isPlayed = true;																// 已播放過音效//
			}																					////////////////
		}
		else
			isPlayed = false;
	}

	////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的暫停狀態(Game Pause)
	////////////////////////////////////////////////////////////////////////////
	CGameStatePause::CGameStatePause(CGame *g)
		:CGameState(g)
	{

	}

	void CGameStatePause::OnBeginState()
	{
		CAudio::Instance()->Pause();
		isPlayed = false;
	}

	void CGameStatePause::OnInit()
	{
		ShowInitProgress(77);	// 接個前一個狀態的進度，此處進度視為77%
		pauseMenu.LoadBitmap(IDB_PAUSEMENU);
		leftsign.LoadBitmap(IDB_LEFTSIGN, RGB(0, 0, 0));
		rightsign.LoadBitmap(IDB_RIGHTSIGN, RGB(0, 0, 0));
	}

	void CGameStatePause::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char ESC = 0x1B; // keyboard ESC

		if (nChar == ESC) {
			switch (level) {
			case 0:
				GotoGameState(GAME_STATE_RUN);
				break;
			case 1:
				GotoGameState(GAME_STATE_RUN1);
				break;
			case 2:
				GotoGameState(GAME_STATE_RUN1_2);
				break;
			}
		}
	}
	
	void CGameStatePause::OnLButtonDown(UINT nFlags, CPoint point)
	{
		mouseX = point.x;
		mouseY = point.y;

		if (point.x > 275 && point.x < 315 && point.y>185 && point.y < 215) { 
			switch (level) {														// 繼續遊戲
			case 0:
				GotoGameState(GAME_STATE_RUN);										// 第一關
				break;
			case 1:
				GotoGameState(GAME_STATE_RUN1);										// 第二關
				break;
			case 2:
				GotoGameState(GAME_STATE_RUN1_2);									// 第二關魔王
				break;
			}																		
		}
		else if (point.x > 245 && point.x < 350 && point.y>260 && point.y < 300) {
			initialize = 1;	//需要初始化	
			if (level == 2)
				level = 1;
			GotoGameState(GAME_STATE_INIT);											 // 回主選單
		}
	}

	void CGameStatePause::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		moveMouseX = point.x;	//取得滑鼠X座標
		moveMouseY = point.y;	//取得滑鼠Y座標
	}

	void CGameStatePause::OnMove()
	{
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR));		// 滑鼠樣式

	}

	void CGameStatePause::OnShow()
	{
		pauseMenu.ShowBitmap();								// 顯示暫停選單
		if (moveMouseX > 275 && moveMouseX < 315 && moveMouseY > 185 && moveMouseY < 215) {
			leftsign.SetTopLeft(220, 170);
			leftsign.ShowBitmap();
			rightsign.SetTopLeft(300, 170);
			rightsign.ShowBitmap();
			if (isPlayed == false) {
				CAudio::Instance()->Play(AUDIO_HOVER, false);
				isPlayed = true;						    // 已經撥放過音效
			}
		}
		else if (moveMouseX > 245 && moveMouseX < 350 && moveMouseY > 260 && moveMouseY < 300) {
			leftsign.SetTopLeft(190, 245);
			leftsign.ShowBitmap();
			rightsign.SetTopLeft(330, 245);
			rightsign.ShowBitmap();
			if (isPlayed == false) {
				CAudio::Instance()->Play(AUDIO_HOVER, false);
				isPlayed = true;							// 已經撥放過音效
			}
		}
		else {
			isPlayed = false;
		}
	}

	////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的選擇狀態(Game Select)
	////////////////////////////////////////////////////////////////////////////

	CGameStateSelect::CGameStateSelect(CGame *g)
		:CGameState(g)
	{
		xMonster = 200, yMonster = 300, dMonster = 0;
		isPlayed = false;
	}

	void CGameStateSelect::OnBeginState()
	{

	}

	void CGameStateSelect::OnInit()
	{
		ShowInitProgress(88);	// 接個前一個狀態的進度，此處進度視為88%
		level3.LoadBitmap(IDB_LEVEL3);								// 載入關卡3
		preview.LoadBitmap(IDB_PREVIEW, RGB(255, 255, 255));		// 載入預覽字樣
		backToMenu1.LoadBitmap(IDB_BACKTOMENU1, RGB(0, 0, 0));		// 返回選單
		backToMenu2.LoadBitmap(IDB_BACKTOMENU2, RGB(0, 0, 0));		// hover返回選單
		monster1.LoadBitmap(IDB_MONSTER1);
		monster3.LoadBitmap(IDB_MONSTER3);
		char *filename1[3] = { ".\\bitmaps\\HK_monster1_1.bmp",".\\bitmaps\\HK_monster1_2.bmp",".\\bitmaps\\HK_monster1_3.bmp" };
		for (int i = 0; i < 3; i++)
			Monster1.AddBitmap(filename1[i], RGB(255, 255, 255));
		char *filename2[3] = { ".\\bitmaps\\HK_monster3_1.bmp",".\\bitmaps\\HK_monster3_2.bmp",".\\bitmaps\\HK_monster3_3.bmp" };
		for (int i = 0; i < 3; i++)
			Monster3.AddBitmap(filename2[i], RGB(255, 255, 255));
	}

	void CGameStateSelect::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
	{
		if (120 < point.x && point.x < 150 && 70 < point.y && point.y < 110) {
			CAudio::Instance()->Stop(AUDIO_MENU);
			level = 0;																// 選擇第一關
			initialize = 1;															// 需要初始化
			GotoGameState(GAME_STATE_RUN);
		}
		else if (190 < point.x && point.x < 230 && 70 < point.y && point.y < 110) {
			CAudio::Instance()->Stop(AUDIO_MENU);
			level = 1;																// 選擇第二關
			initialize = 1;															// 需要初始化
			GotoGameState(GAME_STATE_RUN1);
		}
		else if (270 < moveMouseX && moveMouseX < 310 && 70 < moveMouseY && moveMouseY < 110) {
			CAudio::Instance()->Stop(AUDIO_MENU);
			level = 2;																// 選擇第三關
			initialize = 1;															// 需要初始化
			GotoGameState(GAME_STATE_RUN1_2);
		}
		else if (0 < point.x && point.x < 160 && 420 < point.y && point.y < 480) {
			GotoGameState(GAME_STATE_INIT);
		}
	}

	void CGameStateSelect::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		moveMouseX = point.x;	//取得滑鼠X座標
		moveMouseY = point.y;	//取得滑鼠Y座標
	}

	void CGameStateSelect::OnMove() {
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR)); // 鼠標
		// Level1怪物動畫
		if (dMonster == 0) {
			xMonster += 2;
			if (xMonster > 400) {
				dMonster = 1;
			}
		}
		else {
			xMonster -= 2;
			if (xMonster < 200) {
				dMonster = 0;
			}
		}
		//Level2怪物動畫
		Monster1.OnMove();
		Monster3.OnMove();
	}

	void CGameStateSelect::OnShow() {
		level3.SetTopLeft(0, 0);
		level3.ShowBitmap();
		backToMenu1.SetTopLeft(0, 420);
		backToMenu1.ShowBitmap();
		if (120 < moveMouseX && moveMouseX < 150 && 70 < moveMouseY && moveMouseY < 110) {      // 第一關
			// hover音效
			if (isPlayed == false) {
				CAudio::Instance()->Play(AUDIO_HOVER, false);
				isPlayed = true;
			}
			// 預覽怪物
			preview.SetTopLeft(100, 150);
			preview.ShowBitmap();
			if (dMonster == 0) {
				monster3.SetTopLeft(xMonster, yMonster);
				monster3.ShowBitmap();
			}
			else {
				monster1.SetTopLeft(xMonster, yMonster);
				monster1.ShowBitmap();
			}
		}
		else if (190 < moveMouseX && moveMouseX < 230 && 70 < moveMouseY && moveMouseY < 110) { // 第二關
			// hover音效
			if (isPlayed == false) {
				CAudio::Instance()->Play(AUDIO_HOVER, false);
				isPlayed = true;
			}
			// 預覽怪物
			preview.SetTopLeft(100, 150);
			preview.ShowBitmap();
			if (dMonster == 0) {
				Monster3.SetTopLeft(xMonster, yMonster-50);
				Monster3.OnShow();
			}
			else {
				Monster1.SetTopLeft(xMonster, yMonster-50);
				Monster1.OnShow();
			}
		}
		else if (270 < moveMouseX && moveMouseX < 310 && 70 < moveMouseY && moveMouseY < 110) { // 第三關
			// hover音效
			if (isPlayed == false) {
				CAudio::Instance()->Play(AUDIO_HOVER, false);
				isPlayed = true;
			}
			// 預覽怪物
		}
		else if (0 < moveMouseX && moveMouseX < 160 && 420 < moveMouseY && moveMouseY < 480) { //Back To Menu
			// hover音效
			if (isPlayed == false) {
				CAudio::Instance()->Play(AUDIO_HOVER, false);
				isPlayed = true;
			}
			backToMenu2.SetTopLeft(0, 420);
			backToMenu2.ShowBitmap();
		}
		else {
			isPlayed = false;
		}
	}

	////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的選擇狀態(Game Select)
	////////////////////////////////////////////////////////////////////////////

	CGameStateEnd::CGameStateEnd(CGame *g)
		:CGameState(g) 
	{
		isPlayed = false;
	}

	void CGameStateEnd::OnBeginState() {
		CAudio::Instance()->Play(AUDIO_END, true);
		timer1 = 110;
		timer2 = 190;
		char *filename[39] = {
			".\\bitmaps\\END1.bmp",".\\bitmaps\\END2.bmp",
			".\\bitmaps\\END3.bmp",".\\bitmaps\\END4.bmp",
			".\\bitmaps\\END5.bmp",".\\bitmaps\\END6.bmp",
			".\\bitmaps\\END7.bmp",".\\bitmaps\\END8.bmp",
			".\\bitmaps\\END9.bmp",".\\bitmaps\\END10.bmp",
			".\\bitmaps\\END11.bmp",".\\bitmaps\\END12.bmp",
			".\\bitmaps\\END13.bmp",".\\bitmaps\\END14.bmp",
			".\\bitmaps\\END15.bmp",".\\bitmaps\\END16.bmp",
			".\\bitmaps\\END17.bmp",".\\bitmaps\\END18.bmp",
			".\\bitmaps\\END19.bmp",".\\bitmaps\\END20.bmp",
			".\\bitmaps\\END21.bmp",".\\bitmaps\\END22.bmp",
			".\\bitmaps\\END23.bmp",".\\bitmaps\\END24.bmp",
			".\\bitmaps\\END25.bmp",".\\bitmaps\\END26.bmp",
			".\\bitmaps\\END27.bmp",".\\bitmaps\\END28.bmp",
			".\\bitmaps\\END29.bmp",".\\bitmaps\\END30.bmp",
			".\\bitmaps\\END31.bmp",".\\bitmaps\\END32.bmp",
			".\\bitmaps\\END33.bmp",".\\bitmaps\\END34.bmp",
			".\\bitmaps\\END35.bmp",".\\bitmaps\\END36.bmp",
			".\\bitmaps\\END37.bmp",".\\bitmaps\\END38.bmp",
			".\\bitmaps\\END39.bmp" };
		for (int i = 0; i < 39; i++)// 載入結束動畫(由39張圖形構成)
			end1.AddBitmap(filename[i]);
		char *filename1[31] = {
			".\\bitmaps\\END_2_01.bmp",
			".\\bitmaps\\END_2_02.bmp", ".\\bitmaps\\END_2_03.bmp",
			".\\bitmaps\\END_2_04.bmp", ".\\bitmaps\\END_2_05.bmp",
			".\\bitmaps\\END_2_06.bmp", ".\\bitmaps\\END_2_07.bmp",
			".\\bitmaps\\END_2_08.bmp", ".\\bitmaps\\END_2_09.bmp",
			".\\bitmaps\\END_2_10.bmp", ".\\bitmaps\\END_2_11.bmp",
			".\\bitmaps\\END_2_12.bmp", ".\\bitmaps\\END_2_13.bmp",
			".\\bitmaps\\END_2_14.bmp", ".\\bitmaps\\END_2_15.bmp",
			".\\bitmaps\\END_2_16.bmp", ".\\bitmaps\\END_2_17.bmp",
			".\\bitmaps\\END_2_18.bmp", ".\\bitmaps\\END_2_19.bmp",
			".\\bitmaps\\END_2_20.bmp", ".\\bitmaps\\END_2_21.bmp",
			".\\bitmaps\\END_2_22.bmp", ".\\bitmaps\\END_2_23.bmp",
			".\\bitmaps\\END_2_24.bmp", ".\\bitmaps\\END_2_25.bmp",
			".\\bitmaps\\END_2_26.bmp", ".\\bitmaps\\END_2_27.bmp",
			".\\bitmaps\\END_2_28.bmp", ".\\bitmaps\\END_2_29.bmp",
			".\\bitmaps\\END_2_30.bmp", ".\\bitmaps\\END_2_31.bmp", };
		for (int i = 0; i < 31; i++)// 載入結束動畫(由31張圖形構成)
			end2.AddBitmap(filename1[i]);
	}

	void CGameStateEnd::OnInit() {
		ShowInitProgress(100);	// 接個前一個狀態的進度，此處進度視為100%
		CAudio::Instance()->Load(AUDIO_END, "sounds\\end.wav");
		endMenu1.LoadBitmap(IDB_ENDMENU1);
		endMenu2.LoadBitmap(IDB_ENDMENU2);
		endMenu3.LoadBitmap(IDB_ENDMENU3);
	}

	void CGameStateEnd::OnLButtonDown(UINT nFlags, CPoint point) // 處理滑鼠的動作
	{
		if (timer2 <= 0) {
			if (point.y > 430 && point.y < 460 && point.x > 20 && point.x < 105) { // back to menu
				CAudio::Instance()->Stop(AUDIO_END);
				GotoGameState(GAME_STATE_INIT);
			}
			else if (point.y > 430 && point.y < 460 && point.x > 540 && point.x < 605) { // quit game
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
			}
		}
	}

	void CGameStateEnd::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		moveMouseX = point.x;										//取得滑鼠X座標
		moveMouseY = point.y;										//取得滑鼠Y座標
	}

	void CGameStateEnd::OnMove() {
		SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR)); // 鼠標
		end1.OnMove2();
		end2.OnMove();
		if (timer1 > 0) {
			timer1--;
		}
		else if (timer1 == 0) {
			timer2--;
		}
		
	}

	void CGameStateEnd::OnShow() {
		if (timer2 <= 0) {
			if (moveMouseY > 430 && moveMouseY < 460 && moveMouseX > 20 && moveMouseX < 105) { // back to menu
				// hover音效
				if (isPlayed == false) {
					CAudio::Instance()->Play(AUDIO_HOVER, false);
					isPlayed = true;
				}
				// 顯示圖片
				endMenu2.SetTopLeft(0, 0);
				endMenu2.ShowBitmap();
			}
			else if (moveMouseY > 430 && moveMouseY < 460 && moveMouseX > 540 && moveMouseX < 605) { // quit game
				// hover音效
				if (isPlayed == false) {
					CAudio::Instance()->Play(AUDIO_HOVER, false);
					isPlayed = true;
				}
				// 顯示圖片
				endMenu3.SetTopLeft(0, 0);
				endMenu3.ShowBitmap();
			}
			else {
				isPlayed = false;
				endMenu1.SetTopLeft(0, 0);
				endMenu1.ShowBitmap();
			}
		}
		else if (timer1 == 0) {
			end2.SetTopLeft(0, 0);
			end2.OnShow();
		}
		else if (timer1 > 0) {
			end1.SetTopLeft(0, 0);
			end1.OnShow();
		}
	}
}
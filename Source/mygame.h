#include "CKnight.h"
#include "CMap.h"
#include "CMonster.h"
#include "CWeapon.h"
#include "CMonster2.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_MENU,				// 0
		AUDIO_INGAME,			// 1
		AUDIO_FOOTSTEPS	,		// 2
		AUDIO_JUMP,				// 3
		AUDIO_HOVER,			// 4
		AUDIO_MONSTERSTILLALIVE,// 5
		AUDIO_PICK,				// 6
		AUDIO_CONGRAT,			// 7
		AUDIO_SHOOT,			// 8
		AUDIO_HOWL,				// 9
		AUDIO_SLASH,			// 10
		AUDIO_HITFOOD,			// 11
		AUDIO_HURT,				// 12
		AUDIO_INGAME2,			// 13
		AUDIO_FINALBOSS,		// 14
		AUDIO_END				// 15
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		int downMouseX, downMouseY;						// 滑鼠按下位置
		int moveMouseX, moveMouseY;						// 滑鼠移動位置
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap menu;								// hollow knight的選單
		CMovingBitmap leftsign;							// 選單左符號
		CMovingBitmap rightsign;						// 選單右符號
		CMovingBitmap control;							// 按鍵設置圖
		CMovingBitmap backToMenu1, backToMenu2;			// 返回選單
		CMovingBitmap scroll1, scroll2;					// 卷軸
		CMovingBitmap skills;							// 密技圖
		bool		  isMusicLoaded;					// 是否已經載入音樂
		bool		  isPlayed;							// 是否播放過音效
		bool		  showingCtrl;						// 正在show按鍵設置圖
		bool		  showingSkill;						// 正在show密技圖
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的第1關
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);				// 處理鍵盤Down的動作
		void OnKeyUp(UINT, UINT, UINT);					// 處理鍵盤Up的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap	tomb;		// 墳墓
		CMonster        monster;    // 怪物
		CKnight			knight;		// 主角
		CMap			map;		// 地圖
		CWeapon			weapon;		// 武器
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的第2關
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun1 : public CGameState {
	public:
		CGameStateRun1(CGame *g);
		~CGameStateRun1();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);				// 處理鍵盤Down的動作
		void OnKeyUp(UINT, UINT, UINT);					// 處理鍵盤Up的動作
		int downMouseX, downMouseY;						// 滑鼠按下位置
		int moveMouseX, moveMouseY;						// 滑鼠移動位置
		bool canDoubleJump;								// 可以二段跳
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMonster2       monster;    // 怪物
		CKnight			knight;		// 主角
		CMap			map;		// 地圖
		CWeapon			weapon;		// 武器
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲第2關的魔王
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun1_2 : public CGameState {
	public:
		CGameStateRun1_2(CGame *g);
		~CGameStateRun1_2();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);				// 處理鍵盤Down的動作
		void OnKeyUp(UINT, UINT, UINT);					// 處理鍵盤Up的動作
		bool canDoubleJump;								// 可以二段跳
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap	tomb;		// 墳墓
		CMap			map;		// 地圖
		CMonster2       monster;    // 怪物
		CKnight			knight;		// 主角
		CWeapon			weapon;		// 武器
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的過關狀態(Game Win)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateWin : public CGameState {
	public:
		CGameStateWin(CGame *g);
		void OnBeginState();
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		int moveMouseX, moveMouseY;						// 滑鼠移動位置
		bool isPlayed;									// 是否播放過音效
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap   congrats;						// 過關選單
		CMovingBitmap	congrats1;						// 過關選單->回主選單
		CMovingBitmap	congrats2;						// 過關選單->下一關
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int counter;									// 倒數之計數器
		CMovingBitmap gameover;							// 結束圖示
	};

	////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的暫停狀態(Game Pause)
	////////////////////////////////////////////////////////////////////////////

	class CGameStatePause : public CGameState {
	public:
		CGameStatePause(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();									// 載入圖片(LoadBitmap)
		void OnKeyDown(UINT, UINT, UINT);				// 處理鍵盤Down的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		int moveMouseX, moveMouseY;						// 滑鼠移動位置
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CPoint mouseX, mouseY;							// 滑鼠座標
		CMovingBitmap pauseMenu;						// 暫停選單
		CMovingBitmap leftsign;							// 選單左符號
		CMovingBitmap rightsign;						// 選單右符號
		bool		  isPlayed;							// 是否播放過音效
	};

	////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的選擇狀態(Game Select)
	////////////////////////////////////////////////////////////////////////////

	class CGameStateSelect : public CGameState {
	public:
		CGameStateSelect(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();									// 載入圖片(LoadBitmap)
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		int moveMouseX, moveMouseY;						// 滑鼠移動位置
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap level1, level2, level3;			// 關卡圖
		CMovingBitmap preview;							// 預覽字樣
		CMovingBitmap backToMenu1, backToMenu2;			// 返回選單
		CMovingBitmap monster1, monster3;				// 預覽怪物
		CAnimation	  Monster1, Monster3;				// 預覽座標
		int xMonster, yMonster, dMonster;				// 怪物座標
		int XMonster, YMonster, DMonster;				// 怪物座標
		bool		  isPlayed;							// 是否播放過音效
	};

	////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的完結狀態(Game End)
	////////////////////////////////////////////////////////////////////////////
	class CGameStateEnd : public CGameState {
	public:
		CGameStateEnd(CGame *g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();									// 載入圖片(LoadBitmap)
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		int moveMouseX, moveMouseY;						// 滑鼠移動位置
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		int timer1;
		int timer2;
		bool isPlayed;									// 是否播放過音效
		CAnimation end1;								// 結束動畫1
		CAnimation end2;								// 結束動畫2
		CMovingBitmap endMenu1;							// 選單1
		CMovingBitmap endMenu2;							// 選單2
		CMovingBitmap endMenu3;							// 選單3
	};
}
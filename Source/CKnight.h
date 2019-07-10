#ifndef _CKNIGHT_H_
#define _CKNIGHT_H_
#include "includeFile.h"
namespace game_framework {
	class CKnight
	{
	public:
		CKnight();
		~CKnight();
		void Initialize();					// 初始化角色
		bool MapCanMoveRight(CMap *);		// 地圖可以往右移(人物往左走)
		bool MapCanMoveLeft(CMap *);		// 地圖可以往左移(人物往右走)
		void LoadBitmap();					// 載入圖形
		void OnMove(CMap *);				// 移動角色
		void SetMovingLeft(bool flag);		// 設定是否正在往左移動
		void SetMovingRight(bool flag);		// 設定是否正在往右移動
		void SetJumping(bool flag);			// 設定是否正在跳
		void SetAttacking(bool flag);		// 設定是否攻擊
		void SetMovingFast(bool flag);		// 設定是否快走
		void SetTouchMonster(CMonster *monster);// 設定是否撞到怪物
		void SetTouchMonster2(CMonster2 *monster);// 設定是否撞到怪物2
		void SetTouchFire(CMonster2 *fire); // 設定是否撞到火球
		void SetCatch(bool flag);			// 設定是否撿取
		bool isDeath(CMap*);				// 設定是否死亡
		bool isWin(CMap*);					// 設定是否勝利
		void OnShow();						// 將角色圖形貼到畫面
		bool isMovingLeft;					// 是否正在往左移動
		bool isMovingRight;					// 是否正在往右移動
		bool isAttacking;					// 是否攻擊
		bool isMovingFast;					// 是否快走
		bool isTouch;						// 被怪物撞到
		bool isTouch2;						// 被怪物撞到
		bool isBurn;						// 被火球燒到
		bool isCatch;						// 撿取
		bool flowerIsCatch;					// 花被撿起來了
		bool flower1IsCatch;				// 花被撿起來了
		bool foodIsEaten;					// 食物已被吃
		bool rising;						// true表上升、false表下降
		int x, y;							// 主角左上角座標
		int dx;								// X方向位移座標
		int STEP_SIZE;						// 一步的距離
		int initial_velocity;				// 初始速度
		int velocity;						// 目前速度
		int lifeLeft;						// 剩餘生命
		int level;							// 目前等級
	private:
		CAnimation knight1;					// 主角面向左走路
		CAnimation knightburn1;				// 被火球砸到會閃
		CAnimation knight1_2;				// 主角面向左攻擊
		CMovingBitmap knight2;				// 主角面向前
		CAnimation knightburn2;				// 被火球砸到會閃
		CAnimation knight3;					// 主角面向右走路
		CAnimation knightburn3;				// 被火球砸到會閃
		CAnimation knight3_2;				// 主角面向右攻擊
		CMovingBitmap knight_sprint1;		// 主角衝刺左
		CMovingBitmap knight_sprint3;		// 主角衝刺右
		CMovingBitmap life1;				// 生命
		CMovingBitmap life2;				// 生命
		CMovingBitmap life3;				// 生命
	};
}
#endif
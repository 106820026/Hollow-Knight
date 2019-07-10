#ifndef _CMAP_H_
#define _CMAP_H_
#include "includeFile.h"
namespace game_framework {
	class CMap 
	{
	public:
		CMap();
		~CMap();
		void Initialize(int gameLevel);			// 初始化
		void LoadBitmap();	
		void OnMove(CKnight *);
		void SetMovingFast(bool flag);			// 設定是否加速
		void hitFood(CKnight *);				// 攻擊食物
		bool isEmpty(int x, int y);				// 所在位置為空
		bool isUnderGround(int x, int y);		// 掉到底下
		bool isWin(int x, int y);				// 遊戲勝利
		bool isCutted(int x, int y);			// 被電鋸鋸到
		void OnShow();
		bool isMovingFast;						// 是否加速
		bool isChainsawDown;					// 電鋸往下
		bool flowerIsCatch;						// 速度花已被撿
		bool flower1IsCatch;					// 彈跳花已被撿
		bool foodIsEaten;						// 食物已被吃
		bool foodIsHit;							// 食物被攻擊
		int mapData[12][128];
		int level;								// 關卡
		int STEP_SIZE;							// 一步的距離
		int x1, x2, x3, x4, x5, x6, x7, x8;		// 地圖X座標
		int	xChainsaw, yChainsaw;				// 電鋸座標
		int	xFlower, yFlower;					// 花朵座標
		int	xFlower1, yFlower1;					// 花朵座標
		int	xDoor, yDoor;						// 門座標
		int	messageTimer, messageTimer1, messageTimerJ; // 速度/魔王/跳躍
		int	xFood, yFood, dFood, dxFood, centerX, foodLife;

	private:
		// 第一關
		CMovingBitmap HK_BG0_1;
		CMovingBitmap HK_BG0_2;
		CMovingBitmap HK_BG0_3;
		CMovingBitmap HK_BG0_4;
		CMovingBitmap HK_BG0_5;
		CMovingBitmap HK_BG0_6;
		CMovingBitmap HK_BG0_7;
		CMovingBitmap HK_BG0_8;
		// 第二關
		CMovingBitmap HK_BG1_1;
		CMovingBitmap HK_BG1_2;
		CMovingBitmap HK_BG1_3;
		CMovingBitmap HK_BG1_4;
		CMovingBitmap HK_BG1_5;
		CMovingBitmap HK_BG1_6;
		CMovingBitmap HK_BG1_7;
		CMovingBitmap HK_BG1_8;
		// 雜物
		CAnimation	  chainsaw;	// 電鋸
		CMovingBitmap flower;	// 吃了可以新增衝刺技能的小花
		CMovingBitmap flower1;	// 吃了可以二段跳的花
		CAnimation    flowermassage;//速度之花的資訊
		CAnimation    flowermassageJ;//跳跳之花的資訊
		CAnimation    monstermassage;//怪物的資訊
		CAnimation    door;		// 門
		// 毛毛蟲
		CMovingBitmap food1;	// 補血小蟲
		CMovingBitmap food3;    // 補血小蟲
		CMovingBitmap foodLife1;// 血條
		CMovingBitmap foodLife2;// 血條
		CMovingBitmap foodLife3;// 血條
		CMovingBitmap eaten1;	//死掉小蟲
		CMovingBitmap eaten3;	//死掉小蟲
	};
}
#endif

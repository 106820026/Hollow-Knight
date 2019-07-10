#ifndef _CMONSTER_H_
#define _CMONSTER_H_
#include "includeFile.h"
namespace game_framework {
	class CMonster
	{
	public:
		CMonster();
		void Initialize();				// 設定角色為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove(CKnight *knight);	// 移動角色
		void OnShow();					// 將角色圖形貼到畫面
		void SetisHit(CWeapon *weapon);	// 設定是否被主角攻擊到
		int floor;						// 地板的Y座標
		bool isHit;						// 是否被主角攻擊到
		int centerX;					// 怪物中心座標
		int M_dx,M_x, M_y;				// 怪物座標              
		int d;
		int STEP_SIZE;					// 一步的距離
		int hitleft;					// 剩餘攻擊數
	protected:
		CMovingBitmap Monster1;			// 主角面向左走路
		CMovingBitmap Monster3;			// 主角面向右走路
		CMovingBitmap blood1;			// 血條
		CMovingBitmap blood2;
		CMovingBitmap blood3;
		CMovingBitmap blood4;
		CMovingBitmap blood5;
		CMovingBitmap blood6;
	};
}
#endif
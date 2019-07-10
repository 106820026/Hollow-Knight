#ifndef _MONSTER2_H_
#define _MONSTER2_H_
#include "includeFile.h"
namespace game_framework {
	class CMonster2 {
	public:
		CMonster2();
		~CMonster2();
		void Initialize(int gamelevel);		// 初始化角色
		void LoadBitmap();					// 載入圖形
		void OnMove(CKnight *knight, CMap *);// 移動角色
		void OnShow();						// 將角色圖形貼到畫面
		void SetisHit(CWeapon *weapon);		// 設定是否被主角攻擊到
		int Width();						// 火球寬
		int d;								// 方向(0左 1右)
		int M_x, M_y;						// 怪物左上角座標
		int floor;							// 怪物地板座標
		int initial_velocity;				// 初始速度
		int velocity;						// 目前速度
		int rising;							// 0表在地板、1表上升、2表下降
		int F_x, F_y;						// 火球左上座標
		int attackTimer;					// 攻擊計時器
		int jumpTimer;						// 跳躍計時器
		bool fireIsOnFloor;					// 完成一次攻擊
		int A_x, A_y;						// 警告座標
		int hitleft;						// 剩餘攻擊數
		int i;
		int level;							// 目前等級
		bool isHit;							// 是否被攻擊
		CAnimation monsterLeft;
		CAnimation monsterRight;
		CAnimation fire;
		CMovingBitmap alert;				// 怪物跳躍警告
		CMovingBitmap blood1;				// 血條
		CMovingBitmap blood2;
		CMovingBitmap blood3;
		CMovingBitmap blood4;
		CMovingBitmap blood5;
		CMovingBitmap blood6;
	};
}
#endif // !_MONSTER2_H_
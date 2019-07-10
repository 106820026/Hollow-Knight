#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include <cstdlib>
#include "CMap.h"
#include "CKnight.h"
#include "CWeapon.h"
#include "CMonster.h"

namespace game_framework {
	CMonster::CMonster()
	{
		Initialize();
	}

	void CMonster::Initialize()
	{
		centerX = 730;				// 中心座標
		M_y = 220;					// Y座標
		M_x = 730;					// X座標
		M_dx = 0;					// X方向位移量
		d = 0;						// 方向(0往右 1往左)
		hitleft = 50;				// 剩餘攻擊數
	}

	void CMonster::LoadBitmap()
	{
		Monster1.LoadBitmap(IDB_MONSTER1, RGB(255, 255, 255));
		Monster3.LoadBitmap(IDB_MONSTER3, RGB(255, 255, 255));
		blood1.LoadBitmap(IDB_BLOOD1, RGB(255, 255, 255));
		blood2.LoadBitmap(IDB_BLOOD2, RGB(255, 255, 255));
		blood3.LoadBitmap(IDB_BLOOD3, RGB(255, 255, 255));
		blood4.LoadBitmap(IDB_BLOOD4, RGB(255, 255, 255));
		blood5.LoadBitmap(IDB_BLOOD5, RGB(255, 255, 255));
		blood6.LoadBitmap(IDB_BLOOD6, RGB(255, 255, 255));

	}

	void CMonster::OnMove(CKnight *knight)
	{
		if (hitleft > 0) {
			if (knight->isMovingFast) {
				STEP_SIZE = 8;
			}
			else {
				STEP_SIZE = 4;
			}
			M_dx = M_x - centerX;		// 位移量=目前x座標-中心座標
			if (-65 > M_dx) {			// 當位移量大於-65 轉向
				d = 0;
			}
			else if (65 < M_dx) {		// 當位移量大於65 轉向
				d = 1;
			}
			if (d == 0) {				// 當向右走
				M_x += STEP_SIZE;
			}
			else if (d == 1) {			// 當向左走
				M_x -= STEP_SIZE;
			}
		}
		if (knight->isMovingLeft && !knight->isAttacking) {		  // 隨著人物走動出現(同地圖位移方式)
			centerX += STEP_SIZE;
			M_x += STEP_SIZE;
		}
		else if (knight->isMovingRight && !knight->isAttacking) { // 隨著人物走動出現(同地圖位移方式) 
			centerX -= STEP_SIZE;
			M_x -= STEP_SIZE;
		}
	}
	void CMonster::SetisHit(CWeapon *weapon) {
			 // 從左邊射擊
		if ((weapon->isShootingRight && weapon->x + 160 >= M_x && weapon->x + 160 <= M_x + 130 && weapon->y + 55 > M_y && weapon->y + 55 < M_y + 98) ||
			 // 從右邊射擊
			(weapon->isShootingLeft && weapon->x <= M_x + 90 && weapon->x >= M_x && weapon->y + 55 > M_y && weapon->y + 55 < M_y + 98))
			isHit = true;
		else
			isHit = false;
	}

	void CMonster::OnShow()
	{
		if (isHit)					// 如果被擊中
			hitleft -= 1;			// 扣怪物生命
		if (hitleft > 0)			// 還有命時
			if (d == 1) {
				Monster1.SetTopLeft(M_x, M_y);
				Monster1.ShowBitmap();
			}
			else if (d == 0) {
				Monster3.SetTopLeft(M_x, M_y);
				Monster3.ShowBitmap();
			}

			if (hitleft < 50 && hitleft >= 40) {
				blood1.SetTopLeft(M_x, M_y - 8);
				blood1.ShowBitmap();
			}
			else if(hitleft < 40 && hitleft >= 30){
				blood2.SetTopLeft(M_x, M_y - 8);
				blood2.ShowBitmap();
			}
			else if (hitleft < 30 && hitleft >= 20) {
				blood3.SetTopLeft(M_x, M_y - 8);
				blood3.ShowBitmap();
			}
			else if (hitleft < 20 && hitleft >= 10) {
				blood4.SetTopLeft(M_x, M_y - 8);
				blood4.ShowBitmap();
			}
			else if (hitleft < 10 && hitleft >= 5) {
				blood5.SetTopLeft(M_x, M_y - 8);
				blood5.ShowBitmap();
			}
			else if (hitleft < 5 && hitleft > 0) {
				blood6.SetTopLeft(M_x, M_y - 8);
				blood6.ShowBitmap();
			}
	}
}
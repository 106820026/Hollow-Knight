#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CKnight.h"
#include "CMap.h"
#include "CWeapon.h"
#include "CMonster2.h"

namespace game_framework {
	CMonster2::CMonster2() {
		Initialize(level);
	}

	CMonster2::~CMonster2() {

	}

	void CMonster2::Initialize(int gamelevel) {
		level = gamelevel;
		if (level == 2) {						// 當到魔王關時
			M_x = 490; M_y = 225;
			hitleft = 100;						// 怪物血量
			d = 0;								//一開始先向左
			jumpTimer = 0;
			floor = 225;						// 地板座標
			const int INITIAL_VELOCITY = 15;	// 初始上升速度
			initial_velocity = INITIAL_VELOCITY;
			velocity = initial_velocity;
			rising = false;
			isHit = false;
		}
		else {
			hitleft = 100;						// 怪物血量
			M_x = F_x = 245;
			M_y = F_y = 0;
			d = 1;				//一開始先向右
			attackTimer = 0;
			i = 0;
			isHit = false;
		}
	}

	void CMonster2::LoadBitmap() {
		char *filename1[3] = { ".\\bitmaps\\HK_monster1_1.bmp",".\\bitmaps\\HK_monster1_2.bmp",".\\bitmaps\\HK_monster1_3.bmp" };
		for (int i = 0; i < 3; i++)
			monsterLeft.AddBitmap(filename1[i], RGB(255, 255, 255)); // 左走
		char *filename2[3] = { ".\\bitmaps\\HK_monster3_1.bmp",".\\bitmaps\\HK_monster3_2.bmp",".\\bitmaps\\HK_monster3_3.bmp" };
		for (int i = 0; i < 3; i++)
			monsterRight.AddBitmap(filename2[i], RGB(255, 255, 255)); // 右走
		char *filename3[10] = { 
			".\\bitmaps\\fire10.bmp", ".\\bitmaps\\fire9.bmp",".\\bitmaps\\fire8.bmp", ".\\bitmaps\\fire7.bmp",
			".\\bitmaps\\fire6.bmp", ".\\bitmaps\\fire5.bmp",".\\bitmaps\\fire4.bmp", ".\\bitmaps\\fire3.bmp",
			".\\bitmaps\\fire2.bmp", ".\\bitmaps\\fire.bmp", };
		for (int i = 0; i < 10; i++)
			fire.AddBitmap(filename3[i], RGB(255, 255, 255)); // 火球
		alert.LoadBitmap(IDB_ALERT, RGB(255, 255, 255));
		blood1.LoadBitmap(IDB_BLOOD1, RGB(255, 255, 255));
		blood2.LoadBitmap(IDB_BLOOD2, RGB(255, 255, 255));
		blood3.LoadBitmap(IDB_BLOOD3, RGB(255, 255, 255));
		blood4.LoadBitmap(IDB_BLOOD4, RGB(255, 255, 255));
		blood5.LoadBitmap(IDB_BLOOD5, RGB(255, 255, 255));
		blood6.LoadBitmap(IDB_BLOOD6, RGB(255, 255, 255));
	}

	void CMonster2::OnMove(CKnight *knight, CMap *map) {
		monsterLeft.OnMove();
		monsterRight.OnMove();
		const int STEP_SIZE = 4;
		int knightStep = 4;
		if (hitleft > 0) {	// 當怪物還有生命時才能動
			// 怪物左右移動
			if (d == 1) { //向右
				if (knight->MapCanMoveLeft(map) && !knight->isAttacking)
					M_x += 2;
				else if (knight->MapCanMoveRight(map) && !knight->isAttacking)
					M_x += 5;
				else
					M_x += STEP_SIZE;
				if (M_x > 490)
					d = 0;
			}
			else if (d == 0) { //向左
				if (knight->MapCanMoveLeft(map) && !knight->isAttacking)
					M_x -= 2;
				else if (knight->MapCanMoveRight(map) && !knight->isAttacking)
					M_x -= 4;
				else
					M_x -= STEP_SIZE;
				if (M_x < 25)
					d = 1;
			}
			// 怪物跳躍
			if (rising == 1) {			// 上升狀態
				if (velocity > 0) {
					M_y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
					velocity--;			// 受重力影響，下次的上升速度降低
				}
				else {
					rising = 2;			// 當速度 <= 0，上升終止，下次改為下降
					velocity = 1;		// 下降的初速(velocity)為1
				}
			}
			else if (rising == 2) {		// 下降狀態
				if (M_y < floor - 1) {  // 當y座標還沒碰到地板
					M_y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
					velocity++;			// 受重力影響，下次的下降速度增加
				}
				else {
					M_y = floor - 1;	// 當y座標低於地板，更正為地板上
					rising = 0;
					jumpTimer = 0;		// 探底反彈，下次改為上升
					velocity = initial_velocity; // 重設上升初始速度
				}
			}
			else if (rising == 0) {		// 走路狀態
				if (jumpTimer == 50) {
					rising = 1;
				}
				else {
					jumpTimer++;
				}
			}
		}
		// 火球移動
		if (attackTimer == 13) {
			fire.OnMove2();
			if (knight->MapCanMoveLeft(map) && !knight->isAttacking)
				F_x += STEP_SIZE - knightStep;
			else if (knight->MapCanMoveRight(map) && !knight->isAttacking)
				F_x += STEP_SIZE + knightStep;
			else
				F_x += STEP_SIZE;
			F_y += 12;
			if (F_y >= 360) { //當掉到地板
				F_x = M_x;
				F_y = M_y;
				attackTimer = 0;
				i = 0;
			}
		}
		else {
			attackTimer++;
		}
		// 警告標誌移動
		A_x = knight->x + 20;
		A_y = knight->y - 10;
		//怪物被攻擊
		if (isHit)
			hitleft--;
	}

	int CMonster2::Width() {
		return fire.Width();
	}

	void CMonster2::SetisHit(CWeapon *weapon) {
			// 從左邊射擊
		if ((weapon->isShootingRight && weapon->x + 160 >= M_x && weapon->x + 160 <= M_x + 130 && weapon->y + 55 > M_y && weapon->y + 55 < M_y + 98) ||
			// 從右邊射擊
			(weapon->isShootingLeft && weapon->x <= M_x + 90 && weapon->x >= M_x && weapon->y + 55 > M_y && weapon->y + 55 < M_y + 98))
			isHit = true;
		else
			isHit = false;
	}

	void CMonster2::OnShow() {
		if (level != 2) { // 如果在第二關時 
			if (d == 0) {
				monsterLeft.SetTopLeft(M_x, M_y);
				monsterLeft.OnShow();
			}
			else if (d == 1) {
				monsterRight.SetTopLeft(M_x, M_y);
				monsterRight.OnShow();
			}
			if (attackTimer == 13) {
				fire.SetTopLeft(F_x, F_y);
				fire.OnShow();
			}
		}
		else {	// 如果在第二關的魔王時
			// 顯示怪物
			if (hitleft > 0) {
				if (d == 0) {
					monsterLeft.SetTopLeft(M_x, M_y);
					monsterLeft.OnShow();
				}
				else if (d == 1) {
					monsterRight.SetTopLeft(M_x, M_y);
					monsterRight.OnShow();
				}
				if (jumpTimer > 40 && jumpTimer <= 50) {
					alert.SetTopLeft(A_x, A_y);
					alert.ShowBitmap();
				}
			}
			//怪物血條
			if (hitleft > 0)			// 還有命時
				if (hitleft < 100 && hitleft >= 80) {
					blood1.SetTopLeft(M_x + 50, M_y - 8);
					blood1.ShowBitmap();
				}
				else if (hitleft < 80 && hitleft >= 60) {
					blood2.SetTopLeft(M_x + 50, M_y - 8);
					blood2.ShowBitmap();
				}
				else if (hitleft < 60 && hitleft >= 40) {
					blood3.SetTopLeft(M_x + 50, M_y - 8);
					blood3.ShowBitmap();
				}
				else if (hitleft < 40 && hitleft >= 20) {
					blood4.SetTopLeft(M_x + 50, M_y - 8);
					blood4.ShowBitmap();
				}
				else if (hitleft < 20 && hitleft >= 1) {
					blood5.SetTopLeft(M_x + 50, M_y - 8);
					blood5.ShowBitmap();
				}
				else if (hitleft < 1 && hitleft > 0) {
					blood6.SetTopLeft(M_x + 50, M_y - 8);
					blood6.ShowBitmap();
				}
		}
	}
}
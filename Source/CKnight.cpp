#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CMap.h"
#include "CMonster.h"
#include "CMonster2.h"
#include "CKnight.h"

namespace game_framework {
	CKnight::CKnight() {
		Initialize();
	}

	CKnight::~CKnight() {
		
	}

	void CKnight::Initialize() {
		const int INITIAL_VELOCITY = 15;	// 初始上升速度
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		lifeLeft = 100;
		x = 240;
		y = 230;
		dx = x;
		isMovingLeft = isMovingRight = isAttacking = rising = isMovingFast = flower1IsCatch =
		isTouch = isTouch2 = isCatch = flowerIsCatch = isBurn = foodIsEaten = false;
	}

	bool CKnight::MapCanMoveRight(CMap *map) {  // 如果主角正在往左移,先確認左方是否為空,且位於240到4720之間
		return isMovingLeft && map->isEmpty(dx - 1, y) && map->isEmpty(dx - 1, y + 45) && 
			   map->isEmpty(dx - 1, y + 91) && dx >= 240 && dx <= 4720 && !isAttacking && level != 2;
	}

	bool CKnight::MapCanMoveLeft(CMap *map) {  // 如果主角正在往右移,先確認右方是否為空,且位於240到4720之間
		return isMovingRight && map->isEmpty(dx + 57, y) && map->isEmpty(dx + 57, y + 45) && 
			   map->isEmpty(dx + 57, y + 91) && dx >= 240 && dx <= 4720 && !isAttacking && level != 2;
	}

	void CKnight::LoadBitmap(){
		char *filename1[2] = { ".\\bitmaps\\HK_knight1.bmp",".\\bitmaps\\HK_knight1_2.bmp" };
		for (int i = 0; i < 2; i++)																// 載入走路動畫(由2張圖形構成)
			knight1.AddBitmap(filename1[i], RGB(255, 255, 255));								// 載入主角左側
		char *filename2[2] = { ".\\bitmaps\\HK_knight1_3.bmp",".\\bitmaps\\HK_knight1_4.bmp" };	
		for (int i = 0; i < 2; i++)																// 載入攻擊動畫(由2張圖形構成)
			knight1_2.AddBitmap(filename2[i], RGB(255, 255, 255));								// 載入主角左側
		char *filename3[2] = { ".\\bitmaps\\HK_knight3.bmp",".\\bitmaps\\HK_knight3_2.bmp" };
		for (int i = 0; i < 2; i++)																// 載入走路動畫(由2張圖形構成)
			knight3.AddBitmap(filename3[i], RGB(255, 255, 255));								// 載入主角右側
		char *filename4[2] = { ".\\bitmaps\\HK_knight3_3.bmp",".\\bitmaps\\HK_knight3_4.bmp" };
		for (int i = 0; i < 2; i++)																// 載入攻擊動畫(由2張圖形構成)
			knight3_2.AddBitmap(filename4[i], RGB(255, 255, 255));								// 載入主角右側
		char *filename5[2] = { ".\\bitmaps\\HK_knight1_2.bmp",".\\bitmaps\\HK_knight1trans.bmp" };
		for (int i = 0; i < 2; i++)																// 載入被攻擊動畫(由2張圖形構成)
			knightburn1.AddBitmap(filename5[i], RGB(255, 255, 255));							// 載入主角左側
		char *filename6[2] = { ".\\bitmaps\\HK_knight3_2.bmp",".\\bitmaps\\HK_knight3trans.bmp" };
		for (int i = 0; i < 2; i++)																// 載入被攻擊動畫(由2張圖形構成)
			knightburn3.AddBitmap(filename6[i], RGB(255, 255, 255));							// 載入主角右側
		char *filename7[2] = { ".\\bitmaps\\HK_knight2.bmp",".\\bitmaps\\HK_knight2trans.bmp" };
		for (int i = 0; i < 2; i++)																// 載入被攻擊動畫(由2張圖形構成)
			knightburn2.AddBitmap(filename7[i], RGB(255, 255, 255));							// 載入主角正面
		knight2.LoadBitmap(IDB_KNIGHT2, RGB(255, 255, 255));// 載入主角正面
		knight_sprint1.LoadBitmap(IDB_KNIGHT_SPRINT1, RGB(0, 0, 0)); // 衝刺左
		knight_sprint3.LoadBitmap(IDB_KNIGHT_SPRINT3, RGB(0, 0, 0)); // 衝刺右
		life1.LoadBitmap(IDB_LIFE1, RGB(255, 255, 255));
		life2.LoadBitmap(IDB_LIFE2, RGB(255, 255, 255));
		life3.LoadBitmap(IDB_LIFE3, RGB(255, 255, 255));
	}

	void CKnight::OnMove(CMap * map){
		level = map->level;
		//////////設定步數//////////
		if (isMovingFast) {
			STEP_SIZE = 8;
		}
		else {
			STEP_SIZE = 4;
		}
		//////////觸碰怪物//////////
		if (isTouch) {
			lifeLeft -= 1;
		}
		if (isTouch2) {
			lifeLeft -= 1;
		}
		//////////攻擊//////////
		if (isAttacking && isMovingLeft) {			// 向左
			knight1_2.OnMove2();
		}
		else if (isAttacking && isMovingRight) {	// 向右
			knight3_2.OnMove2();
		}
		//////////左右移動//////////
		else if (isMovingLeft && map->isEmpty(dx - 1, y) && map->isEmpty(dx - 1, y + 45) && map->isEmpty(dx - 1, y + 91)) {// 往左走且左方為空(dx - 1, y + 60)
			knight1.OnMove();
			knightburn1.OnMove2();
			if (level == 2) {									// 當在第二關的魔王關時
				if (x > 0) {									// dx必須>0,這樣才不會跑出地圖
					x -= STEP_SIZE;								// 地圖不動,換人物動
				}
			}
			else if (dx > 240 && dx < 4720) {					// 位移量介於240到4720時(地圖可動的值)
				dx -= STEP_SIZE;								// 移動位移量
				x = 240;										// 地圖在動時 人物保持在x=240
				if (dx < 240) {									// 當位移量小於240時 
					dx = 239;									// 重設為239(為了方便XD)
					x = 240;									// 地圖動時,人物保持在x = 240
				}
			}
			else if(dx > 0) {									// dx必須>0,這樣才不會跑出地圖
				x -= STEP_SIZE;									// 地圖不動,換人物動
				dx -= STEP_SIZE;								// 位移量還是要繼續算
			}
		}
		else if (isMovingRight && map->isEmpty(dx + 57, y) && map->isEmpty(dx + 57, y + 45) && map->isEmpty(dx + 57, y + 91)) {// 往右走且右方為空
			knight3.OnMove();
			knightburn3.OnMove2();
			if (level == 2) {									// 當在第二關的魔王關時
				if (x + 90 < 640) {								// dx必須<640,這樣才不會跑出地圖
					x += STEP_SIZE;								// 地圖不動,換人物動
				}
			}
			else if (dx > 240 && dx < 4720) {					 // 位移量介於240到4720時(地圖可動的值)
				dx += STEP_SIZE;								 // 移動位移量
				x = 240;										 // 地圖在動時 人物保持在x=240
				if (dx > 4720) {								 // 當位移量大於4720時
					dx = 4721;									 // 重設為4721(為了方便XD)
					x = 240;									 // 地圖動時,人物保持在x = 240
				}
			}
			else if(dx+90<5120){								 // dx必須<5120,這樣才不會跑出地圖
				x += STEP_SIZE;									 // 地圖不動,換人物動
				dx += STEP_SIZE;								 // 位移量還是要繼續算
			}
		}
		knightburn2.OnMove2();									// 正面閃爍動畫
		//////////跳躍//////////
		if (rising && map->isEmpty(dx,y) && map->isEmpty(dx+45, y) && map->isEmpty(dx+51, y)) {// 上升狀態
			if (velocity > 0) {
				y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				velocity--;		// 受重力影響，下次的上升速度降低
			}
			else {
				rising = false; // 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;	// 下降的初速(velocity)為1
			}
		}
		else {					// 下降狀態
			rising = false;
			if (map->isEmpty(dx, y + 96) && map->isEmpty(dx+45, y + 96) && map->isEmpty(dx+51, y + 96)) {// 當y座標還沒碰到地板
				y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				velocity++;		// 受重力影響，下次的下降速度增加
			}
			else {
				y = (y+96)/40*40-96;		 // 當y座標低於地板，更正為地板上(y/40+1)*40-1
				velocity = initial_velocity; // 重設上升初始速度
			}
		}
		//////////撿東西//////////
		if (foodIsEaten) {
			lifeLeft = lifeLeft + 40; // 回復40生命
			foodIsEaten = false;
		}
		switch (map->level) {
		case 0:
			if (isCatch && dx > 1240 && dx + 55 < 1320 && y + 90 <120) {
				flowerIsCatch = true; // 撿取速度之花
			}
			break;
		case 1:
			if (isCatch && x > map->xFood - 30 && x < map->xFood + 47 && 
				y + 90 > map->yFood && map->foodLife < 0) {
				foodIsEaten = true; // 撿取食物
				isCatch = false;
			}
			if (isCatch && x > map->xFlower1-20 && x < map->xFlower1+42) {
				flower1IsCatch = true; // 撿取跳跳之花
			}
			break;
		}
	}

	void CKnight::SetMovingLeft(bool flag){
		isMovingLeft = flag;
	}

	void CKnight::SetMovingRight(bool flag){
		isMovingRight = flag;
	}

	void CKnight::SetJumping(bool flag){
		rising = flag;
	}

	void CKnight::SetAttacking(bool flag){
		isAttacking = flag;
	}

	void CKnight::SetMovingFast(bool flag) {
		isMovingFast = flag;
	}

	void CKnight::SetTouchMonster(CMonster *monster) {
		if (monster->hitleft > 0) { // 在怪物還活著的時候
			if (x + 90 > monster->M_x && x < monster->M_x + 90) {
				isTouch = true;
			}
			else
				isTouch = false;
		}
	}

	void CKnight::SetTouchMonster2(CMonster2 *monster) {
		if (monster->hitleft > 0) { // 在怪物還活著的時候
			if (x + 56 >= monster->M_x + 35 && x + 28 <= monster->M_x + 115) {
				if(y+45>monster->M_y&&y+45<monster->M_y+134)
					isTouch2 = true;
			}
			else
				isTouch2 = false;
		}
	}

	void CKnight::SetTouchFire(CMonster2 *fire) {
		if (lifeLeft > 0) { // 在主角還活著的時候
			if (fire->F_y > y && fire->F_x<x + 90 && (fire->F_x + fire->fire.Width()) > x + 10) {
				lifeLeft = lifeLeft - 1;
				isBurn = true;
			}
			else
				isBurn = false;
		}
	}

	void CKnight::SetCatch(bool flag) {
		isCatch = flag;
	}

	bool CKnight::isDeath(CMap *map) {
		return map->isUnderGround(dx,y+100) ||
			   map->isCutted(x,y) ||
			   lifeLeft <=0;
	}

	bool CKnight::isWin(CMap *map) {
		return map->isWin(dx	 , y + 100) ||
			   map->isWin(dx + 45, y + 100) ||
			   map->isWin(dx + 91, y + 100);
	}

	void CKnight::OnShow(){
		if ((isMovingFast&&isMovingLeft)) {
			knight_sprint1.SetTopLeft(x, y);
			knight_sprint1.ShowBitmap();
		}
		else if ((isMovingFast&&isMovingRight)) {
			knight_sprint3.SetTopLeft(x - 200, y);
			knight_sprint3.ShowBitmap();
		}
		else if (isAttacking && isMovingLeft) {			// 向左攻擊
			knight1_2.SetTopLeft(x, y + 5);
			knight1_2.OnShow();
		}
		else if (isAttacking && isMovingRight) {		// 向右攻擊
			knight3_2.SetTopLeft(x, y + 5);
			knight3_2.OnShow();
		}
		else if (isMovingLeft) {						// 往左走
			if (isBurn || isTouch || isTouch2) {
				knightburn1.SetTopLeft(x, y + 5);
				knightburn1.OnShow();
			}
			else {
				knight1.SetTopLeft(x, y + 5);
				knight1.OnShow();
			}
		}
		else if (isMovingRight) {						// 往右走
			if (isBurn || isTouch || isTouch2) {
				knightburn3.SetTopLeft(x, y + 5);
				knightburn3.OnShow();
			}
			else {
				knight3.SetTopLeft(x, y + 5);
				knight3.OnShow();
			}
		}
		else{											// 跳躍 + 不動
			if (isBurn || isTouch || isTouch2) {
				knightburn2.SetTopLeft(x, y);
				knightburn2.OnShow();
			}
			else {
				knight2.SetTopLeft(x, y);
				knight2.ShowBitmap();
			}
		}
		////////人物生命////////
		if (lifeLeft > 66) {
			life1.SetTopLeft(0, 0);
			life2.SetTopLeft(23, 0);
			life3.SetTopLeft(46, 0);
			life1.ShowBitmap();
			life2.ShowBitmap();
			life3.ShowBitmap();
		}
		else if (lifeLeft > 32) {
			life1.ShowBitmap();
			life2.ShowBitmap();
		}
		else if (lifeLeft > 0) {
			life1.ShowBitmap();
		}
	}
}
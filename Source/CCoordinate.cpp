#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CCoordinate.h"

namespace game_framework {
	CCoordinate::CCoordinate() 
	{
		Initialize();
	}

	int CCoordinate::GetX()
	{
		return x;
	}

	int CCoordinate::GetY()
	{
		return y;
	}

	void CCoordinate::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void CCoordinate::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void CCoordinate::SetJumping(bool flag)
	{
		rising = flag;
	}

	void CCoordinate::SetAttacking(bool flag)
	{
		isAttacking = flag;
	}

	void CCoordinate::Initialize() 
	{
		const int X = 240;
		const int Y = 240;
		x = X;
		y = Y;
		isMovingLeft = isMovingRight = isAttacking = rising = false;
		int map[6][24] = {
			//   第一張圖  \\ //  第二張圖  \\ //  第三張圖  \\          /
			{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 24; j++) {
				mapData[i][j] = map[i][j];
			}
		}
	}

	void CCoordinate::OnMove()
	{
		int STEP_SIZE = 8;
		if (isMovingLeft && mapData[y / 80][(x - 1) / 80] == 0 && !isAttacking) {
			x -= STEP_SIZE;
		}
		else if (isMovingRight && mapData[y / 80][(x + 1) / 80] == 0 && !isAttacking) {
			x += STEP_SIZE;
		}
		if (rising) {			// 上升狀態
			if (velocity > 0) {
				y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
				velocity--;		// 受重力影響，下次的上升速度降低
			}
			else {
				rising = false; // 當速度 <= 0，上升終止，下次改為下降
				velocity = 1;	// 下降的初速(velocity)為1
			}
		}
		else {				// 下降狀態
			if (mapData[(y + 1) / 80][x / 80] == 0) {  // 當y座標還沒碰到地板
				y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
				velocity++;		// 受重力影響，下次的下降速度增加
			}
			else {
				y = y;  // 當y座標低於地板，更正為地板上
				rising = true;	// 探底反彈，下次改為上升
				velocity = initial_velocity; // 重設上升初始速度
			}
		}
	}
}
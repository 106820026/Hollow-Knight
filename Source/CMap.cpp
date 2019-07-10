#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CKnight.h"
#include "CMonster.h"
#include "CMap.h"
#include "CWeapon.h"

namespace game_framework {
	CMap::CMap()
	{
		Initialize(level);
	}

	CMap::~CMap() {

	}

	void CMap::Initialize(int gameLevel) {
		level = gameLevel;
		x1 = 0;    x2 = 640;  x3 = 1280; x4 = 1920;
		x5 = 2560; x6 = 3200; x7 = 3840; x8 = 4480;
		if (gameLevel == 0) {  //只有在第一關出現
			xChainsaw = 1720;  yChainsaw = 0;
			xFlower = 1260;	   yFlower = 80;
			xDoor = 4970;      yDoor = 170;
			messageTimer = 80;
		}
		if (gameLevel = 1) {   //只有在第二關出現
			xFood = 1120; yFood = 327; dFood = 1, dxFood = 0, centerX = 950, foodLife = 60;
			xFlower1 = 2870; yFlower1 = 395;
			messageTimer1 = 50; messageTimerJ = 80;
		}
		isMovingFast = flowerIsCatch = flower1IsCatch = foodIsHit = false;
		isChainsawDown = true;
		int map0[12][128] = { // 第一關地圖
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0,1,1,0,0,0,0,1,1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0, 0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0, 0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0, 0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,1,1,1,0,0,0,0,0,0,0,1,1,1,2,2, 0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,0, 0,0,0,1,1,1,1,2,2,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,2,2,2,0,0,1,1, 0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2, 0,1,1,1,2,2,0,0,0,2,2,1,1,1,0,0, 0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1, 2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0, 0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 } };
		int map1[12][128] = { // 第二關地圖
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1, 1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,1,0,0,1,1,0,0,0,0,0,0,1,1,1,0, 1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0, 0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1, 0,0,1,1,0,0,0,0,1,0,0,1,1,1,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0, 1,1,2,2,1,1,0,0,1,1,0,0,1,0,0,0, 1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1, 0,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0, 1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0, 0,0,0,1,1,0,0,0,0,1,0,0,1,1,1,1, 1,1,0,0,1,1,2,2,1,1,2,2,0,0,0,0, 1,0,1,1,1,0,0,0,1,1,0,0,0,0,0,0, 0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1, 0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1, 1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 0,0,2,2,0,0,0,2,2,0,0,0,0,0,2,0, 1,1,1,1,1,2,2,0,0,1,2,2,1,1,1,1, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,0,0,0,0,2,2,0,0,0,0, 0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,1, 1,1,0,0,0,0,2,2,0,0,0,0,0,0,0,0, 1,1,1,1,0,0,0,2,2,0,0,2,2,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
		int map2[12][16] = { // 第二關魔王地圖
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
		/////讀取地圖/////
		switch (level) {
		case 0:
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 128; j++) {
					mapData[i][j] = map0[i][j];
				}
			}
			break;
		case 1:
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 128; j++) {
					mapData[i][j] = map1[i][j];
				}
			}
			break;
		case 2:
			for (int i = 0; i < 12; i++) {
				for (int j = 0; j < 16; j++) {
					mapData[i][j] = map2[i][j];
				}
			}
			break;
		}
	}

	void CMap::LoadBitmap()
	{
		// 第一關
		HK_BG0_1.LoadBitmap(IDB_HK_BG1);
		HK_BG0_2.LoadBitmap(IDB_HK_BG2);
		HK_BG0_3.LoadBitmap(IDB_HK_BG3);
		HK_BG0_4.LoadBitmap(IDB_HK_BG4);
		HK_BG0_5.LoadBitmap(IDB_HK_BG5);
		HK_BG0_6.LoadBitmap(IDB_HK_BG6);
		HK_BG0_7.LoadBitmap(IDB_HK_BG7);
		HK_BG0_8.LoadBitmap(IDB_HK_BG8);
		char *filename[12] = { ".\\bitmaps\\Chainsaw1.bmp", ".\\bitmaps\\Chainsaw2.bmp",
							   ".\\bitmaps\\Chainsaw3.bmp", ".\\bitmaps\\Chainsaw4.bmp",
							   ".\\bitmaps\\Chainsaw5.bmp", ".\\bitmaps\\Chainsaw6.bmp",
							   ".\\bitmaps\\Chainsaw7.bmp", ".\\bitmaps\\Chainsaw8.bmp",
							   ".\\bitmaps\\Chainsaw9.bmp", ".\\bitmaps\\Chainsaw10.bmp",
							   ".\\bitmaps\\Chainsaw11.bmp",".\\bitmaps\\Chainsaw12.bmp" };
		for (int i = 0; i < 12; i++)// 載入電鋸動畫(由12張圖形構成)
			chainsaw.AddBitmap(filename[i], RGB(255, 255, 255));
		char *filename1[4] = { ".\\bitmaps\\door1.bmp", ".\\bitmaps\\door2.bmp",
							   ".\\bitmaps\\door3.bmp", ".\\bitmaps\\door4.bmp" };
		for (int i = 0; i < 4; i++)// 載入門動畫(由4張圖形構成)
			door.AddBitmap(filename1[i], RGB(255, 255, 255));
		flower.LoadBitmap(IDB_FLOWER, RGB(255, 255, 255));
		// 第二關
		HK_BG1_1.LoadBitmap(IDB_HK_L2BG1);
		HK_BG1_2.LoadBitmap(IDB_HK_L2BG2);
		HK_BG1_3.LoadBitmap(IDB_HK_L2BG3);
		HK_BG1_4.LoadBitmap(IDB_HK_L2BG4);
		HK_BG1_5.LoadBitmap(IDB_HK_L2BG5);
		HK_BG1_6.LoadBitmap(IDB_HK_L2BG6);
		HK_BG1_7.LoadBitmap(IDB_HK_L2BG7);
		HK_BG1_8.LoadBitmap(IDB_HK_L2BG8);
		char *filename2[27] = { ".\\bitmaps\\HK_FM_1.bmp", ".\\bitmaps\\HK_FM_2.bmp",
								".\\bitmaps\\HK_FM_3.bmp", ".\\bitmaps\\HK_FM_4.bmp",
								".\\bitmaps\\HK_FM_5.bmp", ".\\bitmaps\\HK_FM_6.bmp",
								".\\bitmaps\\HK_FM_7.bmp", ".\\bitmaps\\HK_FM_8.bmp",
								".\\bitmaps\\HK_FM_9.bmp", ".\\bitmaps\\HK_FM_10.bmp",
								".\\bitmaps\\HK_FM_11.bmp", ".\\bitmaps\\HK_FM_12.bmp",
								".\\bitmaps\\HK_FM_13.bmp", ".\\bitmaps\\HK_FM_14.bmp",
								".\\bitmaps\\HK_FM_15.bmp", ".\\bitmaps\\HK_FM_16.bmp",
								".\\bitmaps\\HK_FM_17.bmp", ".\\bitmaps\\HK_FM_18.bmp",
								".\\bitmaps\\HK_FM_19.bmp", ".\\bitmaps\\HK_FM_20.bmp",
								".\\bitmaps\\HK_FM_21.bmp", ".\\bitmaps\\HK_FM_22.bmp",
								".\\bitmaps\\HK_FM_23.bmp", ".\\bitmaps\\HK_FM_24.bmp",
								".\\bitmaps\\HK_FM_25.bmp", ".\\bitmaps\\HK_FM_26.bmp",
								".\\bitmaps\\HK_FM_27.bmp" };
		for (int i = 0; i < 27; i++)// 載入花資訊動畫(由27張圖形構成)
			flowermassage.AddBitmap(filename2[i], RGB(0, 255, 0));
		char *filename4[27] = { ".\\bitmaps\\HK_FM2_1.bmp", ".\\bitmaps\\HK_FM2_2.bmp",
								".\\bitmaps\\HK_FM2_3.bmp", ".\\bitmaps\\HK_FM2_4.bmp",
								".\\bitmaps\\HK_FM2_5.bmp", ".\\bitmaps\\HK_FM2_6.bmp",
								".\\bitmaps\\HK_FM2_7.bmp", ".\\bitmaps\\HK_FM2_8.bmp",
								".\\bitmaps\\HK_FM2_9.bmp", ".\\bitmaps\\HK_FM2_10.bmp",
								".\\bitmaps\\HK_FM2_11.bmp", ".\\bitmaps\\HK_FM2_12.bmp",
								".\\bitmaps\\HK_FM2_13.bmp", ".\\bitmaps\\HK_FM2_14.bmp",
								".\\bitmaps\\HK_FM2_15.bmp", ".\\bitmaps\\HK_FM2_16.bmp",
								".\\bitmaps\\HK_FM2_17.bmp", ".\\bitmaps\\HK_FM2_18.bmp",
								".\\bitmaps\\HK_FM2_19.bmp", ".\\bitmaps\\HK_FM2_20.bmp",
								".\\bitmaps\\HK_FM2_21.bmp", ".\\bitmaps\\HK_FM2_22.bmp",
								".\\bitmaps\\HK_FM2_23.bmp", ".\\bitmaps\\HK_FM2_24.bmp",
								".\\bitmaps\\HK_FM2_25.bmp", ".\\bitmaps\\HK_FM2_26.bmp",
								".\\bitmaps\\HK_FM2_27.bmp" };
		for (int i = 0; i < 27; i++)// 載入花資訊動畫(由27張圖形構成)
			flowermassageJ.AddBitmap(filename4[i], RGB(0, 255, 0));
		char *filename3[17] = { ".\\bitmaps\\HK_MM_1.bmp", ".\\bitmaps\\HK_MM_2.bmp",
								".\\bitmaps\\HK_MM_3.bmp", ".\\bitmaps\\HK_MM_4.bmp",
								".\\bitmaps\\HK_MM_5.bmp", ".\\bitmaps\\HK_MM_6.bmp",
								".\\bitmaps\\HK_MM_7.bmp", ".\\bitmaps\\HK_MM_8.bmp",
								".\\bitmaps\\HK_MM_9.bmp", ".\\bitmaps\\HK_MM_10.bmp",
								".\\bitmaps\\HK_MM_11.bmp", ".\\bitmaps\\HK_MM_12.bmp",
								".\\bitmaps\\HK_MM_13.bmp", ".\\bitmaps\\HK_MM_14.bmp",
								".\\bitmaps\\HK_MM_15.bmp", ".\\bitmaps\\HK_MM_16.bmp", 
								".\\bitmaps\\HK_MM_17.bmp", };
		for (int i = 0; i < 17; i++)// 載入怪物資訊動畫(由17張圖形構成)
			monstermassage.AddBitmap(filename3[i], RGB(0, 255, 0));
		food1.LoadBitmap(IDB_FOOD1, RGB(255, 255, 255));
		food3.LoadBitmap(IDB_FOOD3, RGB(255, 255, 255));
		foodLife1.LoadBitmap(IDB_FOODLIFE1);
		foodLife2.LoadBitmap(IDB_FOODLIFE2);
		foodLife3.LoadBitmap(IDB_FOODLIFE3);
		eaten1.LoadBitmap(IDB_EATEN1, RGB(255, 255, 255));
		eaten3.LoadBitmap(IDB_EATEN3, RGB(255, 255, 255));
		flower1.LoadBitmap(IDB_FLOWER1, RGB(255, 255, 255));
	}

	void CMap::OnMove(CKnight *knight)
	{	
		/////X方向的動作/////
		if (isMovingFast) {
			STEP_SIZE = 8;
		}
		else {
			STEP_SIZE = 4;
		}
		if (knight->MapCanMoveRight(this) && !knight->isAttacking) { // 地圖可以往右動(人物往左)
			if (x1 == 0) { // 當第一張圖在0位置時,地圖不能動
				STEP_SIZE = 0;
			}
			x1 += STEP_SIZE;
			x2 += STEP_SIZE;
			x3 += STEP_SIZE;
			x4 += STEP_SIZE;
			x5 += STEP_SIZE;
			x6 += STEP_SIZE;
			x7 += STEP_SIZE;
			x8 += STEP_SIZE;
			xChainsaw += STEP_SIZE;
			xFlower += STEP_SIZE;
			xFlower1 += STEP_SIZE;
			xDoor += STEP_SIZE;
		}
		else if (knight->MapCanMoveLeft(this) && !knight->isAttacking) { // 地圖可以往左動(人物往右)
			if (x8 == 0) { // 當第八張圖在0位置時,地圖不能動
				STEP_SIZE = 0;
			}
			x1 -= STEP_SIZE;
			x2 -= STEP_SIZE;
			x3 -= STEP_SIZE;
			x4 -= STEP_SIZE;
			x5 -= STEP_SIZE;
			x6 -= STEP_SIZE;
			x7 -= STEP_SIZE;
			x8 -= STEP_SIZE;
			xChainsaw -= STEP_SIZE;
			xFlower -= STEP_SIZE;
			xFlower1 -= STEP_SIZE;
			xDoor -= STEP_SIZE;
		}
		/////Y方向的動作/////
		chainsaw.OnMove();
		if (isChainsawDown) {
			yChainsaw += 5;
			if (yChainsaw == 350)
				isChainsawDown = false;
		}
		else if(!isChainsawDown) {
			yChainsaw -= 5;
			if (yChainsaw == 0)
				isChainsawDown = true;
		}
		/////花朵的動作/////
		flowerIsCatch = knight->flowerIsCatch;
		flower1IsCatch = knight->flower1IsCatch;
		/////各種顯示訊息/////
		if (flowerIsCatch==true && messageTimer >= 0) {
			flowermassage.OnMove2();
			messageTimer--;
		}
		if (flower1IsCatch == true && messageTimerJ >= 0) {
			flowermassageJ.OnMove2();
			messageTimerJ--;
		}
		if (x8 <= 0 && messageTimer1 >= 0) {
			monstermassage.OnMove2();
			messageTimer1--;
		}
		/////門的動作/////
		door.OnMove();
		/////食物的動作/////
		foodIsEaten = knight->foodIsEaten; // 接收食物是否被吃掉
		dxFood = xFood - centerX;		   // 位移量=目前x座標-中心座標
		if (-45 > dxFood) {				   // 當位移量大於-60 轉向
			dFood = 1;
		}
		else if (50 < dxFood) {			   // 當位移量大於70 轉向
			dFood = 0;
		}
		if (dFood == 1 && foodLife>0) {		// 當向右走
			xFood += 2;
		}
		else if (dFood == 0 && foodLife>0) {// 當向左走
			xFood -= 2;
		}
		if (knight->MapCanMoveRight(this) && !knight->isAttacking) {	 // 隨著人物走動出現(同地圖位移方式)
			centerX += STEP_SIZE;
			xFood += STEP_SIZE;
		}
		else if (knight->MapCanMoveLeft(this) && !knight->isAttacking) { // 隨著人物走動出現(同地圖位移方式) 
			centerX -= STEP_SIZE;
			xFood -= STEP_SIZE;
		}
		hitFood(knight); // 食物被攻擊
	}

	void CMap::SetMovingFast(bool flag) {
		isMovingFast = flag;
	}

	void CMap::hitFood(CKnight *knight) { // 攻擊食物
		if (knight->isAttacking && knight->isMovingRight && 
			knight->x + 90 > xFood && knight->x + 90 < xFood + 30) {
			foodLife -= 1;
		}
		if (knight->isAttacking && knight->isMovingLeft &&
			knight->x < xFood + 30 && knight->x > xFood) {
			foodLife -= 1;
		}
	}

	bool CMap::isEmpty(int x, int y) {
		return mapData[y / 40][x / 40] == 0;
	}

	bool CMap::isUnderGround(int x, int y) {
		return mapData[y / 40][x / 40] == 2;
	}

	bool CMap::isWin(int x, int y) {
		return mapData[y / 40][x / 40] == 3;
	}

	bool CMap::isCutted(int x, int y) {
		return y + 90 >= yChainsaw && y +90 <= yChainsaw +130 && x + 55 > xChainsaw && x + 55 < xChainsaw + 130 ||
			   y <= yChainsaw + 130 && y >= yChainsaw && x + 55 > xChainsaw && x + 55 < xChainsaw + 130;
	}

	void CMap::OnShow()
	{
		switch (level) {
			case 0:
				HK_BG0_1.SetTopLeft(x1, 0);HK_BG0_1.ShowBitmap();
				HK_BG0_2.SetTopLeft(x2, 0);HK_BG0_2.ShowBitmap();
				HK_BG0_3.SetTopLeft(x3, 0);HK_BG0_3.ShowBitmap();
				HK_BG0_4.SetTopLeft(x4, 0);HK_BG0_4.ShowBitmap();
				HK_BG0_5.SetTopLeft(x5, 0);HK_BG0_5.ShowBitmap();
				HK_BG0_6.SetTopLeft(x6, 0);HK_BG0_6.ShowBitmap();
				HK_BG0_7.SetTopLeft(x7, 0);HK_BG0_7.ShowBitmap();
				HK_BG0_8.SetTopLeft(x8, 0);HK_BG0_8.ShowBitmap();
				// 電鋸
				chainsaw.SetTopLeft(xChainsaw, yChainsaw);
				chainsaw.OnShow();
				// 如果花沒被撿起
				if (!flowerIsCatch) {
					flower.SetTopLeft(xFlower, yFlower);
					flower.ShowBitmap();
				}
				// 如果花"被"撿起
				if (flowerIsCatch && messageTimer >= 0) {
					flowermassage.SetTopLeft(40, 100);
					flowermassage.OnShow();
				}
				// 門
				door.SetTopLeft(xDoor, yDoor);
				door.OnShow();
				break;
			case 1:
				HK_BG1_1.SetTopLeft(x1, 0);HK_BG1_1.ShowBitmap();
				HK_BG1_2.SetTopLeft(x2, 0);HK_BG1_2.ShowBitmap();
				HK_BG1_3.SetTopLeft(x3, 0);HK_BG1_3.ShowBitmap();
				HK_BG1_4.SetTopLeft(x4, 0);HK_BG1_4.ShowBitmap();
				HK_BG1_5.SetTopLeft(x5, 0);HK_BG1_5.ShowBitmap();
				HK_BG1_6.SetTopLeft(x6, 0);HK_BG1_6.ShowBitmap();
				HK_BG1_7.SetTopLeft(x7, 0);HK_BG1_7.ShowBitmap();
				HK_BG1_8.SetTopLeft(x8, 0);HK_BG1_8.ShowBitmap();
				// 蟲蟲還活著
				if (dFood == 0 && foodLife > 0) {
					food1.SetTopLeft(xFood, yFood);
					food1.ShowBitmap();
				}
				// 蟲蟲還活著
				else if (dFood == 1 && foodLife > 0) {
					food3.SetTopLeft(xFood, yFood);
					food3.ShowBitmap();
				}
				// 蟲蟲可以吃了
				if (foodLife <= 0) { 
					if (!foodIsEaten) { // 當食物還沒被吃掉
						if (dFood == 1) {
							eaten3.SetTopLeft(xFood, yFood);
							eaten3.ShowBitmap();
						}
						else if (dFood == 0) {
							eaten1.SetTopLeft(xFood, yFood);
							eaten1.ShowBitmap();
						}
					}
					//重新設定蟲蟲座標
					else { 
						foodLife = 60;
						xFood = 3050;
						yFood = 327;
						centerX = 3250;
						dFood = 1;
					}
				}
				// 血量低於20
				else if (foodLife <= 20 && foodLife > 0) { 
					foodLife3.SetTopLeft(xFood, yFood - 5);
					foodLife3.ShowBitmap();
				}
				// 血量低於40
				else if (foodLife <= 40) {
					foodLife2.SetTopLeft(xFood, yFood - 5);
					foodLife2.ShowBitmap();
				}
				// 血量低於60
				else if (foodLife <= 60) {
					foodLife1.SetTopLeft(xFood, yFood - 5);
					foodLife1.ShowBitmap();
				}
				//如果彈跳花"沒"被撿起
				if (!flower1IsCatch) {
					flower1.SetTopLeft(xFlower1, yFlower1);
					flower1.ShowBitmap();
				}
				//如果彈跳花"被"撿起
				if (flower1IsCatch && messageTimerJ >= 0) {
					flowermassageJ.SetTopLeft(40, 80);
					flowermassageJ.OnShow();
				}
				// 當要到魔王關時
				if (x8 <= 0 && messageTimer1 >= 0) {
					monstermassage.SetTopLeft(40, 100);
					monstermassage.OnShow();
				}
				break;
			case 2:
				HK_BG1_8.SetTopLeft(x1, 0);
				HK_BG1_8.ShowBitmap();
				break;
		}
	}
}
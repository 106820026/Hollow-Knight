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
		centerX = 730;				// ���߮y��
		M_y = 220;					// Y�y��
		M_x = 730;					// X�y��
		M_dx = 0;					// X��V�첾�q
		d = 0;						// ��V(0���k 1����)
		hitleft = 50;				// �Ѿl������
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
			M_dx = M_x - centerX;		// �첾�q=�ثex�y��-���߮y��
			if (-65 > M_dx) {			// ��첾�q�j��-65 ��V
				d = 0;
			}
			else if (65 < M_dx) {		// ��첾�q�j��65 ��V
				d = 1;
			}
			if (d == 0) {				// ��V�k��
				M_x += STEP_SIZE;
			}
			else if (d == 1) {			// ��V����
				M_x -= STEP_SIZE;
			}
		}
		if (knight->isMovingLeft && !knight->isAttacking) {		  // �H�ۤH�����ʥX�{(�P�a�Ϧ첾�覡)
			centerX += STEP_SIZE;
			M_x += STEP_SIZE;
		}
		else if (knight->isMovingRight && !knight->isAttacking) { // �H�ۤH�����ʥX�{(�P�a�Ϧ첾�覡) 
			centerX -= STEP_SIZE;
			M_x -= STEP_SIZE;
		}
	}
	void CMonster::SetisHit(CWeapon *weapon) {
			 // �q����g��
		if ((weapon->isShootingRight && weapon->x + 160 >= M_x && weapon->x + 160 <= M_x + 130 && weapon->y + 55 > M_y && weapon->y + 55 < M_y + 98) ||
			 // �q�k��g��
			(weapon->isShootingLeft && weapon->x <= M_x + 90 && weapon->x >= M_x && weapon->y + 55 > M_y && weapon->y + 55 < M_y + 98))
			isHit = true;
		else
			isHit = false;
	}

	void CMonster::OnShow()
	{
		if (isHit)					// �p�G�Q����
			hitleft -= 1;			// ���Ǫ��ͩR
		if (hitleft > 0)			// �٦��R��
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
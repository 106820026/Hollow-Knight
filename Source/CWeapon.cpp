#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "gamelib.h"
#include "CKnight.h"
#include "CWeapon.h"

namespace game_framework {
	CWeapon::CWeapon() {
		isShootingLeft = isShootingRight = false;
	}

	CWeapon::~CWeapon() {

	}

	void CWeapon::LoadBitmap() {
		weapon1.LoadBitmap(IDB_WEAPON1, RGB(0, 0, 0));
		weapon2.LoadBitmap(IDB_WEAPON2, RGB(0, 0, 0));
	}

	void CWeapon::SetShootingLeft(bool flag) {
		isShootingLeft = flag;
	}

	void CWeapon::SetShootingRight(bool flag) {
		isShootingRight = flag;
	}

	void CWeapon::Initialize(CKnight *knight) {
		x = knight->x;	// ���D��x
		y = knight->y;	// ���D��y
		init_x = x;		// ���_�l�Z��
	}

	void CWeapon::OnMove(CKnight *knight) {
		int STEP_SIZE = 20;						// �@�B���Z��
		if (isShootingRight) {					// ��D���k�g��
			x += STEP_SIZE;
			isShootingLeft = false;
			if (x - init_x == 240 || x >= 2360) {
				isShootingRight = false;
			}
		}
		else if (isShootingLeft) {				// ��S�����g��
			x -= STEP_SIZE;
			isShootingRight = false;
			if (x <= 0 || init_x - x == 240) {
				isShootingLeft = false;
			}
		}
	}

	void CWeapon::OnShow() {
		if (isShootingLeft) {
			weapon1.SetTopLeft(x-104, y);
			weapon1.ShowBitmap();
		}
		else if (isShootingRight) {
			weapon2.SetTopLeft(x, y);
			weapon2.ShowBitmap();
		}
	}
}
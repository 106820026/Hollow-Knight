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
		const int INITIAL_VELOCITY = 15;	// ��l�W�ɳt��
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		lifeLeft = 100;
		x = 240;
		y = 230;
		dx = x;
		isMovingLeft = isMovingRight = isAttacking = rising = isMovingFast = flower1IsCatch =
		isTouch = isTouch2 = isCatch = flowerIsCatch = isBurn = foodIsEaten = false;
	}

	bool CKnight::MapCanMoveRight(CMap *map) {  // �p�G�D�����b������,���T�{����O�_����,�B���240��4720����
		return isMovingLeft && map->isEmpty(dx - 1, y) && map->isEmpty(dx - 1, y + 45) && 
			   map->isEmpty(dx - 1, y + 91) && dx >= 240 && dx <= 4720 && !isAttacking && level != 2;
	}

	bool CKnight::MapCanMoveLeft(CMap *map) {  // �p�G�D�����b���k��,���T�{�k��O�_����,�B���240��4720����
		return isMovingRight && map->isEmpty(dx + 57, y) && map->isEmpty(dx + 57, y + 45) && 
			   map->isEmpty(dx + 57, y + 91) && dx >= 240 && dx <= 4720 && !isAttacking && level != 2;
	}

	void CKnight::LoadBitmap(){
		char *filename1[2] = { ".\\bitmaps\\HK_knight1.bmp",".\\bitmaps\\HK_knight1_2.bmp" };
		for (int i = 0; i < 2; i++)																// ���J�����ʵe(��2�i�ϧκc��)
			knight1.AddBitmap(filename1[i], RGB(255, 255, 255));								// ���J�D������
		char *filename2[2] = { ".\\bitmaps\\HK_knight1_3.bmp",".\\bitmaps\\HK_knight1_4.bmp" };	
		for (int i = 0; i < 2; i++)																// ���J�����ʵe(��2�i�ϧκc��)
			knight1_2.AddBitmap(filename2[i], RGB(255, 255, 255));								// ���J�D������
		char *filename3[2] = { ".\\bitmaps\\HK_knight3.bmp",".\\bitmaps\\HK_knight3_2.bmp" };
		for (int i = 0; i < 2; i++)																// ���J�����ʵe(��2�i�ϧκc��)
			knight3.AddBitmap(filename3[i], RGB(255, 255, 255));								// ���J�D���k��
		char *filename4[2] = { ".\\bitmaps\\HK_knight3_3.bmp",".\\bitmaps\\HK_knight3_4.bmp" };
		for (int i = 0; i < 2; i++)																// ���J�����ʵe(��2�i�ϧκc��)
			knight3_2.AddBitmap(filename4[i], RGB(255, 255, 255));								// ���J�D���k��
		char *filename5[2] = { ".\\bitmaps\\HK_knight1_2.bmp",".\\bitmaps\\HK_knight1trans.bmp" };
		for (int i = 0; i < 2; i++)																// ���J�Q�����ʵe(��2�i�ϧκc��)
			knightburn1.AddBitmap(filename5[i], RGB(255, 255, 255));							// ���J�D������
		char *filename6[2] = { ".\\bitmaps\\HK_knight3_2.bmp",".\\bitmaps\\HK_knight3trans.bmp" };
		for (int i = 0; i < 2; i++)																// ���J�Q�����ʵe(��2�i�ϧκc��)
			knightburn3.AddBitmap(filename6[i], RGB(255, 255, 255));							// ���J�D���k��
		char *filename7[2] = { ".\\bitmaps\\HK_knight2.bmp",".\\bitmaps\\HK_knight2trans.bmp" };
		for (int i = 0; i < 2; i++)																// ���J�Q�����ʵe(��2�i�ϧκc��)
			knightburn2.AddBitmap(filename7[i], RGB(255, 255, 255));							// ���J�D������
		knight2.LoadBitmap(IDB_KNIGHT2, RGB(255, 255, 255));// ���J�D������
		knight_sprint1.LoadBitmap(IDB_KNIGHT_SPRINT1, RGB(0, 0, 0)); // �Ĩ륪
		knight_sprint3.LoadBitmap(IDB_KNIGHT_SPRINT3, RGB(0, 0, 0)); // �Ĩ�k
		life1.LoadBitmap(IDB_LIFE1, RGB(255, 255, 255));
		life2.LoadBitmap(IDB_LIFE2, RGB(255, 255, 255));
		life3.LoadBitmap(IDB_LIFE3, RGB(255, 255, 255));
	}

	void CKnight::OnMove(CMap * map){
		level = map->level;
		//////////�]�w�B��//////////
		if (isMovingFast) {
			STEP_SIZE = 8;
		}
		else {
			STEP_SIZE = 4;
		}
		//////////Ĳ�I�Ǫ�//////////
		if (isTouch) {
			lifeLeft -= 1;
		}
		if (isTouch2) {
			lifeLeft -= 1;
		}
		//////////����//////////
		if (isAttacking && isMovingLeft) {			// �V��
			knight1_2.OnMove2();
		}
		else if (isAttacking && isMovingRight) {	// �V�k
			knight3_2.OnMove2();
		}
		//////////���k����//////////
		else if (isMovingLeft && map->isEmpty(dx - 1, y) && map->isEmpty(dx - 1, y + 45) && map->isEmpty(dx - 1, y + 91)) {// �������B���謰��(dx - 1, y + 60)
			knight1.OnMove();
			knightburn1.OnMove2();
			if (level == 2) {									// ��b�ĤG�����]������
				if (x > 0) {									// dx����>0,�o�ˤ~���|�]�X�a��
					x -= STEP_SIZE;								// �a�Ϥ���,���H����
				}
			}
			else if (dx > 240 && dx < 4720) {					// �첾�q����240��4720��(�a�ϥi�ʪ���)
				dx -= STEP_SIZE;								// ���ʦ첾�q
				x = 240;										// �a�Ϧb�ʮ� �H���O���bx=240
				if (dx < 240) {									// ��첾�q�p��240�� 
					dx = 239;									// ���]��239(���F��KXD)
					x = 240;									// �a�ϰʮ�,�H���O���bx = 240
				}
			}
			else if(dx > 0) {									// dx����>0,�o�ˤ~���|�]�X�a��
				x -= STEP_SIZE;									// �a�Ϥ���,���H����
				dx -= STEP_SIZE;								// �첾�q�٬O�n�~���
			}
		}
		else if (isMovingRight && map->isEmpty(dx + 57, y) && map->isEmpty(dx + 57, y + 45) && map->isEmpty(dx + 57, y + 91)) {// ���k���B�k�謰��
			knight3.OnMove();
			knightburn3.OnMove2();
			if (level == 2) {									// ��b�ĤG�����]������
				if (x + 90 < 640) {								// dx����<640,�o�ˤ~���|�]�X�a��
					x += STEP_SIZE;								// �a�Ϥ���,���H����
				}
			}
			else if (dx > 240 && dx < 4720) {					 // �첾�q����240��4720��(�a�ϥi�ʪ���)
				dx += STEP_SIZE;								 // ���ʦ첾�q
				x = 240;										 // �a�Ϧb�ʮ� �H���O���bx=240
				if (dx > 4720) {								 // ��첾�q�j��4720��
					dx = 4721;									 // ���]��4721(���F��KXD)
					x = 240;									 // �a�ϰʮ�,�H���O���bx = 240
				}
			}
			else if(dx+90<5120){								 // dx����<5120,�o�ˤ~���|�]�X�a��
				x += STEP_SIZE;									 // �a�Ϥ���,���H����
				dx += STEP_SIZE;								 // �첾�q�٬O�n�~���
			}
		}
		knightburn2.OnMove2();									// �����{�{�ʵe
		//////////���D//////////
		if (rising && map->isEmpty(dx,y) && map->isEmpty(dx+45, y) && map->isEmpty(dx+51, y)) {// �W�ɪ��A
			if (velocity > 0) {
				y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
			}
			else {
				rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
				velocity = 1;	// �U������t(velocity)��1
			}
		}
		else {					// �U�����A
			rising = false;
			if (map->isEmpty(dx, y + 96) && map->isEmpty(dx+45, y + 96) && map->isEmpty(dx+51, y + 96)) {// ��y�y���٨S�I��a�O
				y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
				velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
			}
			else {
				y = (y+96)/40*40-96;		 // ��y�y�ЧC��a�O�A�󥿬��a�O�W(y/40+1)*40-1
				velocity = initial_velocity; // ���]�W�ɪ�l�t��
			}
		}
		//////////�ߪF��//////////
		if (foodIsEaten) {
			lifeLeft = lifeLeft + 40; // �^�_40�ͩR
			foodIsEaten = false;
		}
		switch (map->level) {
		case 0:
			if (isCatch && dx > 1240 && dx + 55 < 1320 && y + 90 <120) {
				flowerIsCatch = true; // �ߨ��t�פ���
			}
			break;
		case 1:
			if (isCatch && x > map->xFood - 30 && x < map->xFood + 47 && 
				y + 90 > map->yFood && map->foodLife < 0) {
				foodIsEaten = true; // �ߨ�����
				isCatch = false;
			}
			if (isCatch && x > map->xFlower1-20 && x < map->xFlower1+42) {
				flower1IsCatch = true; // �ߨ���������
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
		if (monster->hitleft > 0) { // �b�Ǫ��٬��۪��ɭ�
			if (x + 90 > monster->M_x && x < monster->M_x + 90) {
				isTouch = true;
			}
			else
				isTouch = false;
		}
	}

	void CKnight::SetTouchMonster2(CMonster2 *monster) {
		if (monster->hitleft > 0) { // �b�Ǫ��٬��۪��ɭ�
			if (x + 56 >= monster->M_x + 35 && x + 28 <= monster->M_x + 115) {
				if(y+45>monster->M_y&&y+45<monster->M_y+134)
					isTouch2 = true;
			}
			else
				isTouch2 = false;
		}
	}

	void CKnight::SetTouchFire(CMonster2 *fire) {
		if (lifeLeft > 0) { // �b�D���٬��۪��ɭ�
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
		else if (isAttacking && isMovingLeft) {			// �V������
			knight1_2.SetTopLeft(x, y + 5);
			knight1_2.OnShow();
		}
		else if (isAttacking && isMovingRight) {		// �V�k����
			knight3_2.SetTopLeft(x, y + 5);
			knight3_2.OnShow();
		}
		else if (isMovingLeft) {						// ������
			if (isBurn || isTouch || isTouch2) {
				knightburn1.SetTopLeft(x, y + 5);
				knightburn1.OnShow();
			}
			else {
				knight1.SetTopLeft(x, y + 5);
				knight1.OnShow();
			}
		}
		else if (isMovingRight) {						// ���k��
			if (isBurn || isTouch || isTouch2) {
				knightburn3.SetTopLeft(x, y + 5);
				knightburn3.OnShow();
			}
			else {
				knight3.SetTopLeft(x, y + 5);
				knight3.OnShow();
			}
		}
		else{											// ���D + ����
			if (isBurn || isTouch || isTouch2) {
				knightburn2.SetTopLeft(x, y);
				knightburn2.OnShow();
			}
			else {
				knight2.SetTopLeft(x, y);
				knight2.ShowBitmap();
			}
		}
		////////�H���ͩR////////
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
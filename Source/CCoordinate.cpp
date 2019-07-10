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
			//   �Ĥ@�i��  \\ //  �ĤG�i��  \\ //  �ĤT�i��  \\          /
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
		if (rising) {			// �W�ɪ��A
			if (velocity > 0) {
				y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
			}
			else {
				rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
				velocity = 1;	// �U������t(velocity)��1
			}
		}
		else {				// �U�����A
			if (mapData[(y + 1) / 80][x / 80] == 0) {  // ��y�y���٨S�I��a�O
				y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
				velocity++;		// �����O�v�T�A�U�����U���t�׼W�[
			}
			else {
				y = y;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
				rising = true;	// �����ϼu�A�U���אּ�W��
				velocity = initial_velocity; // ���]�W�ɪ�l�t��
			}
		}
	}
}
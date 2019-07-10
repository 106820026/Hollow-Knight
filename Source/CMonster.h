#ifndef _CMONSTER_H_
#define _CMONSTER_H_
#include "includeFile.h"
namespace game_framework {
	class CMonster
	{
	public:
		CMonster();
		void Initialize();				// �]�w���⬰��l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove(CKnight *knight);	// ���ʨ���
		void OnShow();					// �N����ϧζK��e��
		void SetisHit(CWeapon *weapon);	// �]�w�O�_�Q�D��������
		int floor;						// �a�O��Y�y��
		bool isHit;						// �O�_�Q�D��������
		int centerX;					// �Ǫ����߮y��
		int M_dx,M_x, M_y;				// �Ǫ��y��              
		int d;
		int STEP_SIZE;					// �@�B���Z��
		int hitleft;					// �Ѿl������
	protected:
		CMovingBitmap Monster1;			// �D�����V������
		CMovingBitmap Monster3;			// �D�����V�k����
		CMovingBitmap blood1;			// ���
		CMovingBitmap blood2;
		CMovingBitmap blood3;
		CMovingBitmap blood4;
		CMovingBitmap blood5;
		CMovingBitmap blood6;
	};
}
#endif
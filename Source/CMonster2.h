#ifndef _MONSTER2_H_
#define _MONSTER2_H_
#include "includeFile.h"
namespace game_framework {
	class CMonster2 {
	public:
		CMonster2();
		~CMonster2();
		void Initialize(int gamelevel);		// ��l�ƨ���
		void LoadBitmap();					// ���J�ϧ�
		void OnMove(CKnight *knight, CMap *);// ���ʨ���
		void OnShow();						// �N����ϧζK��e��
		void SetisHit(CWeapon *weapon);		// �]�w�O�_�Q�D��������
		int Width();						// ���y�e
		int d;								// ��V(0�� 1�k)
		int M_x, M_y;						// �Ǫ����W���y��
		int floor;							// �Ǫ��a�O�y��
		int initial_velocity;				// ��l�t��
		int velocity;						// �ثe�t��
		int rising;							// 0��b�a�O�B1��W�ɡB2��U��
		int F_x, F_y;						// ���y���W�y��
		int attackTimer;					// �����p�ɾ�
		int jumpTimer;						// ���D�p�ɾ�
		bool fireIsOnFloor;					// �����@������
		int A_x, A_y;						// ĵ�i�y��
		int hitleft;						// �Ѿl������
		int i;
		int level;							// �ثe����
		bool isHit;							// �O�_�Q����
		CAnimation monsterLeft;
		CAnimation monsterRight;
		CAnimation fire;
		CMovingBitmap alert;				// �Ǫ����Dĵ�i
		CMovingBitmap blood1;				// ���
		CMovingBitmap blood2;
		CMovingBitmap blood3;
		CMovingBitmap blood4;
		CMovingBitmap blood5;
		CMovingBitmap blood6;
	};
}
#endif // !_MONSTER2_H_
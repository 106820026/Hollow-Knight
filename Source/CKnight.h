#ifndef _CKNIGHT_H_
#define _CKNIGHT_H_
#include "includeFile.h"
namespace game_framework {
	class CKnight
	{
	public:
		CKnight();
		~CKnight();
		void Initialize();					// ��l�ƨ���
		bool MapCanMoveRight(CMap *);		// �a�ϥi�H���k��(�H��������)
		bool MapCanMoveLeft(CMap *);		// �a�ϥi�H������(�H�����k��)
		void LoadBitmap();					// ���J�ϧ�
		void OnMove(CMap *);				// ���ʨ���
		void SetMovingLeft(bool flag);		// �]�w�O�_���b��������
		void SetMovingRight(bool flag);		// �]�w�O�_���b���k����
		void SetJumping(bool flag);			// �]�w�O�_���b��
		void SetAttacking(bool flag);		// �]�w�O�_����
		void SetMovingFast(bool flag);		// �]�w�O�_�֨�
		void SetTouchMonster(CMonster *monster);// �]�w�O�_����Ǫ�
		void SetTouchMonster2(CMonster2 *monster);// �]�w�O�_����Ǫ�2
		void SetTouchFire(CMonster2 *fire); // �]�w�O�_������y
		void SetCatch(bool flag);			// �]�w�O�_�ߨ�
		bool isDeath(CMap*);				// �]�w�O�_���`
		bool isWin(CMap*);					// �]�w�O�_�ӧQ
		void OnShow();						// �N����ϧζK��e��
		bool isMovingLeft;					// �O�_���b��������
		bool isMovingRight;					// �O�_���b���k����
		bool isAttacking;					// �O�_����
		bool isMovingFast;					// �O�_�֨�
		bool isTouch;						// �Q�Ǫ�����
		bool isTouch2;						// �Q�Ǫ�����
		bool isBurn;						// �Q���y�N��
		bool isCatch;						// �ߨ�
		bool flowerIsCatch;					// ��Q�߰_�ӤF
		bool flower1IsCatch;				// ��Q�߰_�ӤF
		bool foodIsEaten;					// �����w�Q�Y
		bool rising;						// true��W�ɡBfalse��U��
		int x, y;							// �D�����W���y��
		int dx;								// X��V�첾�y��
		int STEP_SIZE;						// �@�B���Z��
		int initial_velocity;				// ��l�t��
		int velocity;						// �ثe�t��
		int lifeLeft;						// �Ѿl�ͩR
		int level;							// �ثe����
	private:
		CAnimation knight1;					// �D�����V������
		CAnimation knightburn1;				// �Q���y�{��|�{
		CAnimation knight1_2;				// �D�����V������
		CMovingBitmap knight2;				// �D�����V�e
		CAnimation knightburn2;				// �Q���y�{��|�{
		CAnimation knight3;					// �D�����V�k����
		CAnimation knightburn3;				// �Q���y�{��|�{
		CAnimation knight3_2;				// �D�����V�k����
		CMovingBitmap knight_sprint1;		// �D���Ĩ륪
		CMovingBitmap knight_sprint3;		// �D���Ĩ�k
		CMovingBitmap life1;				// �ͩR
		CMovingBitmap life2;				// �ͩR
		CMovingBitmap life3;				// �ͩR
	};
}
#endif
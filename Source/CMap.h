#ifndef _CMAP_H_
#define _CMAP_H_
#include "includeFile.h"
namespace game_framework {
	class CMap 
	{
	public:
		CMap();
		~CMap();
		void Initialize(int gameLevel);			// ��l��
		void LoadBitmap();	
		void OnMove(CKnight *);
		void SetMovingFast(bool flag);			// �]�w�O�_�[�t
		void hitFood(CKnight *);				// ��������
		bool isEmpty(int x, int y);				// �Ҧb��m����
		bool isUnderGround(int x, int y);		// ���쩳�U
		bool isWin(int x, int y);				// �C���ӧQ
		bool isCutted(int x, int y);			// �Q�q������
		void OnShow();
		bool isMovingFast;						// �O�_�[�t
		bool isChainsawDown;					// �q�����U
		bool flowerIsCatch;						// �t�ת�w�Q��
		bool flower1IsCatch;					// �u����w�Q��
		bool foodIsEaten;						// �����w�Q�Y
		bool foodIsHit;							// �����Q����
		int mapData[12][128];
		int level;								// ���d
		int STEP_SIZE;							// �@�B���Z��
		int x1, x2, x3, x4, x5, x6, x7, x8;		// �a��X�y��
		int	xChainsaw, yChainsaw;				// �q���y��
		int	xFlower, yFlower;					// �ᦷ�y��
		int	xFlower1, yFlower1;					// �ᦷ�y��
		int	xDoor, yDoor;						// ���y��
		int	messageTimer, messageTimer1, messageTimerJ; // �t��/�]��/���D
		int	xFood, yFood, dFood, dxFood, centerX, foodLife;

	private:
		// �Ĥ@��
		CMovingBitmap HK_BG0_1;
		CMovingBitmap HK_BG0_2;
		CMovingBitmap HK_BG0_3;
		CMovingBitmap HK_BG0_4;
		CMovingBitmap HK_BG0_5;
		CMovingBitmap HK_BG0_6;
		CMovingBitmap HK_BG0_7;
		CMovingBitmap HK_BG0_8;
		// �ĤG��
		CMovingBitmap HK_BG1_1;
		CMovingBitmap HK_BG1_2;
		CMovingBitmap HK_BG1_3;
		CMovingBitmap HK_BG1_4;
		CMovingBitmap HK_BG1_5;
		CMovingBitmap HK_BG1_6;
		CMovingBitmap HK_BG1_7;
		CMovingBitmap HK_BG1_8;
		// ����
		CAnimation	  chainsaw;	// �q��
		CMovingBitmap flower;	// �Y�F�i�H�s�W�Ĩ�ޯ઺�p��
		CMovingBitmap flower1;	// �Y�F�i�H�G�q������
		CAnimation    flowermassage;//�t�פ��᪺��T
		CAnimation    flowermassageJ;//�������᪺��T
		CAnimation    monstermassage;//�Ǫ�����T
		CAnimation    door;		// ��
		// �����
		CMovingBitmap food1;	// �ɦ�p��
		CMovingBitmap food3;    // �ɦ�p��
		CMovingBitmap foodLife1;// ���
		CMovingBitmap foodLife2;// ���
		CMovingBitmap foodLife3;// ���
		CMovingBitmap eaten1;	//�����p��
		CMovingBitmap eaten3;	//�����p��
	};
}
#endif

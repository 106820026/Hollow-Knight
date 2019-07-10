#ifndef _CWEAPON_H_
#define _CWEAPON_H_
#include "includeFile.h"
namespace game_framework {
	class CWeapon
	{
		public:
			CWeapon();
			~CWeapon();
			void LoadBitmap();
			void SetShootingLeft(bool flag);		// �]�w�O�_�V���g��
			void SetShootingRight(bool flag);		// �]�w�O�_�V�k�g��
			void Initialize(CKnight *);				// ���o�D����m
			void OnMove(CKnight *);
			void OnShow();
			int x, y;								// ���u��m
			int i;
			int init_x;								// ��l��m
			bool isShootingLeft;					// �O�_�V���g��
			bool isShootingRight;					// �O�_�V�k�g��
		private:
			CMovingBitmap weapon1;					// �V������
			CMovingBitmap weapon2;					// �V�k����
	};
}
#endif
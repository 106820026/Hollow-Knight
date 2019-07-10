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
			void SetShootingLeft(bool flag);		// 設定是否向左射擊
			void SetShootingRight(bool flag);		// 設定是否向右射擊
			void Initialize(CKnight *);				// 取得主角位置
			void OnMove(CKnight *);
			void OnShow();
			int x, y;								// 飛彈位置
			int i;
			int init_x;								// 初始位置
			bool isShootingLeft;					// 是否向左射擊
			bool isShootingRight;					// 是否向右射擊
		private:
			CMovingBitmap weapon1;					// 向左攻擊
			CMovingBitmap weapon2;					// 向右攻擊
	};
}
#endif
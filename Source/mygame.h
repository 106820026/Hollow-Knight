#include "CKnight.h"
#include "CMap.h"
#include "CMonster.h"
#include "CWeapon.h"
#include "CMonster2.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// �w�q�U�ح��Ī��s��
		AUDIO_MENU,				// 0
		AUDIO_INGAME,			// 1
		AUDIO_FOOTSTEPS	,		// 2
		AUDIO_JUMP,				// 3
		AUDIO_HOVER,			// 4
		AUDIO_MONSTERSTILLALIVE,// 5
		AUDIO_PICK,				// 6
		AUDIO_CONGRAT,			// 7
		AUDIO_SHOOT,			// 8
		AUDIO_HOWL,				// 9
		AUDIO_SLASH,			// 10
		AUDIO_HITFOOD,			// 11
		AUDIO_HURT,				// 12
		AUDIO_INGAME2,			// 13
		AUDIO_FINALBOSS,		// 14
		AUDIO_END				// 15
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		int downMouseX, downMouseY;						// �ƹ����U��m
		int moveMouseX, moveMouseY;						// �ƹ����ʦ�m
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap menu;								// hollow knight�����
		CMovingBitmap leftsign;							// ��楪�Ÿ�
		CMovingBitmap rightsign;						// ���k�Ÿ�
		CMovingBitmap control;							// ����]�m��
		CMovingBitmap backToMenu1, backToMenu2;			// ��^���
		CMovingBitmap scroll1, scroll2;					// ���b
		CMovingBitmap skills;							// �K�޹�
		bool		  isMusicLoaded;					// �O�_�w�g���J����
		bool		  isPlayed;							// �O�_����L����
		bool		  showingCtrl;						// ���bshow����]�m��
		bool		  showingSkill;						// ���bshow�K�޹�
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C������1��
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);				// �B�z��LDown���ʧ@
		void OnKeyUp(UINT, UINT, UINT);					// �B�z��LUp���ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap	tomb;		// �X��
		CMonster        monster;    // �Ǫ�
		CKnight			knight;		// �D��
		CMap			map;		// �a��
		CWeapon			weapon;		// �Z��
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C������2��
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun1 : public CGameState {
	public:
		CGameStateRun1(CGame *g);
		~CGameStateRun1();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);				// �B�z��LDown���ʧ@
		void OnKeyUp(UINT, UINT, UINT);					// �B�z��LUp���ʧ@
		int downMouseX, downMouseY;						// �ƹ����U��m
		int moveMouseX, moveMouseY;						// �ƹ����ʦ�m
		bool canDoubleJump;								// �i�H�G�q��
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMonster2       monster;    // �Ǫ�
		CKnight			knight;		// �D��
		CMap			map;		// �a��
		CWeapon			weapon;		// �Z��
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C����2�����]��
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateRun1_2 : public CGameState {
	public:
		CGameStateRun1_2(CGame *g);
		~CGameStateRun1_2();
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);				// �B�z��LDown���ʧ@
		void OnKeyUp(UINT, UINT, UINT);					// �B�z��LUp���ʧ@
		bool canDoubleJump;								// �i�H�G�q��
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap	tomb;		// �X��
		CMap			map;		// �a��
		CMonster2       monster;    // �Ǫ�
		CKnight			knight;		// �D��
		CWeapon			weapon;		// �Z��
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����L�����A(Game Win)
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateWin : public CGameState {
	public:
		CGameStateWin(CGame *g);
		void OnBeginState();
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		int moveMouseX, moveMouseY;						// �ƹ����ʦ�m
		bool isPlayed;									// �O�_����L����
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap   congrats;						// �L�����
		CMovingBitmap	congrats1;						// �L�����->�^�D���
		CMovingBitmap	congrats2;						// �L�����->�U�@��
	};

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	// �C��Member function��Implementation���n����
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);
		void OnBeginState();
		void OnInit();
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int counter;									// �˼Ƥ��p�ƾ�
		CMovingBitmap gameover;							// �����ϥ�
	};

	////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����Ȱ����A(Game Pause)
	////////////////////////////////////////////////////////////////////////////

	class CGameStatePause : public CGameState {
	public:
		CGameStatePause(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();									// ���J�Ϥ�(LoadBitmap)
		void OnKeyDown(UINT, UINT, UINT);				// �B�z��LDown���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		int moveMouseX, moveMouseY;						// �ƹ����ʦ�m
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CPoint mouseX, mouseY;							// �ƹ��y��
		CMovingBitmap pauseMenu;						// �Ȱ����
		CMovingBitmap leftsign;							// ��楪�Ÿ�
		CMovingBitmap rightsign;						// ���k�Ÿ�
		bool		  isPlayed;							// �O�_����L����
	};

	////////////////////////////////////////////////////////////////////////////
	// �o��class���C������ܪ��A(Game Select)
	////////////////////////////////////////////////////////////////////////////

	class CGameStateSelect : public CGameState {
	public:
		CGameStateSelect(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();									// ���J�Ϥ�(LoadBitmap)
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		int moveMouseX, moveMouseY;						// �ƹ����ʦ�m
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap level1, level2, level3;			// ���d��
		CMovingBitmap preview;							// �w���r��
		CMovingBitmap backToMenu1, backToMenu2;			// ��^���
		CMovingBitmap monster1, monster3;				// �w���Ǫ�
		CAnimation	  Monster1, Monster3;				// �w���y��
		int xMonster, yMonster, dMonster;				// �Ǫ��y��
		int XMonster, YMonster, DMonster;				// �Ǫ��y��
		bool		  isPlayed;							// �O�_����L����
	};

	////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game End)
	////////////////////////////////////////////////////////////////////////////
	class CGameStateEnd : public CGameState {
	public:
		CGameStateEnd(CGame *g);
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();									// ���J�Ϥ�(LoadBitmap)
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		int moveMouseX, moveMouseY;						// �ƹ����ʦ�m
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		int timer1;
		int timer2;
		bool isPlayed;									// �O�_����L����
		CAnimation end1;								// �����ʵe1
		CAnimation end2;								// �����ʵe2
		CMovingBitmap endMenu1;							// ���1
		CMovingBitmap endMenu2;							// ���2
		CMovingBitmap endMenu3;							// ���3
	};
}
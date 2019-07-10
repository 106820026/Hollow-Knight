namespace game_framework {
	class CCoordinate
	{
	public:
		CCoordinate();
		int GetX();						// ���oX�y��
		int GetY();						// ���oY�y��
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetJumping(bool flag);		// �]�w�O�_���b��
		void SetAttacking(bool flag);	// �]�w�O�_����
		void Initialize();				// ��l��
		bool isMovingLeft;				// �O�_���b��������
		bool isMovingRight;				// �O�_���b���k����
		bool isAttacking;				// �O�_����
		void OnMove();					// �]�wX Y�y��
		int x, y;						// �D�����W���y��
		int floor;
		int initial_velocity;
		int velocity;
		bool rising;					// true��W�ɡBfalse��U��
		int mapData[6][24];
	};
}
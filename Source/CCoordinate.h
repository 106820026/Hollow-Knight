namespace game_framework {
	class CCoordinate
	{
	public:
		CCoordinate();
		int GetX();						// 取得X座標
		int GetY();						// 取得Y座標
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetJumping(bool flag);		// 設定是否正在跳
		void SetAttacking(bool flag);	// 設定是否攻擊
		void Initialize();				// 初始化
		bool isMovingLeft;				// 是否正在往左移動
		bool isMovingRight;				// 是否正在往右移動
		bool isAttacking;				// 是否攻擊
		void OnMove();					// 設定X Y座標
		int x, y;						// 主角左上角座標
		int floor;
		int initial_velocity;
		int velocity;
		bool rising;					// true表上升、false表下降
		int mapData[6][24];
	};
}
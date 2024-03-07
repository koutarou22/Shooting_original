#include "BasicAbility.h"
#include <vector>
#include "Bullet.h"

using std::vector;

const int PLAYER_CHR_SIZE{ 48 }; 
const double PLAYER_RECT_SIZE{ 45 };
const double PLAYER_MOVE_SPEED{ PLAYER_CHR_SIZE * 4.5 }; 
const int PLAYER_MAX_BULLET_NUM{ 5 };

enum direction
{
	UP, LEFT, DOWN, RIGHT, NONE
};

class EnemyMaster;


class Player :
	public BasicAbility
{
	vector<Bullet*> Gun_;//プレイヤーの銃
	int GetBlankBullet();
public:
	Player();
	~Player();
	void Initialize();
	void Release();
	direction GetDirection();
	void Update() override;
	void Draw() override;
	void Reset();
	
	vector<Bullet*> GetGunBullet() { return Gun_; }
	
};


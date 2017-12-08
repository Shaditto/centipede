/* Spider.h - Gage O'Connor, September 2017 */
#ifndef _Spider
#define _Spider

#include "TEAL\CommonElements.h"
#include "Mushroom.h"
#include "Grid.h"

// Forward declaration
class Bullet;

class Spider : public GameObject
{
public:
	/*BIG FOUR*/
	Spider();
	Spider(const Spider &) = default;
	Spider & operator =(const Spider &) = default;
	~Spider() = default;

	/* INITIALIZER */
	void Initialize(Tile *tile, float side);

	/* METHODS */
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void EatShroom(Tile *tile);

	// Check Movement Methods
	virtual void CheckMovement();
	virtual void CheckDiagUp();
	virtual void CheckDiagDown();
	virtual void CheckUp();
	virtual void CheckDown();

	// Actual Movement
	virtual void MoveDiagUpRight();
	virtual void MoveDiagDownRight();
	virtual void MoveDiagUpLeft();
	virtual void MoveDiagDownLeft();
	virtual void MoveUp();
	virtual void MoveDown();

	/* COLLISIONS */
	virtual void Collision(GameObject *go) {};
	virtual void Collision(Bullet *other);

private:
	enum Movement
	{
		isMovingUp,
		isMovingDown,
		isDiagUpRight,
		isDiagUpLeft,
		isDiagDownRight,
		isDiagDownLeft
	};
	Movement currentMove;

	Tile *tile;
	const int MAXHEALTH;

	static const int FRAMES_PER_MOVEMENT = 16;
	static const int PIXELS_PER_MOVEMENT = 16;
	static const int offset = 24;
	static const int offset_Y = 32;
	static const int randChance = 2;

	float SPEED;

	int frameCounter;
	int health;
	int pickMove;
	int willEat;

	sf::Vector2f Pos;

	AnimatedSprite MainSprite;
	CollisionTools::TextureBitmap bitmap;
};
#endif _Spider

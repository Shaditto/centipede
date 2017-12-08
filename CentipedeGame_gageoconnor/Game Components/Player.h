/* Player.h - Gage O'Connor, October 2017 */

#ifndef _Player
#define _Player

#include "TEAL\CommonElements.h"
#include "Grid.h"

//test
#include "CentipedeHead.h"

// Forward declarations
class Mushroom;
class Spider;
class Centipede;
class Flea;

class Player : public GameObject
{
public:
	/* BIG FOUR */
	Player();
	Player(const Player & player) = default;
	Player & operator = (const Player & player) = default;
	~Player() = default;

	/* INITIALIZER */
	void Initialize(Grid * pGrid);

	/* METHODS */
	virtual void Update();
	virtual void Draw();
	virtual void Destroy();
	virtual void fireBullet();

	virtual void KeyPressed(sf::Keyboard::Key k, bool altKey, bool ctrlKey, bool shiftKey, bool systemKey);
	virtual void setBulletActive();
	virtual void setPosition(sf::Vector2f val);
	virtual void setPositionAttractor(sf::Vector2f val);
	virtual void resetPosition(sf::Vector2f val);

	virtual void setScore(int val);
	virtual void setLives();
	virtual int getScore();
	virtual int getLives();
	virtual sf::Vector2f getPos();

	/* COLLISIONS */
	virtual void Collision(GameObject * other) {};
	virtual void Collision(Mushroom *other);
	virtual void Collision(Spider *other);
	virtual void Collision(CentipedeHead *other);
	virtual void Collision(CentipedeSegment *other);
	virtual void Collision(Flea *other);

private:
	const sf::Vector2f X_CLAMP;
	const sf::Vector2f Y_CLAMP;
	const float SPEED;
	const int MAX_LIVES;
	const int X_BOUNDARY;
	const int Y_BOUNDARY;
	const int START_X = 29;
	const int START_Y = 9;
	const int OFFSET = -10;

	Grid *pGrid;
	Tile *pTile;
	
	sf::Vector2f Pos;
	sf::Vector2f oldPos;
	sf::Vector2f bullet_Offset;
	AnimatedSprite MainSprite;
	AnimatedSprite deathSprite;
	CollisionTools::TextureBitmap bitmap;

	int score;
	int currLives;

	bool bullet_IsActive;
};
#endif _Player
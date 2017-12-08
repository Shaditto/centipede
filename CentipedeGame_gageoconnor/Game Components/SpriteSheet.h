/* SpriteSheet.h - Gage O'Connor, October 2017 */

#ifndef _SpriteSheet
#define _SpriteSheet

#include "SFML\Graphics.hpp"
#include "Glyph.h"
#include <vector>

class SpriteSheet
{
public:
	/* BIG FOUR */
	//SpriteSheet() = delete;
	//SpriteSheet(const SpriteSheet&) = delete;
	//SpriteSheet& operator =(const SpriteSheet&) = delete;
	virtual ~SpriteSheet() = default;

	SpriteSheet(sf::Texture& tex, int CellCountHor, int CellCountVert);

	/* METHODS */
	void Draw(int i, sf::Vector2f pos);

	int GetCellWidth();
	int GetCellHeight();
	sf::Sprite GetSprite();

	Glyph* GetGlyph(char c, sf::Vector2f pos);

private:
	std::vector<sf::IntRect> cells;
	sf::Sprite MainSprite;
	int cellWidth;
	int cellHeight;

	virtual int CharToIndex(char& c) = 0; // Abstract method
};

#endif _SpriteSheet
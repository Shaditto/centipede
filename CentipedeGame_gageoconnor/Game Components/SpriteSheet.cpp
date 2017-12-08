/* SpriteSheet.cpp - Gage O'Connor, October 2017 */

#include "SpriteSheet.h"
#include "GlyphFactory.h"
#include "TEAL\WindowManager.h"

SpriteSheet::SpriteSheet(sf::Texture& tex, int CellCountHor, int CellCountVert)
{
	MainSprite = sf::Sprite(tex);

	// Rectangle dimension corresponding to a single cell of a sprite sheet
	cellWidth = tex.getSize().x / CellCountHor;
	cellHeight = tex.getSize().y / CellCountVert;

	cells.resize(CellCountHor * CellCountVert);

	// Determine rectangle for each cell
	int left;
	int top;

	for (int j = 0; j < CellCountVert; j++)
	{
		top = j * cellHeight;
		for (int i = 0; i < CellCountHor; i++)
		{
			left = i * cellWidth;
			cells[j*CellCountHor + i] = sf::IntRect(left, top, cellWidth, cellHeight);
		}
	}
}

int SpriteSheet::GetCellWidth()
{
	return cellWidth;
}

int SpriteSheet::GetCellHeight()
{
	return cellHeight;
}

sf::Sprite SpriteSheet::GetSprite()
{
	return MainSprite;
}

Glyph* SpriteSheet::GetGlyph(char c, sf::Vector2f pos)
{
	return GlyphFactory::createGlyph(this, CharToIndex(c), pos);
}

void SpriteSheet::Draw(int i, sf::Vector2f pos)
{
	MainSprite.setTextureRect(cells[i]);		// These two operations are fast to perform
	MainSprite.setPosition(pos);

	WindowManager::MainWindow.draw(MainSprite);
}
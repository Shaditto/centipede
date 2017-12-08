/* FontWriter.cpp - Gage O'Connor, October 2017 */

#include "FontWriter.h"

FontWriter* FontWriter::pInstance = nullptr;

FontWriter::FontWriter()
{
	//RegisterInput(InputFlags::TextEntered);

}
void FontWriter::privateDisplayInfo()
{
	// Initial Display
	std::string p1ScoreD = "    00";
	std::string p1LivesD = "@@@";
	std::string p2LivesD = "       @@@";
	std::string p2ScoreD = "    00";
	std::string highScoreD = "    " + std::to_string(currHighScore);;
	nextpos = 0;

	// P1 Score Initial Display
	for (size_t i = 0; i < p1ScoreD.length(); i++)
	{
		p1Score.push_back(myfont.GetGlyph(p1ScoreD.at(i), sf::Vector2f(nextpos, 0)));
		nextpos += myfont.GetCellWidth();
	}

	// P1 Lives Initial Display
	for (size_t i = 0; i < p1LivesD.length(); i++)
	{
		p1Lives.push_back(myfont.GetGlyph(p1LivesD.at(i), sf::Vector2f(nextpos, 0)));
		nextpos += myfont.GetCellWidth();
	}

	// HighScore Initial Display
	for (size_t i = 0; i < highScoreD.length(); i++)
	{
		p1Lives.push_back(myfont.GetGlyph(highScoreD.at(i), sf::Vector2f(nextpos, 0)));
		nextpos += myfont.GetCellWidth();
	}

	// P2 Score Initial Display
	for (size_t i = 0; i < p2LivesD.length(); i++)
	{
		p2Lives.push_back(myfont.GetGlyph(p2LivesD.at(i), sf::Vector2f(nextpos, 0)));
		nextpos += myfont.GetCellWidth();
	}

	// P2 Lives Initial Display
	for (size_t i = 0; i < p2ScoreD.length(); i++)
	{
		p2Score.push_back(myfont.GetGlyph(p2ScoreD.at(i), sf::Vector2f(nextpos, 0)));
		nextpos += myfont.GetCellWidth();
	}
}

void FontWriter::privateDisplayHighScores(Tile* pTile)
{
	Tile* tmp1 = pTile->getDown();
	Tile* tmp2 = tmp1->getDown();
	Tile* tmp3 = tmp2->getDown();
	Tile* tmp4 = tmp3->getDown();
	Tile* tmp5 = tmp4->getDown();
	Tile* tmp6 = tmp5->getDown();
	Tile* tmp7 = tmp6->getDown();
	Tile* tmp8 = tmp7->getDown();
	Tile* space = tmp8->getDown();
	Tile* credits = space->getDown();
	Tile* bonus = credits->getDown()->getLeft()->getLeft()->getLeft();

	// Displays High Scores
	privateSetGlyphTiles(pTile, HIGHSCORELABEL);
	privateSetGlyphTiles(tmp1, " " + std::to_string(currHighScore) + " " + HS1);
	privateSetGlyphTiles(tmp2, HS2);
	privateSetGlyphTiles(tmp3, HS3);
	privateSetGlyphTiles(tmp4, HS4);
	privateSetGlyphTiles(tmp5, HS5);
	privateSetGlyphTiles(tmp6, HS6);
	privateSetGlyphTiles(tmp7, HS7);
	privateSetGlyphTiles(tmp8, HS8);
	privateSetGlyphTiles(space, SPACE);
	privateSetGlyphTiles(credits, CREDITS);
	privateSetGlyphTiles(bonus, BONUS);
}

void FontWriter::privateSetGlyphTiles(Tile* pTile, std::string glyphs)
{
	for (size_t i = 0; i < glyphs.length(); i++)
	{
		pTile->setTile(myfont.GetGlyph(glyphs.at(i), sf::Vector2f(pTile->getPos().x - glyphOffset, pTile->getPos().y - glyphOffset)));
		pTile = pTile->getRight();
	}
}

void FontWriter::privateComputeP1Score(std::string val, int val2)
{
	// Recycles Glyphs
	while (p1Score.size() != 0)
	{
		p1Score.front()->MarkForDestroy();
		p1Score.pop_front();
	}

	// Calculates the offset to Draw the Score based on CellWidth and number of digits
	nextpos = static_cast<float>(myfont.GetCellWidth() * (numCharP1Score - val.length()));

	// Writes the new score
	for (size_t i = 0; i < val.length(); i++)
	{
		p1Score.push_back(myfont.GetGlyph(val.at(i), sf::Vector2f(nextpos, 0)));
		nextpos += myfont.GetCellWidth();
	}

	// Updates HighScore if necessary
	if (val2 >= currHighScore)
		ComputeNewHighScore(val2);

}

void FontWriter::privateComputeNewHighScore(int val)
{
	// Recycles Glyphs
	while (highscore.size() != 0)
	{
		highscore.front()->MarkForDestroy();
		highscore.pop_front();
	}

	// Assigns new High Score
	currHighScore = val;

	// Calculates the offset to Draw the Score based on CellWidth and number of digits
	nextpos = static_cast<float>(myfont.GetCellWidth() * (numHighScore));

	// Writes the new score
	for (size_t i = 0; i < std::to_string(currHighScore).length(); i++)
	{
		p1Score.push_back(myfont.GetGlyph(std::to_string(currHighScore).at(i), sf::Vector2f(nextpos, 0)));
		nextpos += myfont.GetCellWidth();
	}
}

void FontWriter::privateComputeP1Lives(std::string val)
{
	// Recycles and Updates P1 Lives
	if (p1Lives.size() != 0)
	{
		p1Lives.front()->MarkForDestroy();
		p1Lives.pop_front();
	}
}

void FontWriter::privateComputeP2Score(std::string val)
{
	// Recycles Glyphs
	while (p2Score.size() != 0)
	{
		p2Score.front()->MarkForDestroy();
		p2Score.pop_front();
	}

	// Calculates the offset to Draw the Score based on CellWidth and number of digits
	nextpos = static_cast<float>(myfont.GetCellWidth() * (numCharP2Score - val.length()));

	for (size_t i = 0; i < val.length(); i++)
	{
		p2Score.push_back(myfont.GetGlyph(val.at(i), sf::Vector2f(nextpos, 0)));
		nextpos += myfont.GetCellWidth();
	}
}

void FontWriter::privateComputeP2Lives(std::string val)
{
	// Recycles and Updates P2 Lives
	if (p2Lives.size() != 0)
	{
		p2Lives.back()->MarkForDestroy();
		p2Lives.pop_back();
	}
}

void FontWriter::Draw()
{
	std::list<Glyph*>::iterator it_P1Score;
	for (it_P1Score = p1Score.begin(); it_P1Score != p1Score.end(); it_P1Score++)
		(*it_P1Score)->Draw();

	std::list<Glyph*>::iterator it_P2Score;
	for (it_P2Score = p2Score.begin(); it_P2Score != p2Score.end(); it_P2Score++)
		(*it_P2Score)->Draw();

	std::list<Glyph*>::iterator it_P1Lives;
	for (it_P1Lives = p1Lives.begin(); it_P1Lives != p1Lives.end(); it_P1Lives++)
		(*it_P1Lives)->Draw();

	std::list<Glyph*>::iterator it_P2Lives;
	for (it_P2Lives = p2Lives.begin(); it_P2Lives != p2Lives.end(); it_P2Lives++)
		(*it_P2Lives)->Draw();

}

void FontWriter::Terminate()
{
	pInstance = nullptr;
	delete pInstance;	
}

FontWriter::~FontWriter()
{
	ConsoleMsg::WriteLine("Deleting p1Score (" + Tools::ToString(p1Score.size()) + ")");
	ConsoleMsg::WriteLine("Deleting p1Lives (" + Tools::ToString(p1Lives.size()) + ")");
	ConsoleMsg::WriteLine("Deleting p2Score (" + Tools::ToString(p2Score.size()) + ")");
	ConsoleMsg::WriteLine("Deleting p2Lives (" + Tools::ToString(p2Lives.size()) + ")");

	// Clear out symbols
	p1Score.clear();
	p1Lives.clear();
	p2Score.clear();
	p2Lives.clear();
}

/*void FontWriter::TextEntered(sf::Uint32 UnicodeValue)
{
symbols.push_back(myfont.GetGlyph((char)UnicodeValue, nextpos));
nextpos.x += myfont.GetCellWidth();
}*/

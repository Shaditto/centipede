/* FontWriter.cpp - Gage O'Connor, October 2017 */

#ifndef _FontWriter
#define _FontWriter

#include "TEAL/CommonElements.h"
#include <list>
#include "CentiFont.h"
#include "Tile.h"

class FontWriter : public GameObject
{
public:
	static void ComputeP1Score(std::string val, int val2) {Instance().privateComputeP1Score(val, val2);};
	static void ComputeP1Lives(std::string val) { Instance().privateComputeP1Lives(val); }

	//static void ComputeP2Score(std::string val) { Instance().privateComputeP2Score(val); };
	//static void ComputeP2Lives(std::string val) { Instance().privateComputeP2Lives(val); }

	static void DisplayInfo() { Instance().privateDisplayInfo(); };
	static void DisplayHighScores(Tile* pTile) { Instance().privateDisplayHighScores(pTile); };

	static void ComputeNewHighScore(int val) { Instance().privateComputeNewHighScore(val); };
	virtual void Draw();

	static void Terminate();

private:
	static FontWriter *pInstance;	// Set up as Singleton

	FontWriter();
	FontWriter(const FontWriter &) = delete;					// Prevents copy-constructions
	FontWriter & operator = (const FontWriter &) = delete;	// Prevents assignment
	~FontWriter();												// Only this can delete

	static FontWriter & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new FontWriter;
		return *pInstance;
	};

	const std::string HIGHSCORELABEL = "HIGH SCORES";
	const std::string HS1 = " PLR";
	const std::string HS2 = " 11367 PPZ ";
	const std::string HS3 = " 10145 DOG ";
	const std::string HS4 = " 10139 WIT ";
	const std::string HS5 = " 10125 ART ";
	const std::string HS6 = " 10122 MON ";
	const std::string HS7 = " 10018 TPM ";
	const std::string HS8 = " 10000 CAT ";
	const std::string CREDITS = " CREDITS 2 ";
	const std::string SPACE = "           ";
	const std::string BONUS = "BONUS EVERY 12000";

	const int numCharP1Score = 6;
	const int numCharP1Lives = 8;
	const int numHighScore = 13;
	const int numCharP2Score = 30;
	const int numCharP2Lives = 24;
	const int glyphOffset = 8;

	int currHighScore = 1;

	CentiFont myfont;

	std::list<Glyph*> p1Score;
	std::list<Glyph*> p1Lives;
	std::list<Glyph*> p2Score;
	std::list<Glyph*> p2Lives;
	std::list<Glyph*> highscore;

	float nextpos;

	virtual void privateComputeP1Score(std::string val, int val2);
	virtual void privateComputeP1Lives(std::string val);

	virtual void privateComputeP2Score(std::string val);
	virtual void privateComputeP2Lives(std::string val);

	virtual void privateDisplayInfo();
	virtual void privateDisplayHighScores(Tile* pTile);

	virtual void privateComputeNewHighScore(int val);

	void privateSetGlyphTiles(Tile* pTile, std::string glyphs);
};

#endif _FontWriter
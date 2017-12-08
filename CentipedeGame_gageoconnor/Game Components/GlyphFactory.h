/* GlyphFactory.h - Gage O'Connor, October 2017 */

#ifndef _GlyphFactory
#define _GlyphFactory

#include <stack>
#include "Glyph.h"

/* Set up as a Singleton */
class GlyphFactory
{
public:
	// Static services
	static Glyph* createGlyph(SpriteSheet* sheet, int cellInd, sf::Vector2f pos) { return Instance().privateCreateGlyph(sheet, cellInd, pos); };
	static void recycleGlyph(GameObject *pGlyph) { Instance().privateRecycleGlyph(pGlyph); };

	static void Terminate();

private:
	static GlyphFactory *pInstance;	// Set up as Singleton

	GlyphFactory() = default;
	GlyphFactory(const GlyphFactory &) = delete;					// Prevents copy-constructions
	GlyphFactory & operator = (const GlyphFactory &) = delete;		// Prevents assignment
	~GlyphFactory();												// Only this can delete

	static GlyphFactory & Instance() // Access reference (since all public methods will be static)
	{
		if (!pInstance)
			pInstance = new GlyphFactory;
		return *pInstance;
	};

	std::stack<Glyph *> recycledGlyphs; // Non-static

	Glyph* privateCreateGlyph(SpriteSheet* sheet, int cellInd, sf::Vector2f pos);
	void privateRecycleGlyph(GameObject *pGlyph);
};

#endif _GlyphFactory



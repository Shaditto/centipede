/* GlyphFactory.cpp - Gage O'Connor, October 2017 */

#include "TEAL/CommonElements.h"
#include "GlyphFactory.h"
#include "Glyph.h"

GlyphFactory *GlyphFactory::pInstance = nullptr;

Glyph* GlyphFactory::privateCreateGlyph(SpriteSheet* sheet, int cellInd, sf::Vector2f pos)
{
	Glyph *pGlyph;

	if (recycledGlyphs.empty())
	{
		ConsoleMsg::WriteLine("New Glyph");

		pGlyph = new Glyph();

		// Object will return here instead of being destroyed
		pGlyph->SetExternalManagement(recycleGlyph);
	}
	else
	{
		ConsoleMsg::WriteLine("Recycled Glyph");

		pGlyph = recycledGlyphs.top();
		recycledGlyphs.pop();

		// Register back to scene
		pGlyph->RegisterToCurrentScene();
	}
	pGlyph->Initialize(sheet, cellInd, pos);
	return pGlyph;
}

void GlyphFactory::privateRecycleGlyph(GameObject *pGlyph)
{
	recycledGlyphs.push((Glyph*)pGlyph);
	ConsoleMsg::WriteLine("Recycled Glyph Size: " + Tools::ToString(recycledGlyphs.size()));
}

void GlyphFactory::Terminate()
{
	delete pInstance;
	pInstance = nullptr;
}

GlyphFactory::~GlyphFactory()
{
	ConsoleMsg::WriteLine("Deleting Recycled Glyphs (" + Tools::ToString(recycledGlyphs.size()) + ")");

	// Forcefully delete Recycled Glyphs
	while (!recycledGlyphs.empty())
	{
		delete recycledGlyphs.top();
		recycledGlyphs.pop();
	}
}
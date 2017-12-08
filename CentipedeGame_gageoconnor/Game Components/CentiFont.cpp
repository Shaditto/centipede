/* CentiFont.cpp - Gage O'Connor, October 2017 */

#include "CentiFont.h"
#include "TEAL\ResourceManager.h"

CentiFont::CentiFont()
	: SpriteSheet(ResourceManager::GetTexture("Alphabet"), 16, 3)
{
}

// Calculates the value of the cellIndex for each char
int CentiFont::CharToIndex(char& c)
{
	int cellIndex = 0;

	// Converts lowercase to uppercase
	if (c >= 'a' && 'z')
		c -= 32;

	// Selects symbol to use
	if ( c >= '0' && c <= '9')
		cellIndex = (int) c - (int) '0';	
	else if ( c >= 'A' && c <= 'Z')
		cellIndex = (int) c - (int) 'A' + 17;
	else
		switch (c)
		{
		case ' ':	// Space
			cellIndex = 16;
			break;
		case ':':	// Colon
			cellIndex = 10;
			break;
		case '/':	// Half
			cellIndex = 11;
			break;
		case '[':	// Copyright
			cellIndex = 12;
			break;
		case ']':	// Publisher
			cellIndex = 14;
			break;
		case '@':	// Life
			cellIndex = 43;
			break;
		default:
			cellIndex = 16;
		}
	
	return cellIndex;
}
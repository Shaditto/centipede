/* CentiFont.h - Gage O'Connor, October 2017 */

#ifndef _CentiFont
#define _CentiFont

#include "SpriteSheet.h"

class CentiFont : public SpriteSheet
{
public:
	CentiFont();
	CentiFont(const CentiFont&) = delete;
	CentiFont& operator =(const CentiFont&) = delete;
	virtual ~CentiFont() = default;

private:
	virtual int CharToIndex(char& c);
};

#endif _CentiFont
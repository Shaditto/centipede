/* CommandBase.h - Gage O'Connor, October 2017 */

#ifndef _CommandBase
#define _CommandBase

#include "TEAL/CommonElements.h"

class CommandBase
{
public:
	virtual void Execute() = 0;
};

#endif _CommandBase
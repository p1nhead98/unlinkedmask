#include "Banks/SetAutoBank.h"
#include "Math.h"

UINT8 current_level = 0;

void PerDelay(UINT8 numloops) BANKED
{
	
	for (UINT8 i = 0; i < numloops; i++)
	{
		wait_vbl_done();
	}
}


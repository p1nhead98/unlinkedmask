#include "Banks/SetAutoBank.h"
#include "Math.h"


void PerDelay(UINT8 numloops) BANKED
{
	
	for (UINT8 i = 0; i < numloops; i++)
	{
		wait_vbl_done();
	}
}


#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Music.h"
#include "Scroll.h"
#include <gb/gb.h>


IMPORT_MAP(map);
DECLARE_MUSIC(song1);

UINT8 collision_tiles[] = {4, 5, 6, 7, 0};


UBYTE counter;
UINT16 p1, p2;





void START()
{
	
	
	// LY_REG  = 0;
	// disable_interrupts();
	// add_LCD(LCD_Interrupt);
	// add_VBL(VBL_Interrupt);
	// enable_interrupts();

	OBP0_REG = PAL_DEF(3, 0, 1, 2);
	scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	InitScroll(BANK(map), &map, collision_tiles, 0);

	//set_interrupts(LCD_IFLAG | VBL_IFLAG );
	PlayMusic(song1, LOOP);


	
}

void UPDATE()
{
	// vsync();
	// scanline_offsets = scanline_offsets_tbl + ((sys_time >> 2) & 0x07u);
}

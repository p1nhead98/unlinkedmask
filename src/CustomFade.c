#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "Math.h"
#include "Palette.h"
#include <gb/gb.h>
#include <gb/cgb.h>
#include "Misc2.h"
#include "Misc.h"
#include "Music.h"

extern UWORD ZGB_Fading_BPal[32];
extern UWORD ZGB_Fading_SPal[32];


void DMGFadeCustom(UINT8 fadeout) BANKED {
	
	UINT8 pals3[] = {3, 2, 1, 0, 0, 0};
    UINT8 pals2[] = {2, 1, 0, 0, 0, 0};
    UINT8 pals1[] = {1, 0, 0, 0, 0, 0};
	UINT8 pals0[] = {0, 0, 0, 0, 0, 0};


    BGP_REG = OBP0_REG = OBP1_REG = PAL_DEF(pals0[fadeout], pals1[fadeout], pals2[fadeout], pals3[fadeout] );
		
}

UWORD UpdateColorCustom(UINT8 i, UWORD col) {
	//return RGB2(DespRight(PAL_RED(col), i), DespRight(PAL_GREEN(col), i), DespRight(PAL_BLUE(col), i));
	return RGB2(PAL_RED(col) | DespRight(0x1F, 5 - i), PAL_GREEN(col) | DespRight(0x1F, 5 - i), PAL_BLUE(col) | DespRight(0x1F, 5 - i));
}


void FadeStepColorCustom(UINT8 i) BANKED{
	UINT8 pal, c;
	UWORD palette[4];
	UWORD palette_s[4];
	UWORD* col = ZGB_Fading_BPal;
	UWORD* col_s = ZGB_Fading_SPal;

	for(pal = 0; pal < 8; pal ++) {
		for(c = 0; c < 4; ++c, ++col, ++col_s) {
				palette[c] = UpdateColorCustom(i, *col);
				palette_s[c] = UpdateColorCustom(i, *col_s);
		};
		set_bkg_palette(pal, 1, palette);
		set_sprite_palette(pal, 1, palette_s);
	}
	delay(20);
}

void FadeColorAndMusic() BANKED{
    DMGFadeCustom(0);
    FadeStepColorCustom(0);
    pDelay(10);
    NR50_REG = 0x55;
    DMGFadeCustom(1);
    FadeStepColorCustom(1);
    pDelay(10);
    NR50_REG = 0x33;
    DMGFadeCustom(2);
    FadeStepColorCustom(2);
    pDelay(10);
    NR50_REG = 0x11;
    DMGFadeCustom(3);
    FadeStepColorCustom(3);
    pDelay(10);
    NR50_REG = 0x0;
    StopMusic;
    DMGFadeCustom(4);
    FadeStepColorCustom(4);
    pDelay(10);
    DMGFadeCustom(5);
    FadeStepColorCustom(5);
    pDelay(10);
}

    
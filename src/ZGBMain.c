#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = StateGame;

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if(current_state == StateGame) {
		

		switch(*tile_ptr){
			case 227:
				*tile = 82;
				return SpriteJumpBoxEvent;
			default:
				if(U_LESS_THAN(255 - (UINT16)*tile_ptr, N_SPRITE_TYPES)) {
					*tile = 3;
					return 255 - (UINT16)*tile_ptr;
				}
		}
		
	}

	return 255u;
}
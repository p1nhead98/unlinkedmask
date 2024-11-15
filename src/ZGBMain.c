#include "ZGBMain.h"
#include "Math.h"
UINT8 next_state = StateTitleScreen;
UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {

		switch(*tile_ptr){
			case 254:
				*tile = 3;
				return SpriteJumpBox;
			case 253:
				*tile = 3;
				return SpriteOrbForest;
			case 252:
				*tile = 3;
				return SpriteDoorButton;
			case 251:
				*tile = 3;
				return SpriteOnOffBtn;
			case 250:
				*tile = 3;
				return SpriteOrbTemple;
			case 249:
				*tile = 3;
				return SpriteOrbRooftop;
			case 248:
				*tile = 3;
				return SpriteCrusherDown;
			case 247:
				*tile = 3;
				return SpriteSplitBox;
			case 246:
				*tile = 3;
				return SpriteCrusherLeft;

	}
	return 255u;
}
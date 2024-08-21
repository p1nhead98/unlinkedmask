#include "ZGBMain.h"
#include "Math.h"

UINT8 next_state = StateStage3;

UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {


	if(current_state == StateStage1 || current_state == StateStage2 || current_state == StateStage3){
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
		}
	}
	return 255u;
}
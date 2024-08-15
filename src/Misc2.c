#include "Banks/SetAutoBank.h"
#include "Math.h"
#include "Scroll.h"
#include "TileAnimation.h"
UINT8 current_level = 0;

IMPORT_TILES(darkTileAnim);
IMPORT_TILES(doorAnim);

IMPORT_TILES(OnAnim);
IMPORT_TILES(OffAnim);

void PerDelay(UINT8 numloops) BANKED
{
	
	for (UINT8 i = 0; i < numloops; i++)
	{
		wait_vbl_done();
	}
}

void ScreenShake(UINT8 duration, INT8 seismicscale) BANKED
{

	UINT8 d;

	for (d = 0; d < duration; d++)
	{

		scroll_offset_y = seismicscale;

		///scroll_offset_y=seismicscale;
		PerDelay(1);
		scroll_offset_y = -seismicscale;

		//scroll_offset_y=-seismicscale;
		PerDelay(1);
	}

	scroll_offset_x = 0;
	scroll_offset_y = 0;
}

void SetDoorCols(UINT8 off) BANKED{
    if(off == 1){
        Set_Bkg_Data(&darkTileAnim, 64, 12, BANK(darkTileAnim));
    }else{
        Set_Bkg_Data(&doorAnim, 64, 12, BANK(doorAnim));
        ScreenShake(1,1);
        
    }
     
}



void SetOnOffCols(UINT8 cols[], UINT8 onOff ) BANKED{

    UINT8 i = 0;

    if(onOff == 0){
		for(i = 0u; cols[i] != 0u; ++i) {
            if(i > 15u && i < 20u){
				scroll_collisions[cols[i]] = 1u;
				scroll_collisions_down[cols[i]] = 1u;
			}else if(i > 19u && i < 25u){
				scroll_collisions[cols[i]] = 0u;
				scroll_collisions_down[cols[i]] = 0u;
			}
            
		}
        Set_Bkg_Data(&OffAnim, 60, 4, BANK(OffAnim));
		Set_Bkg_Data(&OnAnim, 56, 4, BANK(OnAnim));
   
        
        // Onoff_tile_anim(&spikesAnim, 0, BANK(spikesAnim), 81);
        // Onoff_tile_anim(&spikesAnim3, 0, BANK(spikesAnim3), 85);
        
    }else if(onOff == 1){
        for(i = 0u; cols[i] != 0u; ++i) {
            if(i > 15u && i < 20u){
				scroll_collisions[cols[i]] = 0u;
				scroll_collisions_down[cols[i]] = 0u;
			}else if(i > 19u && i < 25u){
				scroll_collisions[cols[i]] = 1u;
				scroll_collisions_down[cols[i]] = 1u;
			}
		}
        Set_Bkg_Data(&OnAnim, 60, 4, BANK(OnAnim));
		Set_Bkg_Data(&OffAnim, 56, 4, BANK(OffAnim));
   
        // Onoff_tile_anim(&spikesAnim3, 0, BANK(spikesAnim3), 81);
        // Onoff_tile_anim(&spikesAnim, 0, BANK(spikesAnim), 85);
    }

}
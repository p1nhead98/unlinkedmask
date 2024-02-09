#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"


extern UINT8 current_level;

void CheckCollisionTilePlt4(CUSTOM_DATA_ORB* data)
{
    
    UINT8 colision = GetScrollTile((THIS->x + 16u) >> 3, (THIS->y + 6u) >> 3);
    UINT8 colision2 = GetScrollTile((THIS->x + 4u) >> 3, (THIS->y - 4u) >> 3);
    if(data->state == 2){
     
        colision = data->initial_speed == 4 ? GetScrollTile((THIS->x + 12) >> 3, (THIS->y + 3u) >> 3) : GetScrollTile((THIS->x + 12) >> 3, (THIS->y + 4u) >> 3);
    }else if (data->state == 3){
        colision = data->initial_speed == 4 ? GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 2u) >> 3) : GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 3u) >> 3);
    }else if(data->state == 4){
        colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 4u) >> 3);
    }else if(data->state == 5){
        colision = data->initial_speed == 4 ? GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 13u) >> 3) : GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 12u) >> 3);
    }
  
    if(colision == 92 && data->state != 7 ){
        data->state = 7;
    }if(colision == 93 && data->state != 2 ){
        data->state = 2;
        
    }else if( colision == 94 && data->state != 5){
        data->initial_state = 5;
        data->state = 6;
      
    }else if( colision == 95 && data->state != 4){
        data->initial_state = 4;
        data->state = 6;
      
    }else if( colision == 96 && data->state != 3 ){
        if(data->initial_state != 0){
            data->initial_state = 3;
            data->state = 6;
        }else{
            data->state = 3;
        }
        data->state = 3;
     
    }

    // if(colision2 == 93 && (data->state == 2 || data->state == 9)){
    //     data->initial_state = 8;
    //     data->state = 6;
    //     data->initial_speed = 3;
    // }else if(colision2 == 101 && (data->state == 2 || data->state == 8)){
    //     data->initial_state = 9;
    //     data->state = 6;
    //     data->initial_speed = 2;
    //     data->speed = 1;
    // }
        
    
   

}

void START()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;
    data->initial_state = data->state = 0;
    data->speed = data->initial_speed = 2;
    THIS->y -= 4;
    THIS->x -= 3;
    THIS->lim_x = 100;
    THIS->lim_y = 100;
    THIS->x += 7;
    
}

void UPDATE()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;

    if(data->state != 0){
        CheckCollisionTilePlt4(data);
    }

    switch (data->state)
    {
    case 1:
 
        UINT8 colision = GetScrollTile((THIS->x + 7u) >> 3, (THIS->y ) >> 3);
        if(colision == 94){
            data->state = 5;
            data->initial_speed = 4;
        }
        break;
    case 2:
        THIS->x += data->initial_speed;
        break;
    case 3:
        THIS->y -= data->initial_speed;
        break;
    case 4:
        THIS->x -= data->initial_speed;
        break;
    case 5:
        THIS->y += data->initial_speed;
        break;


    default:
        break;
    }
}

void DESTROY()
{
}
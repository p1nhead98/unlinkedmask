#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

void CheckCollisionTilePlt2(CUSTOM_DATA_ORB* data)
{
    UINT8 colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 4u) >> 3);
    // UINT8 colision2 = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 16u) >> 3);
    if (data->state == 2){
        colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 4u) >> 3);
    }else if(data->state == 3){
        colision = GetScrollTile((THIS->x + 10u) >> 3, (THIS->y + 10u) >> 3);
    }else if(data->state == 4){
        colision = GetScrollTile((THIS->x + 10u) >> 3, (THIS->y + 4u) >> 3);
    }


    if( colision == 107 && data->state != 2 ){
        data->state = 2;
    }else if( colision == 106 && data->state != 3 ){
        data->state = 3;
    }else if( colision == 105 && data->state != 4 ){
        data->state = 4;
    }else if( colision == 104 && data->state != 5 ){
        data->state = 5;
    }

    if(colision == 98 && data->state != 2 ){
        data->state = 2;
        data->initial_speed = 10;
    }else if( colision == 99 && data->state != 5){
        data->state = 5;
        data->initial_speed = 10;
    }else if( colision == 100 && data->state != 4){
        data->state = 4;
        data->initial_speed = 10;
    }else if( colision == 101 && data->state != 3){
        data->state = 3;
        data->initial_speed = 10;
    }

   

}

void START()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;
    data->state = 0;
    data->initial_speed = 20;
    data->speed = data->initial_speed;
    THIS->y -= 4;
    THIS->x -= 3;
    THIS->lim_x = 80;
    THIS->lim_y = 80;
}

void UPDATE()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;

    if(data->state != 0){
        CheckCollisionTilePlt2(data);
    }

    switch (data->state)
    {
    case 1:

        break;
    case 2:
        if(--data->speed == 0){
            THIS->x++;
            data->speed = data->initial_speed;
        }
            
        break;
    case 3:
        THIS->y--;
        if(--data->speed == 0){
            THIS->y--;
            data->speed = data->initial_speed;
        }
        break;
    case 4:
        if(--data->speed == 0){
            THIS->x--;
            data->speed = data->initial_speed;
        }
    
        break;
    case 5:
        if(--data->speed == 0){
            THIS->y++;
            data->speed = data->initial_speed;
        }
      
        break;
    default:
        break;
    }
}

void DESTROY()
{
}
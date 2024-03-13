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

extern UINT8 start_screen;
extern UINT8 event;

void CheckColissionEvent(CUSTOM_DATA_ORB* data)
{
    UINT8 colision = GetScrollTile((THIS->x ) >> 3, (THIS->y + 6u) >> 3);
    // UINT8 colision2 = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 16u) >> 3);
    if(data->state == 1){
        colision = GetScrollTile((THIS->x + 12) >> 3, (THIS->y + 4u) >> 3);
    }else if (data->state == 2){
        colision = GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 3u) >> 3);
    }else if(data->state == 3){
        colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 4u) >> 3);
    }else if(data->state == 4){
        colision = GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 12u) >> 3);
    }


    if( colision == 101 && data->state != 1 ){
        data->state = 1;
    }else if( colision == 102 && data->state != 4 ){
        data->state = 4;
    }else if( colision == 103 && data->state != 3 ){
        data->state = 3;
    }else if( colision == 104 && data->state != 2 ){
        data->state = 2;
    }
    if(current_level > 11){
        if(colision == 97 && data->state != 1 ){
            data->state = 1;
            data->initial_speed = 1;
        }else if( colision == 98 && data->state != 4){
            data->state = 4;
            data->initial_speed = 1;
        }else if( colision == 99 && data->state != 3){
            data->state = 3;
            data->initial_speed = 1;
        }else if( colision == 100 && data->state != 2){
            data->state = 2;
            data->initial_speed = 1;
        }
    }
    
}

void START()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;

    data->initial_frame_speed = 0;
    data->initial_y = THIS->y;
    data->start = 1;

    data->state = 0;
    THIS->y -= 4;
    THIS->x -= 3;
    THIS->lim_x = 80;
}

void UPDATE()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;

     if(start_screen == 0){

        if(data->start == 0){
            data->start = 1;
            THIS->y = data->initial_y;
            THIS->anim_speed = data->initial_frame_speed;
        }

        switch (data->state)
        {
            case 0:
                THIS->y--;
                if(THIS->y == 24){
                    data->state++;
                    THIS->x = 1180;
                }
            break;
            case 1:
               THIS->y++;
               UINT8 colision = GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 12u) >> 3);
               if(colision == 107){
                data->state++;
                event = 1;
               }
            break;
    
        }
        // CheckColissionEvent(data);
     }else{
        if(THIS->y != 0  && data->start == 1){
            data->start = 0;
            data->initial_y = THIS->y;
            THIS->y = 0;
            data->initial_frame_speed = THIS->anim_speed;
            THIS->anim_speed = 0;
        } 
     }
}

void DESTROY()
{
}
#include "Banks/SetAutoBank.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"


extern UINT8 current_level;
extern UINT8 start_screen;

void CheckCollisionTilePlt2(CUSTOM_DATA_ORB* data)
{
    UINT8 colision = GetScrollTile((THIS->x + 16u) >> 3, (THIS->y + 6u) >> 3);
    if(data->state == 2){
        colision = data->initial_speed == 4 ? GetScrollTile((THIS->x + 14) >> 3, (THIS->y + 4u) >> 3) : GetScrollTile((THIS->x + 12) >> 3, (THIS->y + 4u) >> 3);
    }else if (data->state == 3){
         colision = data->initial_speed == 4 ? GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 2u) >> 3) : GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 3u) >> 3);
    }else if(data->state == 4){
        colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 4u) >> 3);
    }else if(data->state == 5){
        colision = GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 12u) >> 3);
    }


    if( colision == 101 && data->state != 2 ){
        data->state = 2;
    }else if( colision == 102 && data->state != 5 ){
        data->state = 5;
    }else if( colision == 103 && data->state != 4 ){
        data->state = 4;
    }else if( colision == 104 && data->state != 3 ){
        data->state = 3;
    }
    if(colision == 116){
        SpriteManagerRemove(THIS_IDX);
    }
   
    // UINT8 colision2 = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 16u) >> 3);
  





    if(current_level > 11){
        if(colision == 92){
            data->state = 6;
        }else if(colision == 97 && data->state != 2 ){
            data->state = 2;
            data->initial_speed = 1;
        }else if( colision == 98 && data->state != 5){
            data->state = 5;
            data->initial_speed = 1;
        }else if( colision == 99 && data->state != 4){
            data->state = 4;
            data->initial_speed = 1;
        }else if( colision == 100 && data->state != 3){
            data->state = 3;
            data->initial_speed = 1;
        }if(colision == 93 && data->state != 2 ){
            data->state = 2;
            data->initial_speed = 4;
        }else if( colision == 94 && data->state != 5){
            data->state = 5;
            data->initial_speed = 4;
        }else if( colision == 95 && data->state != 4){
            data->state = 4;
            data->initial_speed = 4;
        }else if( colision == 96 && data->state != 3){
            if(data->initial_speed == 4){
                THIS->x-=1;
            }else{
                data->initial_speed = 4;    
            }
            data->state = 3;
            
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
    data->initial_state = 0;
    if(current_level == 18 || current_level == 23){
        data->initial_speed = 1;
    }else{
        data->initial_speed = 2;
    }
    data->speed = data->initial_speed;
    THIS->y -= 4;
    THIS->x -= 3;
    THIS->lim_x = 100;
    THIS->lim_y = 160;
    UINT8 col = GetScrollTile((THIS->x + 16u) >> 3, (THIS->y + 6u) >> 3);
    if (col == 106){
        THIS->x += 7;
    }
}

void UPDATE()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;

     if(start_screen == 0){

        if(data->start == 0){
            data->start = 1;
            THIS->y = data->initial_y;
            THIS->anim_speed = data->initial_frame_speed;
        }

        if(data->state != 0){
            CheckCollisionTilePlt2(data);
        }

        switch (data->state)
        {
        case 1:
            UINT8 colision = GetScrollTile((THIS->x ) >> 3, (THIS->y + 6u) >> 3);
            UINT8 colision2 = GetScrollTile((THIS->x + 7u) >> 3, (THIS->y + 6u) >> 3);
            if(colision == 97){
                data->state = 2;
                data->initial_speed = 1;
            }else if (colision == 93){
                data->state = 2;
                data->initial_speed = 4;
            }else if (colision == 101){
                data->state = 2;
            }else if(colision == 105){
                if(current_level == 23){
                    data->state = 4;
                    data->initial_speed = 1;
                }
            }else if(colision2 == 106){
            
                data->state = 5;
                data->initial_speed = 4;
                
            }
            break;
        case 2:
            if(--data->speed == 0 && data->initial_speed == 1){
                THIS->x++;
                data->speed = data->initial_speed;
            }else{
                THIS->x += data->initial_speed;
            }
                
            break;
        case 3:
        
            if(--data->speed == 0 && data->initial_speed == 1){
                THIS->y--;
                data->speed = data->initial_speed;
            }else{
                THIS->y -= data->initial_speed;
            }
            break;
        case 4:
            if(--data->speed == 0 && data->initial_speed == 1){
                THIS->x--;
                data->speed = data->initial_speed;
            }else{
                THIS->x -= data->initial_speed;
            }
        
            break;
        case 5:
            if(--data->speed == 0 && data->initial_speed == 1){
                THIS->y++;
                data->speed = data->initial_speed;
            }else{
                THIS->y += data->initial_speed;
            }
        
            break;

        }
    }else{
        if(THIS->y != 0  && data->start == 1){
            data->start = 0;
            data->initial_y = THIS->y;
            THIS->y = 0;
            data->initial_frame_speed = THIS->anim_speed;
            THIS->anim_speed =0;
        } 
    }
}

void DESTROY()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;

}
#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

extern INT8 door_time;
extern INT8 door_open;

void START()
{
    // CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    // data->initial_y = THIS->y;
    // THIS->lim_x = 80;
    // THIS->lim_y = 80;
    // data->state = 0;
    // data->counter = 0;
    // if(data->state == 0){
    //     data->state = 1;
    //     SpriteManagerAdd(SpriteDoorTile2, THIS->x, THIS->y + 16);
    // }
}

void UPDATE()
{
    // Sprite* tile4 = 0;
    // CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    // if(door_open == 1 && THIS-> y > 0){
    //     if(THIS->y == data->initial_y){
    //         tile4 = SpriteManagerAdd(SpriteDoorTile4, THIS->x, THIS->y);
    //         THIS->y = -16;
    //     }
    // }else if(door_open == 0 && THIS->y != data->initial_y){
    //         if(data->counter != 10){
    //             data->counter++;
    //             if(data->counter == 10){
    //                 data->counter = 0;
    //                 THIS->y = data->initial_y;
    //                 tile4 = 0;
    //             }
    //         }

 
    // }
     
}

void DESTROY()
{
}
#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

extern UINT8 door_time;
extern UINT8 door_open;
extern UINT8 door_button;

void START()
{
    // CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    // data->initial_y = THIS->y;
    // THIS->lim_x = 80;
    // THIS->lim_y = 80;
    // data->counter = 0;
}

void UPDATE()
{
    // CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    // if(door_open == 1 && THIS-> y > 0){
    //     if(THIS->y == data->initial_y){
    //         THIS->y = -16;
    //     }
    // }else if(door_open == 0 && THIS->y != data->initial_y){

    //     if(data->counter != 10)
    //     {
    //         if(data->counter == 0){
    //             THIS->y = data->initial_y - 32;
    //         }
    //         data->counter++;
    //         if(data->counter == 5){
    //             THIS->y = data->initial_y - 16;
    //         }
    //         if(data->counter == 10){
    //             THIS->y = data->initial_y;
    //             data->counter = 0;
                
    //             SpriteManagerAdd(SpriteTimeDoorClosed, THIS->x - 8, THIS->y - 16);
    //         }
     
            
    //     }
    // } 
}

void DESTROY()
{
}
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


void START()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;

    data->initial_frame_speed = 0;
    data->initial_y = THIS->y;
    data->start = 1;

    data->state = 0;
    data->initial_speed = 2;
    data->speed = data->initial_speed;
    if(current_level == 0 ){
        data->state = 10;
        THIS->y -= 4;
        THIS->x -= 4;
    }
    if(current_level == 1){
        if(THIS->x < 680){
            data->state = 10;
            THIS->y -= 4;
            THIS->x -= 4;
        }else if(THIS->x > 1088 ){
            THIS->x += 4;
            data->state = 3;
        }
    }
    if(current_level == 2){
        if(THIS->x < 968){
            data->state = 10;
            THIS->y -= 4;
            THIS->x -= 4;
        }else if (THIS->x > 1256){
            THIS->y -= 4;
            data->state = 0;
        }
    }
    if(current_level == 3){
        if(THIS->x < 672){
            data->state = 10;
            THIS->y -= 4;
            // THIS->x -= 4;
        }else if (THIS->x > 1256){
            // THIS->y -= 4;
            // data->state = 0;
        }
    }
    if(current_level == 4){
        if(THIS->x < 496){
            data->state = 13;
            THIS->x += 4;
        }else if(THIS->x > 496 && THIS->x < 792){
            data->state = 10;
            THIS->y -= 4;
            THIS->x -= 4;
        }else if(THIS->x > 792 && THIS->x < 944){
            data->state = 24;
            THIS->y -= 4;
            THIS->x -= 4;
        }else if(THIS->x > 936 && THIS->x < 1304 && THIS->y > 104){
            data->state = 13;
            THIS->x += 4;
            THIS->lim_x = 200;
            THIS->lim_y = 160;
        }else if(THIS->x > 1350 && THIS->x < 1624 && THIS->y > 128){
            data->state = 24;
            THIS->y -= 4;
            THIS->x -= 4;
            THIS->lim_x = 200;
            THIS->lim_y = 160;
        }else if(THIS->x > 1350 && THIS->x < 1624 && THIS->y < 128){
            data->state = 31;
            THIS->y -= 4;
            THIS->x += 4;
        }else if(THIS->x > 1624){
            data->state = 30;
            THIS->x += 4;
            THIS->y -= 4;
        }

    }
    // if(current_level == 3){
    //     if(THIS->x < 200){
    //         THIS->y -= 4;
    //     }else if(THIS->x > 520 && THIS->x < 592){
    //         THIS->y -= 4;
    //         THIS->x += 16;
    //     }else if(THIS->x > 593 && THIS->x < 640){
    //         data->state = 3;
    //         THIS->x += 4;
    //     }else if(THIS->x > 832 && THIS->x < 880){
    //         data->state = 3;
    //         THIS->x -= 12;
    //     }else if(THIS->x > 881){
    //         data->state = 3;
    //         THIS->x += 4;
    //     }
    // }else{
    //     data->state = 10;
    //     THIS->x = 76;
    //     THIS->y = 148;
    //     THIS->lim_x = 100;
    //     THIS->lim_y = 160;

    // }
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

     switch(data->state){
        case 0:
            if(--data->speed == 0){
                data->speed = 2;
                THIS->x++;
            }
        break;
        case 1:
            if(--data->speed == 0){
                data->speed = 2;
                THIS->x--;
            }
        break;
        case 2:
           if(--data->speed == 0){
                data->speed = 2;
                THIS->y++;
            }
        break;
        case 3:
            if(--data->speed == 0){
                data->speed = 2;
                THIS->y--;
            }
        break;
        

        case 4:
            THIS->y++;
        break;

        case 5:
            THIS->y--;
        break;
        
        case 6:
            THIS->x++;
        break;
        
        case 7:
            THIS->x--;
        break;


        case 8:
            THIS->y -= 3;
        break;
        case 9:
            THIS->y += 3;
        break;
        case 11:
            THIS->x += 3;
        break;
        case 12:
            THIS->x -= 3;
        break;


        case 14:
            THIS->x -= 2;
        break;
        case 15:
            THIS->x += 2;
        break;
        case 16:
            THIS->y -= 2;
        break;
        case 17:
            THIS->y += 2;
            
            break;
        
        case 26:
            THIS->y -= 5;
            break;
        case 27:
            THIS->y += 5;
            break;
        case 28:
            THIS->x += 5;
            break;
        case 29:
            THIS->x -= 5;
            break;

     }

    if(current_level == 0){
        if(data->state == 6 && THIS->x > 915 && THIS->x < 952 && THIS->y < 162){
            data->state = 4;
        }else if(data->state == 4 && THIS->y > 163 && THIS->x < 971){
            data->state = 6;
        }else if(data->state == 6 && THIS->x > 971 && THIS->x < 987 && THIS->y > 163 ){
            data->state = 5;
        }else if(data->state == 5 && THIS->y < 93){
            data->state = 6;
        }else if(data->state == 6 && THIS->x > 1059 && THIS->y < 112){
            data->state = 4;
        }else if(data->state == 4 && THIS->y > 155 && THIS->x > 1059 && THIS->x < 1088){
            data->state = 6;
        }else if(data->state == 6 && THIS->x > 1115 && THIS-> y > 155){
            data->state = 4;
        }
    }else if(current_level == 1){
        if(THIS->x < 1064){
            if(data->state == 6 && THIS->x > 859 && THIS->y > 117){
                data->state = 5;
            }else if(data->state == 5 && THIS->y < 117){
                data->state = 6;
            }else if(data->state == 6 && THIS->x > 1003 && THIS->y < 117){
                data->state = 4;
            }
        }else if(THIS->x > 1088 && THIS->x < 1144){
            if(data->state == 3 && THIS->y < 83){
                data->state = 2;
            }else if(data->state == 2 && THIS->y > 139){
                data->state = 3;
            }
        }else if(THIS->x > 1152 && THIS->x < 1223){
            if(data->state == 3 && THIS->y < 123){
                data->state = 2;
            }else if(data->state == 2 && THIS->y > 160){
                data->state = 3;
            }
        }else if(THIS->x > 1224){
            if(data->state == 3 && THIS->y < 99){
                data->state = 2;
            }else if(data->state == 2 && THIS->y > 163){
                data->state = 3;
            }
        }
    }else if(current_level == 2){
        if(THIS->x < 736){
            if(data->state == 6 && THIS->x > 299 && THIS->x < 320 && THIS->y > 110){
                data->state = 5;
            }else if(data->state == 5 && THIS->y < 110 ){
                data->state = 6;
            }else if(data->state == 6 && THIS->x > 387 && THIS->y < 110){
                data->state = 4;
            }else if(data->state == 4 && THIS->y > 131 && THIS->x < 570){
                data->state = 6;
            }else if(data->state == 6 && THIS->x > 571 && THIS->y > 131){
                data->state = 4;
            }
        }if(THIS->x > 792 && THIS->x < 976){
            if(data->state == 6 && THIS->x > 915){
                data->state = 4;
            }
        }else{
            if(data->state == 0 && THIS->x > 1411){
                data->state = 1;
            }else if(data->state == 1 && THIS->x < 1363){
                data->state = 0;
            }
        }
    }else if(current_level == 3){
        if(data->state == 7 && THIS->x < 155 ){
            data->state = 6;
        }else if(data->state == 6 && THIS->x > 443 && THIS->y > 144 && THIS->x < 464){
            data->state = 5;
        }else if (data->state == 5 && THIS->y < 133 && THIS->x > 443){
            data->state = 7;
        }else if(data->state == 7 && THIS->x > 336 && THIS->x < 389 ){
            data->state = 5;
        }else if(data->state == 5 && THIS->y < 101 && THIS->x < 389){
            data->state = 6;
        }else if(data->state == 6 && THIS->x > 499 && THIS->y < 101){
            data->state = 4;
        }else if(data->state == 4 && THIS->y > 163  && THIS->x < 552){
            data->state = 6;
        }else if(data->state == 6 && THIS->y > 163 && THIS->x > 611){
            data->state = 4;
        }
    }else if(current_level == 4){
        if(THIS->x < 496){
            if(THIS->x < 336){
                if(data->state == 9 && THIS->y > 161){
                    data->state = 11;
                }else if(data->state == 11 && THIS->x > 307){
                    data->state = 8;
                }else if(data->state == 8 && THIS->y < 118){
                    data->state = 7;
                }else if(data->state == 7 && THIS->x < 269){
                    data->state = 9;
                }
            }else if(THIS->x > 336 && THIS->x < 410){
                if(data->state == 9 && THIS->y > 161){
                    data->state = 11;
                }else if(data->state == 11 && THIS->x > 387){
                    data->state = 8;
                }else if(data->state == 8 && THIS->y < 118){
                    data->state = 7;
                }else if(data->state == 7 && THIS->x < 349){
                    data->state = 9;
                }
            }else{
                if(data->state == 9 && THIS->y > 161){
                    data->state = 11;
                }else if(data->state == 11 && THIS->x > 467){
                    data->state = 8;
                }else if(data->state == 8 && THIS->y < 118){
                    data->state = 7;
                }else if(data->state == 7 && THIS->x < 429){
                    data->state = 9;
                }
            }

        }else if(THIS->x > 496 && THIS->x < 784){
            if(data->state == 6 && THIS->x > 571 && THIS->y > 155){
                data->state = 20;
            }else if(data->state == 8 && THIS->y < 128){
                THIS->y-=1;
                data->state = 21;
            }else if(data->state == 6 && THIS->x > 619 && THIS->y < 128){
                data->state = 22;
            }else if(data->state == 15 && THIS->x > 669){
                data->state = 23;
            }else if(data->state == 0 && THIS->x > 747){
                data->state = 50;
            }
        }else if(THIS->x > 784 && THIS->x < 944){
            if(data->state == 11 && THIS->x > 850){
                data->state = 8;
            }else if(data->state == 8 && THIS->y < 112){
                data->state = 50;
            }
        }else if(THIS->x > 936 && THIS->x < 1304 && THIS->y > 104){
            if(data->state == 9 && THIS->y > 162 && THIS->x < 1040){
                data->state = 11;
            }else if(data->state == 11 && THIS->x > 1067 && THIS->y < 166){
                data->state = 8;
            }else if(data->state == 8 && THIS->y < 130 && THIS->x < 1112){
                data->state = 13;
            }else if(data->state == 9 && THIS->y > 178 ){
                data->state = 11;
            }else if(data->state == 11 && THIS->y > 166 && THIS->x > 1259){
                data->state = 8;
            }else if(data->state == 8 && THIS->y < 146 && THIS->x > 1112){
                data->state = 50;
            }
        }else if(THIS->x > 1350 && THIS->x < 1624 && THIS->y > 128 && THIS->y < 160){
            if(data->state == 11 && THIS->x > 1459 && THIS->x < 1463){
                data->state = 24;
            }else if(data->state == 11 && THIS->x > 1523){
                data->state = 50;
            }
        }else if(THIS->x > 1350 && THIS->x < 1624 && THIS->y > 160 ){
            if(data->state == 11 && THIS->x > 1603){
                data->state = 50;
                THIS->x-=2;
            }
        }else if(THIS->x > 1232 && THIS->x < 1624 && THIS->y < 128 ){
            if(data->state == 14 && THIS->x < 1264){
                data->state = 16;
            }
        }else if(THIS->x > 1624){
            if(data->state == 27 && THIS->y > 208){
                data->state = 28;
            }else if(data->state == 28 && THIS->x > 1696 && THIS->x < 1702){
                data->state = 26;
                THIS->x+=1;
            }else if(data->state == 26 && THIS->y < 144 && THIS->x < 1747){
                data->state = 30;
            }else if(data->state == 28 && THIS->x > 1747){
                data->state = 26;
                THIS->x+=1;
            }else if(data->state == 26 && THIS->y < 126){
                data->state = 50;
                THIS->x -= 3;
            }
        }
    }
    //  if(current_level == 3){
    //     if(THIS->x < 200){
    //         if(THIS->x < 68 && data->state == 1){
    //             data->state = 0;
    //         }else if (THIS->x > 140 && data->state == 0){
    //             data->state = 1;
    //         }
    //     }else if(THIS->x > 520 && THIS->x < 592){
    //         if(THIS->x < 532 && data->state == 1){
    //             data->state = 0;
    //         }else if (THIS->x > 580 && data->state == 0){
    //             data->state = 1;
    //         }
    //     }else if(THIS->x > 593 && THIS->x < 640){
    //         if(THIS->y < 100 && data->state == 3){
    //             data->state = 2;
    //         }else if (THIS->y > 156  && data->state == 2){
    //             data->state = 3;
    //         }
    //     }else if(THIS->x > 832){
    //         if(THIS->y < 76 && data->state == 3){
    //             data->state = 2;
    //         }else if (THIS->y > 164  && data->state == 2){
    //             data->state = 3;
    //         }
    //     }
    //  }else{
    //     if(THIS->x > 668 && THIS->y < 163 && data->state == 6){
    //         data->state = 4;
    //     }else if(THIS->y > 164 && data->state == 4){
    //         data->state = 6;
    //     }else if(THIS->x > 755 && THIS->y > 164 && data->state == 6){
    //         data->state = 5;
    //     }
    //  }






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
}
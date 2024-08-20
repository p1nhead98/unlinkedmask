#ifndef DIALOGOS_H
#define DIALOGOS_H

#include <gb/gb.h>
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Banks/SetAutoBank.h"
#include "Scroll.h"
#include "Palette.h"
#include "Sprite.h"
#include "Sound.h"
#include "Music.h"



void SetDialog() BANKED;
void CleanText() BANKED;
void CleanWin() BANKED;
#endif
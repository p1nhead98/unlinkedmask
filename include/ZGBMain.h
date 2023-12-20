#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, player)\
_SPRITE_DMG(SpritePlataforma1, plataforma1)\
_SPRITE_DMG(SpritePlataforma2, plataforma2)\
_SPRITE_DMG(SpriteCrusherDown, crusherDown)\
_SPRITE_DMG(SpriteDoorTile1, doorTile1)\
_SPRITE_DMG(SpriteDoorTile2, doorTile2)\
_SPRITE_DMG(SpriteDoorTile3, doorTile3)\
_SPRITE_DMG(SpriteDoorTile4, doorTile4)\
_SPRITE_DMG(SpriteDoorButton, doorButton)\
_SPRITE_DMG(SpriteTimeDoorClosed, timeDoorClosed)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif
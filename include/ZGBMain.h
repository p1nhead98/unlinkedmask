#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, player)\
_SPRITE_DMG(SpritePlataforma1, plataforma1)\
_SPRITE_DMG(SpritePlataforma2, plataforma2)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif
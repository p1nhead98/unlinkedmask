#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateTitleScreen)\
_STATE(StateCutscenes)\
_STATE(StateStage1)\
_STATE(StateStage2)\
_STATE(StateStage3)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, playerCape)\
_SPRITE_DMG(SpriteSpinOrb, plataforma1)\
_SPRITE_DMG(SpriteJumpBox, plataforma2)\
_SPRITE_DMG(SpriteCrusherDown, crusherDown)\
_SPRITE_DMG(SpriteDoorTile1, doorTile1)\
_SPRITE_DMG(SpriteDoorTile2, doorTile2)\
_SPRITE_DMG(SpriteDoorTile3, doorTile3)\
_SPRITE_DMG(SpriteDoorTile4, doorTile4)\
_SPRITE_DMG(SpriteDoorButton, doorButton)\
_SPRITE_DMG(SpriteTimeDoorClosed, timeDoorClosed)\
_SPRITE_DMG(SpriteSpinOrbActivable, plataforma1)\
_SPRITE_DMG(SpritePlayerDeath, playerDeath)\
_SPRITE_DMG(SpritePlayerVfx, playerVFX)\
_SPRITE_DMG(SpriteOnOffBtn, onOffButton)\
_SPRITE_DMG(SpritePlayerNoCape, playerNoCape)\
_SPRITE_DMG(SpriteIntroBigShine, introBigShine)\
_SPRITE_DMG(SpriteIntroMiniShine, introMiniShine)\
_SPRITE_DMG(SpriteIntroFx, introFx)\
_SPRITE_DMG(SpriteJumpBoxEvent, plataforma2)\
_SPRITE_DMG(SpritePlayerCutscenes, playerNCinematic)\
_SPRITE_DMG(SpriteViewerH, viewerHair)\
_SPRITE_DMG(SpriteCapeCuts, capeCuts)\
_SPRITE_DMG(SpriteExplosionCuts, explosionCuts)\
_SPRITE_DMG(SpritePlayerStars, playerStars)\
_SPRITE_DMG(SpritePlayerCutsTemple, playerTempleCuts)\
_SPRITE_DMG(SpriteCrusherUp, crusherDown)\
_SPRITE_DMG(SpriteCrusherLeft, crusherLeft)\
_SPRITE_DMG(SpriteSplitBox, splitBox)\
_SPRITE_DMG(SpriteBoss1, boss1)\
_SPRITE_DMG(SpriteBossFireFlash, bossFireFlash)\
_SPRITE_DMG(SpriteSkullFlame, skullFlame)\
_SPRITE_DMG(SpriteWarning, warning)\
_SPRITE_DMG(SpriteWarning2, warning)\
_SPRITE_DMG(SpriteBossHand1, hand1boss)\
_SPRITE_DMG(SpriteBossHand2, hand2boss)\
_SPRITE_DMG(SpriteBossFire, BossTrailer3)\
_SPRITE_DMG(SpriteElevatorFloor1, elevFloor1)\
_SPRITE_DMG(SpriteElevatorFloor2, elevFloor2)\
_SPRITE_DMG(SpriteElevatorFloor3, elevFloor3)\
_SPRITE_DMG(SpriteKaizoBlock, kaizoBlock)\
_SPRITE_DMG(SpriteBossElec, elecBoss)\
_SPRITE_DMG(SpriteElectBossFx, elecBossFx)\
_SPRITE_DMG(SpritePlayerFinal, playerBackCape)\
_SPRITE_DMG(SpriteBossHair, hair_boss)\
_SPRITE_DMG(SpriteTitleFlash, titleFlash)\
_SPRITE_DMG(SpriteMoon, moon)\
_SPRITE_DMG(SpriteOrbForest, plataforma1)\
_SPRITE_DMG(SpriteOrbTemple, plataforma1)\
_SPRITE_DMG(SpriteSpinOrbEvent, plataforma1)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif
#pragma once

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

//Player Config
#define START_POSITION Vector2(screenWidth/2, screenHeight - 100)
#define BASE_SPEED 200
#define BASE_HP 100
#define BASE_WEAPON_POWER 1
#define BASE_BULLET_SPEED 400
#define BASE_ATTACK_SPEED 0.4

#define SIZE_X 100
#define SIZE_Y 100

//Enemy Config

//Dark Plane

#define E1_START_POSITION Vector2(screenWidth/2, 100)
#define E1_BASE_SPEED 100
#define E1_BASE_HP 30

#define E1_SIZE_X 50
#define E1_SIZE_Y 50

//Bullet Config

#define PB_SIZE_X 40
#define PB_SIZE_Y 40

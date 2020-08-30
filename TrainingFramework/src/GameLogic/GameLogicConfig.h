#pragma once

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

//Player Config
#define START_POSITION Vector2(screenWidth/2, screenHeight - 100)
#define BASE_SPEED 200
#define BASE_HP 100
#define BASE_WEAPON_POWER 1
#define BASE_BULLET_SPEED 600
#define BASE_ATTACK_SPEED 0.4

#define SIZE_X 80
#define SIZE_Y 80

#define DOUBLE_SHOOT_OFFSET 10
#define REAR_SHOOT_OFFSET 20 

//Enemy Config

//Dark Plane

#define E1_START_POSITION Vector2(screenWidth/2, 50)
#define E1_BASE_SPEED 100
#define E1_BASE_HP 30

#define E1_SIZE_X 50
#define E1_SIZE_Y 50

#define E1_SIZE_Y_OFFSET -10
#define E1_SIZE_X_OFFSET -5

#define E1_SCORE 20

//Bullet Config

#define PB_SIZE_X 40
#define PB_SIZE_Y 40

#define BASE_BULLET_POWER 10

//item config

#define ITEM_POWER_UP 1
#define ITEM_HEATH 2

#define ITEM_SIZE_X 50
#define ITEM_SIZE_Y 30

#define ITEM_SPEED 100
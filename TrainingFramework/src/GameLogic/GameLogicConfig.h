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

#define P_HITBOX_OFFSET_X 10
#define P_HITBOX_OFFSET_Y 25

//Enemy Config

//Dark Plane

#define E1_START_POSITION Vector2(screenWidth/2, 50)
#define E1_BASE_SPEED 80
#define E1_BASE_HP 30
#define E1_BASE_AS 2.0f
#define E1_BULLET_SPEED 250

#define E1_SIZE_X 50
#define E1_SIZE_Y 50

#define E1_SIZE_Y_OFFSET -10
#define E1_SIZE_X_OFFSET -5

#define E1_SCORE 20

//Bullet Config

///Type
#define PLAYER_BULLET 0
#define E1_BULLET 1
/// 

// Player bullet
#define PB_SIZE_X 40
#define PB_SIZE_Y 40

#define BASE_BULLET_POWER 10

// Enemy bullet
#define E1B_SIZE_X 30
#define E1B_SIZE_Y 30

//item config

#define ITEM_POWER_UP 1
#define ITEM_HEATH 2

#define ITEM_SIZE_X 50
#define ITEM_SIZE_Y 30

#define ITEM_SPEED 100


//animation config

///explosion

////red explosion

#define RE_NUM_FRAME 9
#define RE_FRAME_TIME 0.04f
#define RE_SIZE 64

///impact

#define I_NUM_FRAME 3
#define I_FRAME_TIME 0.09f
#define I_SIZE 40
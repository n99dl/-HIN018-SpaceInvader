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

#define SIZE_X 60
#define SIZE_Y 60

#define DOUBLE_SHOOT_OFFSET 10
#define REAR_SHOOT_OFFSET 20 

#define P_HITBOX_OFFSET_X 10
#define P_HITBOX_OFFSET_Y 25

//Enemy Config

//Dark Plane

#define E1_ODD 1.0
#define E1_START_POSITION Vector2(screenWidth/2, 30)
#define E1_BASE_SPEED 80
#define E1_BASE_HP 30
#define E1_BASE_AS 2.0f
#define E1_BULLET_SPEED 250

#define E1_SIZE_X 50
#define E1_SIZE_Y 50

#define E1_SIZE_Y_OFFSET -10
#define E1_SIZE_X_OFFSET -5
#define E1_ITEM_ODD 6

#define E1_SCORE 20

//Circle Plane

#define E2_ODD 0.5
#define E2_BASE_HP 70
#define E2_START_POSITION Vector2(0, 30)
#define E2_TYPE_LEFT 0
#define E2_TYPE_RIGHT 1

#define E2_BASE_AS 2.5f
#define E2_BULLET_SPEED 150

#define E2_ITEM_ODD 3
#define E2_SCORE 50


//Motor
#define E3_ODD 0.1
#define E3_HP 500
#define E3_START_POSITION Vector2(screenWidth/2, -30)
#define E3_IDLE_TIME 4.0f
#define E3_MOVE_SPACE Vector2(screenWidth, 300)

#define E3_SIZE_X 100
#define E3_SIZE_Y 100
#define E3_BASE_AS 5.0f
#define E3_SCORE 500

#define E3_OFFSET_X 30
#define E3_OFFSET_Y 30

#define E3_ITEM_ODD 1

//IMPERIAL SPACESHIP

#define E4_FIRST_PHASE 0
#define E4_SECOND_PHASE 1
#define E4_LAST_PHASE 2
#define E4_HP_1 1000
#define E4_HP_2 2000
#define E4_HP_3 3000
#define E4_BASE_SPEED 200
#define E4_SUB_GUN_CD 0.6
#define E4_CIRCLE_GUN_CD 3.5

#define E4_IDLE_TIME 2.0f

#define E4_CIRCLE_SPEED 200
#define E4_SIZE_X 200
#define E4_SIZE_Y 200

#define E4_OFFSET_X 10
#define E4_OFFSET_Y 30
#define E4_SCORE 10000

#define E4_START_POSITION Vector2(screenWidth / 2, - 199)

//Bullet Config

#define HOMING_COOLDOWN 0.1
///Type
#define PLAYER_BULLET 0
#define E1_BULLET 1
#define E3_BULLET 3
/// 

// Player bullet
#define PB_SIZE_X 40
#define PB_SIZE_Y 40

#define BASE_BULLET_POWER 10

// Enemy bullet
#define E1B_SIZE_X 30
#define E1B_SIZE_Y 30


#define E3_BULLET_POWER 40
#define E3_BULLET_SPEED 150

//item config

#define ITEM_POWER_UP 0
#define ITEM_HEATH 1

#define ITEM_SIZE_X 50
#define ITEM_SIZE_Y 30

#define ITEM_SPEED 100


//animation config

///explosion

////red explosion

#define RE_NUM_FRAME 9
#define RE_FRAME_TIME 0.04f
#define RE_SIZE 64

#define BOSS_RE_SIZE 300

////Blue explosion
#define BE_NUM_FRAME 9
#define BE_FRAME_TIME 0.04f
#define BE_SIZE 128

///impact

#define I_NUM_FRAME 3
#define I_FRAME_TIME 0.09f
#define I_SIZE 40







# define M_PI           3.14159265358979323846
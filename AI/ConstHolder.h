#pragma once

const float PLAYER_VERTICAL_SPEED = 225.0f;
const float PLAYER_MAX_SPEED = 400.0;
const float PLAYER_ACCELERATION = 10.0f;
const float PLAYER_DECCELERATION = 12.5f;
const float PLAYER_FIRE_RATE = 1.0f;
const float	PLAYER_NUKE_TIMER = 60.0f;
const float	PLAYER_SUPER_JUMP_TIMER = 1.0f;
const float PLAYER_OFFSET_FROM_GROUND = 0.9f;
const float PLAYER_MAX_LIVES = 5;
const float PLAYER_LAZER_LIFE = 4.0f;
const float PLAYER_SHIELD_TIMER = 10.0f;
const float PLAYER_RAPID_FIRE_TIMER = 10.0f;

const float PLAYER_LAZER_SPEED = PLAYER_MAX_SPEED*1.5f;

const float NEST_MAX_SPEED = 150.0f;
const float NEST_DISTANCE_TO_FIRE = 300.0f;
const float NEST_DISTANCE_TO_EVADE = 500.0f;
const float NEST_FIRE_RATE = 2.5f;
const float NEST_SPAWN_RATE = 8.0f;
const float NEST_INTERCEPTOR_MISSILE_MAX_SPEED = PLAYER_MAX_SPEED;
const float NEST_INTERCEPTOR_MISSILE_LIFE_TIME = 10.0f;

const int	NEST_INTERCEPTOR_MISSILE_MAX_COUNT = 2;
const int	NEST_MAX_ABDUCTORS_SPAWN_COUNT = 20;
const int	NEST_MAX_HEALTH = 3;

const int	ABDUCTOR_MAX_HEALTH = 1;
const float ABDUCTOR_DISTANCE_TO_FIRE = 350.0f;
const float ABDUCTOR_FIRE_RATE = 2.5f;
const float ABDUCTOR_BULLET_LIFE_TIME = 10.0f;
const float ADBUCTOR_BULLET_SPEED = 200.0f;

const float ABDUCTOR_SPEED = 5.0f;
const float ABDUCTOR_MAX_SPEED = 5.0f;
const float ABDUCTOR_ACCELERATION = 5.0f;
const float ABDUCTOR_DECCELERATION = 5.0f;

const float MUTANT_SPEED = 5.0f;
const float MUTANT_MAX_SPEED = 5.0f;
const float MUTANT_ACCELERATION = 5.0f;
const float MUTANT_DECCELERATION = 5.0f;

const float METEOR_FALL_SPEED = 20.0f;
const float MUTANTS_PER_NEST = 1.5f;

const float	PI = 3.141592;
const float SCREEN_TIME_SIZE = 9.0f;

const int	MAX_METEORS = SCREEN_TIME_SIZE * 1.5f;
const int	MAX_POWER_UPS = 1;

const int	RADAR_HIGHT = 150;
const int   HUD_HEIGHT = 225;
const float ICON_SCALE = 0.5f;
const float SIZE_SCALAR = 0.20f;
const float RADAR_CAMERA_RECTANGLE = 2.5f + 2.5f;

const int	POWER_UP_SCORE = 10;
const int	ABDUCTOR_SCORE = 50;
const int	MUTANT_SCORE = 100;
const int	NEST_SCORE = 250;

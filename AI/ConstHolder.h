#pragma once

const float PLAYER_VERTICAL_SPEED = 150.0f;
const float PLAYER_MAX_SPEED = 300.0f;
const float PLAYER_ACCELERATION = 10.0f;
const float PLAYER_DECCELERATION = 12.5f;
const float PLAYER_FIRE_RATE = 1.0f;
const float	PLAYER_NUKE_TIMER = 60.0f;
const float	PLAYER_SUPER_JUMP_TIMER = 5.0f;
const float PLAYER_OFFSET_FROM_GROUND = 0.9f;
const float PLAYER_MAX_LIVES = 3;
const float PLAYER_LAZER_LIFE = 2.0f;
const float PLAYER_SHIELD_TIMER = 5.0f;
const float PLAYER_RAPID_FIRE_TIMER = 5.0f;

const float PLAYER_LAZER_SPEED = PLAYER_MAX_SPEED*1.5f;

const float NEST_MAX_SPEED = 150.0f;
const float NEST_DISTANCE_TO_FIRE = 300.0f;
const float NEST_DISTANCE_TO_EVADE = 500.0f;
const float NEST_FIRE_RATE = 2.5f;
const float NEST_SPAWN_RATE = 5.0f;
const float NEST_INTERCEPTOR_MISSILE_MAX_SPEED = PLAYER_MAX_SPEED;
const float NEST_INTERCEPTOR_MISSILE_LIFE_TIME = 10.0f;

const int	NEST_INTERCEPTOR_MISSILE_MAX_COUNT = 2;
const int	NEST_MAX_ABDUCTORS_SPAWN_COUNT = 20;
const int	NEST_MAX_HEALTH = 3;

const float ABDUCTOR_SPEED = 5.0f;
const float ABDUCTOR_MAX_SPEED = 5.0f;
const float ABDUCTOR_ACCELERATION = 5.0f;
const float ABDUCTOR_DECCELERATION = 5.0f;

const float MUTANT_SPEED = 5.0f;
const float MUTANT_MAX_SPEED = 5.0f;
const float MUTANT_ACCELERATION = 5.0f;
const float MUTANT_DECCELERATION = 5.0f;

const float METEOR_FALL_SPEED = 20.0f;

const float	PI = 3.141592;
const float SCREEN_TIME_SIZE = 2.0f;// 9.0f;

const int	MAX_METEORS = SCREEN_TIME_SIZE*2;
const int	MAX_POWER_UPS = 1;
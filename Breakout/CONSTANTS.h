#pragma once

// implemented powerups
enum POWERUPS
{
    bigPaddle,
    smallPaddle,
    fastBall,
    slowBall,
    fireBall,
    none
};

// Window settings
constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;
constexpr const char* WINDOW_TITLE = "Game";

// Paddle settings
constexpr float PADDLE_WIDTH = 100.0f;
constexpr float PADDLE_HEIGHT = 20.0f;
// CHANGE: Paddle Speed increased from 300.0f to 500.0f preperation for bullet hell - Calum B.
constexpr float PADDLE_SPEED = 500.0f;

// Ball settings
constexpr float BALL_RADIUS = 10.0f;
constexpr float BALL_SPEED = 400.0f;

// Brick settings
constexpr float BRICK_WIDTH = 75.0f;
constexpr float BRICK_HEIGHT = 20.0f;
constexpr float BRICK_PADDING = 5.0f;
constexpr int BRICK_ROWS = 5;
constexpr int BRICK_COLUMNS = 10;

// Power-up settings
constexpr float POWERUP_RADIUS = 15.0f;
constexpr float POWERUP_SPEED = 150.0f;

// UI settings
constexpr float UI_LIFE_RADIUS = 15.0f;
constexpr float UI_LIFE_PADDING = 20.0f;

// Other game settings
constexpr float PAUSE_TIME_BUFFER = 0.5f;
constexpr float POWERUP_FREQUENCY = 7.5f;
constexpr int INITIAL_LIVES = 3;

// NEW
// Bullet settings
constexpr float BULLET_WIDTH = 6.0f;
constexpr float BULLET_HEIGHT = 14.0f;
constexpr float BULLET_SPEED = 300.0f;
constexpr float BULLET_FIRE_RATE = 0.5f; 

// Bullet Types
constexpr float SPLIT_OFFSET = 120.0f;
constexpr float BIG_SCALE = 2.0f;
constexpr float REPEAT_DELAY = 0.25f;


// Colour Palette
const sf::Color ballEffectsColour = sf::Color(100, 100, 200, 255); // blue-ish?
const sf::Color paddleEffectsColour = sf::Color(255, 250, 205); // lemon chiffon -- very fancy.
const sf::Color extraBallEffectsColour = sf::Color(41, 110, 1); // metallic green



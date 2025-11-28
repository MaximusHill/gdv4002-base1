#pragma once

enum class GameState {
    MAIN_MENU,
    PLAYERVELOCITYRESET,
    PLAYING,
    GAME_OVER
};

// current state (defined in main.cpp)
extern GameState currentGameState;

// function to reset game (defined in main.cpp)


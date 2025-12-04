#pragma once

enum class GameState {
    MAIN_MENU,
    PLAYERVELOCITYRESET,
    PLAYING,
    GAME_OVER
};


extern GameState currentGameState;



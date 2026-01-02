#pragma once

#include "SFML/System/Time.hpp"

struct ProgramState {
    // function to run when the state is loaded
    int (*m_init)();

    // function called at ever frame
    void (*m_update)(sf::Time deltaTime);

    // function called at every frame, but after m_update
    void (*m_gui)();

    // function called at every frame, but after m_gui
    void (*m_draw)();

    // function called just before the state is destroyed 
    void (*m_shutdown)();
};

struct ProgramStateDispatcher {
    ~ProgramStateDispatcher();

    void update(sf::Time deltaTime);
    void gui();
    void draw();

    void setProgramState(ProgramState& state);
private:
    ProgramState* m_currState = nullptr;
};

extern ProgramState initState;
extern ProgramState trainingState;
extern ProgramState liveState;

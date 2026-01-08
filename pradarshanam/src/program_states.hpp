#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>

struct ProgramStateContext {
    sf::RenderWindow* window;
};

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

    // function which returns which state to change to
    ProgramState* (*m_getNextState)();

    ProgramStateContext* m_context;
};

struct ProgramStateDispatcher {
    ProgramStateDispatcher(ProgramStateContext ctx);
    ~ProgramStateDispatcher();

    void update(sf::Time deltaTime);
    void gui();
    void draw();
    ProgramState* getNextState();

    void setProgramState(ProgramState& state);
private:
    ProgramStateContext m_currCtx;
    ProgramState* m_currState = nullptr;
};

extern ProgramState initState;
extern ProgramState trainingState;
extern ProgramState liveState;

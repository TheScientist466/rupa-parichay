#include "program_states.hpp"
#include "SFML/System/Time.hpp"

#include <iostream>
#include <imgui.h>

void ProgramStateDispatcher::update(sf::Time dt)    { m_currState->m_update(dt); }
void ProgramStateDispatcher::gui()                  { m_currState->m_gui(); }
void ProgramStateDispatcher::draw()                 { m_currState->m_draw(); }

void ProgramStateDispatcher::setProgramState(ProgramState& s) {
    if(m_currState != nullptr) {
        m_currState->m_shutdown();
    }
    m_currState = &s;
    m_currState->m_init();
}

ProgramStateDispatcher::~ProgramStateDispatcher() {
    if(m_currState != nullptr) {
        m_currState->m_shutdown();
    }
}

/// --- Init State ---
/// This state will be loaded at the start of the program.
/// This state will ask the user which state to load. Kind
/// of like a bootloader, but fot this program.
ProgramState initState = {
    .m_init = []() {
        std::cout << "Welcome to Rupa Parichay" << std::endl;
        return 0;
    },
    .m_update = [](sf::Time dt) { },
    .m_gui = []() {
        ImGui::Begin("Loader");
        ImGui::Text("Hello From Rupa Parichay");
        ImGui::End();
    },
    .m_draw = []() { },
    .m_shutdown = []() {
        std::cout << "Goodbye!" << std::endl;
    }
};


ProgramState trainingState;
ProgramState liveState;

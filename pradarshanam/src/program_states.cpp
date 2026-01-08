#include "program_states.hpp"
#include "SFML/System/Vector2.hpp"
#include "canvas.hpp"

#include <iostream>
#include <imgui.h>
#include <SFML/System/Time.hpp>

ProgramStateContext ProgramStateDispatcher::s_currCtx;

void ProgramStateDispatcher::update(sf::Time dt)        { m_currState->m_update(dt); }
void ProgramStateDispatcher::gui()                      { m_currState->m_gui(); }
void ProgramStateDispatcher::draw()                     { m_currState->m_draw(); }
ProgramState* ProgramStateDispatcher::getNextState()    { return m_currState->m_getNextState(); }

void ProgramStateDispatcher::setProgramState(ProgramState& s) {
    if(m_currState != nullptr) {
        m_currState->m_shutdown();
    }
    m_currState = &s;
    m_currState->m_init();
}

void ProgramStateDispatcher::setProgramStateContext(ProgramStateContext _ctx) {
    s_currCtx = _ctx;
}

ProgramStateDispatcher::~ProgramStateDispatcher() {
    if(m_currState != nullptr) {
        m_currState->m_shutdown();
    }
}

/// --- Training State ---
/// This state will train and save the model.
ProgramState trainingState = {
    .m_init = []() {
        std::cout << "Training State" << std::endl;
        return 0;
    },
    .m_update = [](sf::Time dt) { },
    .m_gui = []() {
        ImGui::Begin("Trainer");
        ImGui::Text("Training State");
        ImGui::End();
    },
    .m_draw = []() { },
    .m_shutdown = []() { 
        std::cout << "Exiting Training State" << std::endl;
    },
    .m_getNextState = []() {
        return (ProgramState*)nullptr;
    }
};
/// --- End of Training State ---

/// --- Live State ---
/// This state will test and show the model
Canvas* live_canvas;
ProgramState liveState {
    .m_init = []() {
        std::cout << "Live State" << std::endl;
        sf::Vector2u winSize = ProgramStateDispatcher::s_currCtx.window->getSize();
        sf::Vector2u canvasSize(winSize.y, winSize.y);
        live_canvas = new Canvas(canvasSize);
        live_canvas->setParentWindow(ProgramStateDispatcher::s_currCtx.window);
        return 0;
    },
    .m_update = [](sf::Time dt) { },
    .m_gui = []() {
        ImGui::Begin("Live");
        ImGui::Text("Live State");
        ImGui::End();

        live_canvas->gui();
    },
    .m_draw = []() { },
    .m_shutdown = []() { 
        std::cout << "Exiting Live State" << std::endl;
        delete live_canvas;
    },
    .m_getNextState = []() {
        return (ProgramState*)nullptr;
    }
};
/// --- End of Live State ---

/// --- Init State ---
/// This state will be loaded at the start of the program.
/// This state will ask the user which state to load. Kind
/// of like a bootloader, but fot this program.
ProgramState* initStateNextState = nullptr;
ProgramState initState = {
    .m_init = []() {
        std::cout << "Welcome to Rupa Parichay" << std::endl;
        return 0;
    },
    .m_update = [](sf::Time dt) { },
    .m_gui = []() {
        ImGui::Begin("Loader", NULL, ImGuiWindowFlags_NoCollapse);
        ImGui::Text("Do you want to start training or load the model?");
        if(ImGui::Button("Train")) {
            initStateNextState = &trainingState;
        }
        ImGui::SameLine();
        if(ImGui::Button("Load")) {
            initStateNextState = &liveState;
        }
        ImGui::End();
    },
    .m_draw = []() { },
    .m_shutdown = []() { },
    .m_getNextState = []() {
        return initStateNextState;
    }
};
/// --- End Init State ---

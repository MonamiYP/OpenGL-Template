#pragma once

#include <GLFW/glfw3.h>
#include "ApplicationState.hpp"

class Input {
    private:

    public:
        void processInput(ApplicationState& state);
        void toggleImGUI(ApplicationState& state);
};
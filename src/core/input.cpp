#include "Input.hpp"

void Input::processInput(ApplicationState& state) {
    if (glfwGetKey(state.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(state.window, true);

    toggleImGUI(state);
}

void Input::toggleImGUI(ApplicationState& state) {
    static bool g_pressed_prev = false;
    bool g_pressed = glfwGetKey(state.window, GLFW_KEY_G) == GLFW_PRESS;

    if (g_pressed && !g_pressed_prev) {
        state.guiEnable = !state.guiEnable;
        if (state.guiEnable) {
            glfwSetInputMode(state.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(state.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    g_pressed_prev = g_pressed;
}
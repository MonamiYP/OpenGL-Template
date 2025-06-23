#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>

#include "Renderer.hpp"
#include "ImGUI.hpp"
#include "ApplicationState.hpp"
#include "Input.hpp"
#include "Window.hpp"

#include "primitives/Rectangle.hpp"
#include "VertexBufferLayout.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

int main() {
    ApplicationState state;
    Window window;
    if (window.setupWindow(state.window) != 0) return -1;

    ImGUI imGUI(state.window);
    Renderer renderer;
    Input input;

    std::vector<float> vertices = Rectangle::GetVertices();
    std::vector<unsigned int> indices = Rectangle::GetIndices();

    VertexArray vao;
    VertexBuffer vbo(vertices.data(), vertices.size() * sizeof(float));
    VertexBufferLayout layout;
    layout.AddAttribute(GL_FLOAT, 3);
    IndexBuffer ibo(indices.data(), indices.size() * sizeof(unsigned int));
    vao.AddBuffer(vbo, layout);

    Shader shader;
    std::string vertex_source = shader.ParseShader("../res/shaders/basic.vs");
    std::string fragment_source = shader.ParseShader("../res/shaders/basic.fs");
    shader.CreateShaderProgram(vertex_source, fragment_source);

    while (!glfwWindowShouldClose(state.window)) {
        float currentTime = glfwGetTime();
        state.deltaTime = currentTime - state.lastTime;
        state.lastTime = currentTime;

        input.processInput(state);
        renderer.Clear();

        if(state.guiEnable) { imGUI.drawGUI(); };

        renderer.Draw(vao, ibo, shader);

        glfwSwapBuffers(state.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

// renderer.Draw(vao, ibo, shader);
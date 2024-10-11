
#include "GLFW/glfw3.h"
#include <cstdlib>
#include <iostream>

void glfwErrorCallback(int error, const char* description) {
    std::cout << "GLFW Error: " << description << std::endl;
    std::exit(1);
}

void create_window() {
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        std::exit(1);
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Vulkan", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cout << "Failed to create window" << std::endl;
        std::exit(1);
    }
    

    /* if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        glfwDestroyWindow(window);
        glfwTerminate();
        std::cout << "Failed to create Vulkan instance" << std::endl;
        std::exit(1);
    } */

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

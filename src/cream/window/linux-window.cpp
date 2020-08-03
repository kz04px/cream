#include "linux-window.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <clog/clog.hpp>
#include <iostream>
#include "../events/keyboard-event.hpp"
#include "../events/mouse-event.hpp"
#include "../events/window-event.hpp"
#include "../keys.hpp"

namespace cream {

// Convert key constants from glfw to cream
// https://www.glfw.org/docs/latest/group__keys.html
int glfw_to_cream(int key) {
    if (GLFW_KEY_0 <= key && key <= GLFW_KEY_9) {
        const int offset = key - GLFW_KEY_0;
        return CREAM_KEY_0 + offset;
    } else if (GLFW_KEY_A <= key && key <= GLFW_KEY_Z) {
        const int offset = key - GLFW_KEY_A;
        return CREAM_KEY_A + offset;
    } else if (GLFW_KEY_ESCAPE <= key && key <= GLFW_KEY_UP) {
        const int offset = key - GLFW_KEY_ESCAPE;
        return CREAM_KEY_ESCAPE + offset;
    } else if (key == GLFW_KEY_SPACE) {
        return CREAM_KEY_SPACE;
    } else if (GLFW_KEY_F1 <= key && key <= GLFW_KEY_F12) {
        const int offset = key - GLFW_KEY_F1;
        return CREAM_KEY_F1 + offset;
    } else if (GLFW_KEY_LEFT_SHIFT <= key && key <= GLFW_KEY_LEFT_ALT) {
        const int offset = key - GLFW_KEY_LEFT_SHIFT;
        return CREAM_KEY_LEFT_SHIFT + offset;
    } else if (GLFW_KEY_RIGHT_SHIFT <= key && key <= GLFW_KEY_RIGHT_ALT) {
        const int offset = key - GLFW_KEY_RIGHT_SHIFT;
        return CREAM_KEY_RIGHT_SHIFT + offset;
    } else {
        return CREAM_KEY_NONE;
    }
}

void callback_window_size(GLFWwindow *window, int width, int height) {
    assert(window);
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    data.width_ = width;
    data.height_ = height;

    WindowResizeEvent event(width, height);
    data.callback_(event);
}

void callback_window_close(GLFWwindow *window) {
    assert(window);
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    WindowCloseEvent event;
    data.callback_(event);
}

void callback_cursor_position(GLFWwindow *window, double xpos, double ypos) {
    assert(window);
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);
    data.mouse_x_ = xpos;
    data.mouse_y_ = ypos;

    MouseMoveEvent event(xpos, ypos);
    data.callback_(event);
}

void callback_mouse_button(GLFWwindow *window, int button, int action, int mods) {
    assert(window);
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    if (action == GLFW_PRESS) {
        MouseDownEvent event(data.mouse_x_, data.mouse_y_, button);
        data.callback_(event);
    } else if (action == GLFW_RELEASE) {
        MouseUpEvent event(data.mouse_x_, data.mouse_y_, button);
        data.callback_(event);
    } else {
        assert(false);
    }
}

void callback_keyboard(GLFWwindow *window, int key, int scancode, int action, int mods) {
    assert(window);
    WindowData &data = *(WindowData *)glfwGetWindowUserPointer(window);

    const int cream_key = glfw_to_cream(key);

    if (action == GLFW_PRESS) {
        KeyPressEvent event(cream_key, scancode, mods);
        data.callback_(event);
    } else if (action == GLFW_RELEASE) {
        KeyReleaseEvent event(cream_key, scancode, mods);
        data.callback_(event);
    } else if (action == GLFW_REPEAT) {
        KeyRepeatEvent event(cream_key, scancode, mods);
        data.callback_(event);
    } else {
        assert(false);
    }
}

void callback_error(int error_code, const char *description) {
    clog::Log::get()->error(description, " (", error_code, ")");
}

LinuxWindow::LinuxWindow(const std::string &title, const int width, const int height) {
    data_.title_ = title;
    data_.width_ = width;
    data_.height_ = height;

    // Set callbacks -- Errors
    glfwSetErrorCallback(callback_error);

    bool success = glfwInit();
    if (!success) {
        throw "glfwInit() failure";
    }

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window_ = glfwCreateWindow(data_.width_, data_.height_, data_.title_.c_str(), nullptr, nullptr);
    if (!window_) {
        throw "glfwCreateWindow() failure";
    }

    glfwMakeContextCurrent(window_);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(10.0);
    glLineWidth(2.0);

    glfwSetWindowUserPointer(window_, &data_);

    // Set callbacks -- Window
    glfwSetWindowSizeCallback(window_, callback_window_size);
    glfwSetWindowCloseCallback(window_, callback_window_close);
    // Set callbacks -- Mouse
    glfwSetCursorPosCallback(window_, callback_cursor_position);
    glfwSetMouseButtonCallback(window_, callback_mouse_button);
    // Set callbacks -- Keyboard
    glfwSetKeyCallback(window_, callback_keyboard);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    while ((err = glGetError()) != GL_NO_ERROR) {
        clog::Log::get()->warn("glewInit() error ", err);
    }
}

LinuxWindow::~LinuxWindow() {
    if (window_) {
        glfwDestroyWindow(window_);
    }
    glfwTerminate();
}

void LinuxWindow::title(const std::string &title) {
    data_.title_ = title;
    glfwSetWindowTitle(window_, title.c_str());
}

void LinuxWindow::vsync(const bool n) {
    if (n == data_.vsync_) {
        return;
    }

    if (n) {
        // TODO:
        // -- Set vsync true
    } else {
        // TODO:
        // -- Set vsync false
    }
}

void LinuxWindow::update() {
}

void LinuxWindow::clear() {
    glClearColor(clear_colour_.r, clear_colour_.g, clear_colour_.b, clear_colour_.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void LinuxWindow::swap_buffer() {
    glfwSwapBuffers(window_);
}

void LinuxWindow::poll_events() {
    glfwPollEvents();
}

void LinuxWindow::resize(const int w, const int h) {
    glViewport(0, 0, w, h);
}

void LinuxWindow::hide_mouse() {
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void LinuxWindow::show_mouse() {
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

}  // namespace cream

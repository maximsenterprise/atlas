
#include "atlas/core/exec_error.hpp"
#include "atlas/window.hpp"
#include <iostream>
#include <string>

using namespace atlas;

int main() {
    Window window(800, 600, "Atlas Engine", true); 
    window.create_console();
    window.create();
    return 0;
}

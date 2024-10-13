
#include "atlas/core/exec_error.hpp"
#include "atlas/scene.hpp"
#include "atlas/shape.hpp"
#include "atlas/window.hpp"
#include <iostream>
#include <string>

using namespace atlas;

class MyOwnScene : public Scene {
  public:
    void setup() {
        triangle = new Triangle(this);
        std::cout << "Scene setup" << std::endl;
    }
    void render() {}
    void update() {
        triangle->render();
    }

  private:
    atlas::Triangle *triangle = nullptr;
};

int main() {
    Window window(800, 600, "Atlas Engine", true);
    /* MyOwnScene scene;  */
    window.create_console(); 
    window.render_scene(new MyOwnScene());
    window.create();
    return 0;
}

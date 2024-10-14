
#include "atlas/camera.hpp"
#include "atlas/core/exec_error.hpp"
#include "atlas/scene.hpp"
#include "atlas/shape.hpp"
#include "atlas/unit.hpp"
#include "atlas/window.hpp"
#include <iostream>
#include <string>

using namespace atlas;

class MyOwnScene : public Scene {
  public:
    void setup() {
        triangle = new Triangle(this, Size(500, 500, 500), Position(0.0, 0.0, 0.0), "MyTriangle");
        Camera* camera = new Camera("MyCamera", Position(0.0, 0.0, 0.0), Size(800, 600, 0), 0, triangle);
        std::cout << "Scene setup" << std::endl;
    }
    void render() {}
    void update() {
        if (triangle == nullptr) {
            ExecutionError error = ExecutionError("Triangle is null");
            error.express();
        }
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

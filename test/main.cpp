
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
        Color color = AtlasPalette::green;
        cube = new Cube(this, Size(700, 700, 700),
                                Position(1, 1, 0), color.with_alpha(50), "MyTriangle");
        cube->color_face(color.with_alpha(50), CubeFace::TOP);
        Camera* camera = new Camera("MainCamera", Position(0.0, 0.0, 0.0), Size(10, 10, 10), 0, cube);
        std::cout << "Scene setup" << std::endl;
    }
    void render() {}
    void update() {
        if (cube == nullptr) {
            ExecutionError error = ExecutionError("Triangle is null");
            error.express();
        }
        cube->render();
    }

  private:
    atlas::Cube *cube = nullptr;
};

int main() {
    Window window(800, 600, "Atlas Engine", true);
    /* MyOwnScene scene;  */
    window.create_console();
    window.render_scene(new MyOwnScene());
    window.create();
    return 0;
}

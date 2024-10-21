
#include "atlas/camera.hpp"
#include "atlas/core/exec_error.hpp"
#include "atlas/event.hpp"
#include "atlas/scene.hpp"
#include "atlas/shape.hpp"
#include "atlas/texture.hpp"
#include "atlas/unit.hpp"
#include "atlas/window.hpp"
#include <concepts>
#include <iostream>
#include <string>

using namespace atlas;

class MyOwnScene : public Scene {
  public:
    void setup() {
        Color color = AtlasPalette::green;
        cube = new Cube(this, Size(700, 700, 700),
                                Position(1, 1, 0), "MyTriangle"); 
        Texture texture = Texture::fromBMP("./test/textures/cube_texture.bmp");
        cube->set_texture(texture);
        /* cube->color(AtlasPalette::green); */
        Camera* camera = new Camera("MainCamera", Position(0.0, 0.0, 0.0), Size(10, 10, 10), 0, cube);
        std::cout << "Scene setup" << std::endl;
        int count = 0; 

        Event event;
        event.add([] { std::cout << "Event triggered " << std::endl; });
        PredicateEvent predicateEvent([&count] { count++; return count < 10; }, event); 
    }
    void render() {
    }
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

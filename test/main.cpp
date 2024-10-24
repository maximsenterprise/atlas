
#include "atlas/camera.hpp"
#include "atlas/core/exec_error.hpp"
#include "atlas/elements.hpp"
#include "atlas/event.hpp"
#include "atlas/mouse.hpp"
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
        Texture texture = Texture::fromBMP("./test/textures/sample.bmp");
        cube->set_texture(texture);
        /* cube->color(AtlasPalette::green); */
        Camera* camera = new Camera("MainCamera", Position(1, 1, 5), 45, Size(10, 10, 10), 0, cube);
        std::cout << "Scene setup" << std::endl;
        int count = 0; 

        Mouse::lock_cursor(); 
        
        FirstPersonCamera* first_person_camera = new FirstPersonCamera();
        first_person_camera->apply_to(camera);
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

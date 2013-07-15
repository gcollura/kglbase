#include "game.h"

void Game::setup_controls() {

    if (window().joypad_count() > 0) {
        window().joypad(0).axis_while_nonzero_connect(0, [=](kglt::AxisRange range, kglt::Axis) mutable {
                auto pos = scene().camera().position();
                pos.x += range / 100.f;
                scene().camera().move_to(pos);
        });
        window().joypad(0).axis_while_nonzero_connect(1, [=](kglt::AxisRange range, kglt::Axis) mutable {
                scene().camera().move_forward(range / 100.f);
        });
        window().joypad(0).axis_while_nonzero_connect(2, [=](kglt::AxisRange range, kglt::Axis) mutable {
                scene().camera().rotate_y(range);
        });
        window().joypad(0).axis_while_nonzero_connect(3, [=](kglt::AxisRange range, kglt::Axis) mutable {
                scene().camera().rotate_x(range);
        });

    }

    window().keyboard().key_while_down_connect(kglt::KEY_CODE_w, [=](kglt::KeyEvent, double dt) mutable {
            scene().camera().move_forward(dt);
    });
    window().keyboard().key_while_down_connect(kglt::KEY_CODE_q, [=](kglt::KeyEvent, double dt) mutable {
            auto pos = scene().camera().position();
            pos.y += dt;
            scene().camera().move_to(pos);
    });
    window().keyboard().key_while_down_connect(kglt::KEY_CODE_e, [=](kglt::KeyEvent, double dt) mutable {
            auto pos = scene().camera().position();
            pos.y -= dt;
            scene().camera().move_to(pos);
    });

}

bool Game::do_init() {
    
    window().viewport().set_background_colour(kglt::Colour::black);

    scene().camera().set_perspective_projection(
            45.0,
            float(window().width()) / window().height(),
            0.1,
            1000.0
            );

    stage().set_ambient_light(kglt::Colour(0.1, 0.1, 0.1, 1.0));

    kglt::TextureID texture = stage().new_texture_from_file("data/brick.png");

    for (int i = 0; i < 5; i++) {
        kglt::ActorID id = stage().geom_factory().new_cube(0.5f);
        stage().actor(id).move_to(i - 2, 1, -5.0);

        stage().actor(id).mesh().lock()->set_texture_on_material(0, texture); 
        actors.push_back(id);
    }

    kglt::MeshID mid = stage().new_mesh_from_file("data/cube.obj");
    plane = stage().new_actor(mid);
    stage().actor(plane).move_to(0, 0, -30);

    kglt::Light& light = stage().light(stage().new_light());
    light.move_to(5.0, 0.0, -3.0);
    light.set_diffuse(kglt::Colour::green);
    light.set_attenuation_from_range(10.0);

    kglt::Light& light2 = stage().light(stage().new_light());
    light2.move_to(-5.0, 0.0, -3.0);
    light2.set_diffuse(kglt::Colour::blue);
    light2.set_attenuation_from_range(50.0);

    kglt::Light& light3 = stage().light(stage().new_light());
    light3.move_to(0.0, 15.0, -3.0);
    light3.set_diffuse(kglt::Colour::red);
    light3.set_attenuation_from_range(50.0);

    setup_controls();

    return true;
}

void Game::do_step(double dt) {
    for (auto id : actors) {
        stage().actor(id).rotate_x(5.f);
    }
}

void Game::do_cleanup() { }


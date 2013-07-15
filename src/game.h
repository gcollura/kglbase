#ifndef GAME_H
#define GAME_H

#include <kglt/kglt.h>
#include <list>
#include <memory>
#include <stdint.h>

class Game : public kglt::App {

public:
    Game(const unicode& title=_u("KGLT Application"), uint32_t width = 800, uint32_t height = 600, uint8_t bpp = 0, bool fullscreen = false) :
        App(title, width, height, bpp, fullscreen) {
    };

private:
    void setup_controls();

    bool do_init();
    void do_step(double dt);
    void do_cleanup();

    std::list<kglt::ActorID> actors;
    kglt::ActorID plane;
};
#endif

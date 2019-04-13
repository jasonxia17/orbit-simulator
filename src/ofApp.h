#pragma once

#include "ofMain.h"

namespace physicstools {

class OrbitSimulator : public ofBaseApp {
private:
    double theta_ = 0.0;

public:
    // Function used for one time setup
    void setup();

    // Main event loop functions called on every frame
    void update();
    void draw();

    // Event driven functions, called on appropriate user action
    void keyPressed(int key);
    void windowResized(int w, int h);
};
}  // namespace physicstools

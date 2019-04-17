#pragma once

#include "ofMain.h"
#include "celestial_body.h"

using glm::vec2;

namespace physicstools {

class OrbitSimulator : public ofBaseApp {
public:
    // Function used for one time setup
    void setup();

    // Main event loop functions called on every frame
    void update();
    void draw();

    // Event driven functions, called on appropriate user action
    void keyPressed(int key);
    void windowResized(int w, int h);

private:
    vec2 getScreenCoordinates(vec2 real_coordinates);
    Body planet;
};
}  // namespace physicstools

#pragma once

#include <vector>

#include "celestial_body.hpp"
#include "ofMain.h"
#include "ofxGui.h"
#include "orbit_simulator.hpp"

using glm::vec2;

namespace physicsvisuals {

class ChaoticOrbitSimulator : public OrbitSimulator {
public:
    /**
     * Function used for one time setup. Sets the title and background of the app.
     */
    void setup() override;

    /**
     * If the simulation is RUNNING, this method executes one step of Euler on every
     * planet and increments the time counter. (Called on every frame.)
     */
    void update() override;

    void draw() override;

private:
    /**
     * A list of all bodies in this system.
     */
    std::vector<CelestialBody> body_list_;
};

}  // namespace physicsvisuals
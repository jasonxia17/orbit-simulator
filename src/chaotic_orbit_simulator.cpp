#include "chaotic_orbit_simulator.hpp"

namespace physicsvisuals {

void ChaoticOrbitSimulator::setup() {
    OrbitSimulator::setup();
    body_list_.push_back(CelestialBody(
        *this, 5, 0.15, ofColor::blue, ofColor::orange, vec2(3, -3), vec2(-2, -2)));
    body_list_.push_back(CelestialBody(
        *this, 30, 0.2, ofColor::magenta, ofColor::orange, vec2(0, 0), vec2(0.1, 0.1)));
    body_list_.push_back(CelestialBody(
        *this, 3, 0.1, ofColor::green, ofColor::orange, vec2(5, -5), vec2(1, 2)));
    for (CelestialBody& body : body_list_) {
        body.resetMotion();
    }
}

void ChaoticOrbitSimulator::update() {
    if (current_state_ == RUNNING) {
        // if (planet_.crashedIntoAnotherBody(star_)) {
        //     current_state_ = PLANET_CRASHED;
        //     return;
        // }

        const double kTimeStep = 0.01;
        for (CelestialBody& body : body_list_) {
            body.updateVelocityAndPosition(kTimeStep, body_list_);
        }
        time_elapsed_ += kTimeStep;
    }
}

void ChaoticOrbitSimulator::drawVisuals() const {
    for (const CelestialBody& body : body_list_) {
        body.drawTrail();
        body.drawVelocityVector();
        body.drawBody();
    }
}

}  // namespace physicsvisuals
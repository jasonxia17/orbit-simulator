#include "chaotic_orbit_simulator.hpp"

namespace physicsvisuals {

void ChaoticOrbitSimulator::setup() {
    OrbitSimulator::setup();
    body_list_.push_back(CelestialBody(*this, 5, 0.15, vec2(3, -3), vec2(-2, -2), ofColor::blue));
    body_list_.push_back(CelestialBody(*this, 30, 0.2, vec2(0, 0), vec2(0.1, 0.1), ofColor::magenta));
    body_list_.push_back(CelestialBody(*this, 3, 0.1, vec2(5, -5), vec2(1, 2), ofColor::green));
}

void ChaoticOrbitSimulator::update() {
    if (current_state_ == GETTING_USER_INPUT) {
        for (CelestialBody& body : body_list_) {
            body.resetMotion();
        }

    } else if (current_state_ == RUNNING) {
        // pairwise check for crashes
        for (size_t i = 0; i < body_list_.size(); ++i) {
            for (size_t j = i + 1; j < body_list_.size(); ++j) {
                if (body_list_[i].crashedIntoAnotherBody(body_list_[j])) {
                    current_state_ = PLANET_CRASHED;
                    return;
                }
            }
        }

        const double kTimeStep = 0.01;
        for (CelestialBody& body : body_list_) {
            body.updateVelocityAndPosition(kTimeStep, body_list_);
        }
        time_elapsed_ += kTimeStep;
    }
}

void ChaoticOrbitSimulator::draw() {
    for (const CelestialBody& body : body_list_) {
        body.drawTrail();
        body.drawVelocityVector();
        body.drawBody();
    }

    if (current_state_ == PLANET_CRASHED) {
        drawCrashMessage();
    }
}

}  // namespace physicsvisuals
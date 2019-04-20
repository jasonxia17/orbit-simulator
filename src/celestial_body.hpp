#pragma once
#include "ofMain.h"

using glm::vec2;

namespace physicsvisuals {

class CelestialBody {

public:
    /**
     * Parameters are hard-coded for now, will have legit constructor later.
     */
    CelestialBody() {
        position_.x = 0.5;
        velocity_.y = 6;
    }

    const vec2& getPosition() const;

    /**
     * Performs one step of Euler's method to calculate the new velocity and position of the planet.
     * The parameter time_step specifies the step size.
     */
    void updateVelocityAndPosition(double time_step);

private:
    vec2 position_;
    vec2 velocity_;
};

}  // namespace physicsvisuals
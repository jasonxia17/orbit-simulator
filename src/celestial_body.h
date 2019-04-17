#pragma once
#include "ofMain.h"

using glm::vec2;

namespace physicstools {

class Body {
public:
    /**
     * Parameters are hard-coded for now, will have legit constructor later.
     */
    Body() {
        position_.x = 2;
        velocity_.y = 1;
    }

    const vec2& getPosition() { return position_; }

    /**
     * Performs one step of Euler's method to calculate the new velocity and position of the planet
     * after a time interval dt.
     */
    void updateVelocityAndPosition(double dt);

private:
    vec2 position_;
    vec2 velocity_;
};

}  // namespace physicstools
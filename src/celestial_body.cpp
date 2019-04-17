#include "celestial_body.h"

namespace physicstools {

void Body::updateVelocityAndPosition(double dt) {
    const double GM = 6; // constant in gravitational equation
    vec2 acceleration = -GM / pow(glm::length(position_), 3) * position_;
    
    velocity_ += acceleration * dt;
    position_ += velocity_ * dt;
}

}  // namespace physicstools
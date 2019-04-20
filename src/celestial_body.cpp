#include "celestial_body.hpp"

namespace physicsvisuals {

const vec2& CelestialBody::getPosition() const {
    return position_;
}

void CelestialBody::updateVelocityAndPosition(double time_step) {
    const double kGravitationalParameter = 10; // the quantity GM

    vec2 acceleration = -kGravitationalParameter / pow(glm::length(position_), 3) * position_;
    // a = -GM / |r|^3 * r, where r is a vector

    velocity_ += acceleration * time_step;  // dv = a * dt
    position_ += velocity_ * time_step;     // dx = v * dt
}

}  // namespace physicsvisuals
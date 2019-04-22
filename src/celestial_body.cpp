#include "celestial_body.hpp"

namespace physicsvisuals {

CelestialBody::CelestialBody() {}

void CelestialBody::resetMotion(const vec2& initial_position, const vec2& initial_velocity) {
    position_log_.clear();
    position_ = initial_position;
    velocity_ = initial_velocity;
}

const vec2& CelestialBody::getPosition() const {
    return position_;
}

const vec2& CelestialBody::getVelocity() const {
    return velocity_;
}

const std::deque<vec2>& CelestialBody::getPositionLog() const {
    return position_log_;
}

void CelestialBody::updateVelocityAndPosition(double time_step) {
    vec2 acceleration = -kGravitationalParameter / pow(glm::length(position_), 3) * position_;
    // a = -GM / |r|^3 * r, where r is a vector

    velocity_ += acceleration * time_step;  // dv = a * dt
    position_ += velocity_ * time_step;     // dx = v * dt

    position_log_.push_front(position_);
    if (position_log_.size() > kMaxPositionsStored) {
        position_log_.pop_back();
    }
}

bool CelestialBody::crashedIntoStar() const {
    return glm::length(position_) < kStarRadius + kPlanetRadius;
}

}  // namespace physicsvisuals
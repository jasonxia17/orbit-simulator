#include "celestial_body.hpp"

namespace physicsvisuals {

CelestialBody::CelestialBody(const OrbitSimulator& simulator,
                             double mass, double radius,
                             const vec2& initial_position, const vec2& initial_velocity,
                             ofColor body_color, ofColor velocity_color)
    : mass_(mass),
      radius_(radius),
      body_color_(body_color),
      velocity_color_(velocity_color),
      simulator_(simulator) {
    vec2 param_bound(10, 10);
    initial_position_.set("Initial Position", initial_position, -param_bound, param_bound);
    initial_velocity_.set("Initial Velocity", initial_velocity, -param_bound, param_bound);
}

void CelestialBody::resetMotion() {
    position_log_.clear();
    position_ = initial_position_;
    velocity_ = initial_velocity_;
}

const vec2& CelestialBody::getPosition() const {
    return position_;
}

const vec2& CelestialBody::getVelocity() const {
    return velocity_;
}

void CelestialBody::updateVelocityAndPosition(double time_step, const std::vector<CelestialBody>& body_list) {
    vec2 net_acceleration = vec2(0, 0);

    for (const CelestialBody& other : body_list) {
        if (this == &other) {
            continue;
        }
        
        vec2 r_vec = position_ - other.position_;  // vector from other body to this body

        net_acceleration += -simulator_.kGravitationalConstant * other.mass_ /
                            pow(glm::length(r_vec), 3) * r_vec;
        // a = -GM / |r|^3 * r
    }

    velocity_ += net_acceleration * time_step;  // dv = a * dt
    position_ += velocity_ * time_step;         // dx = v * dt

    position_log_.push_front(position_);
    if (position_log_.size() > kMaxPositionsStored) {
        position_log_.pop_back();
    }
}

void CelestialBody::updateVelocityAndPosition(double time_step, const CelestialBody& star) {
    updateVelocityAndPosition(time_step, std::vector<CelestialBody>{star});
}

bool CelestialBody::crashedIntoAnotherBody(const CelestialBody& other) const {
    double distance_between_bodies = glm::length(position_ - other.position_);
    return distance_between_bodies < radius_ + other.radius_;
}

void CelestialBody::drawBody() const {
    ofSetColor(body_color_);
    ofDrawCircle(simulator_.getScreenCoordinates(position_),
                 radius_ * simulator_.getScaleFactor());
}

void CelestialBody::drawTrail() const {
    ofSetLineWidth(3);

    ofColor trail_color = body_color_;
    const double kMaxOpacity = 255;

    if (position_log_.empty()) {
        return;
        // otherwise size() - 1 = size_t(0) - 1 = huge number --> segfault
    }

    for (size_t i = 0; i < position_log_.size() - 1; ++i) {
        double opacity_fraction = 1 - (double)i / kMaxPositionsStored;
        trail_color.a = kMaxOpacity * opacity_fraction;
        // linearly decrease opacity of trail for less recent positions

        ofSetColor(trail_color);
        ofDrawLine(simulator_.getScreenCoordinates(position_log_[i]),
                   simulator_.getScreenCoordinates(position_log_[i + 1]));
    }
}

void CelestialBody::drawVelocityVector() const {
    ofSetLineWidth(4);
    ofSetColor(velocity_color_);

    // A velocity v will show up as a line with length kVectorScaleFactor * v
    const double kVectorScaleFactor = 0.35;
    vec2 vector_head = position_ + kVectorScaleFactor * velocity_;
    ofDrawLine(simulator_.getScreenCoordinates(position_),
               simulator_.getScreenCoordinates(vector_head));

    // Part 2: Draw triangular arrow at vector head

    std::vector<vec2> arrow_coordinates{vec2(0, -0.1), vec2(0, 0.1), vec2(0.2, 0)};
    // Currently, this is an arrow at the origin pointing directly to the right

    float arrow_angle = glm::orientedAngle(vec2(1, 0), glm::normalize(velocity_));
    // signed angle between velocity and positive-x axis, in the interval [-pi, pi]
    // vector parameters need to be normalized when using the orientedAngle function
    // arrow_angle must be a float instead of double to maintain consistent template types

    for (vec2& point : arrow_coordinates) {
        point = glm::rotate(point, arrow_angle);  // rotate arrow to be parallel to vector
        point += vector_head;                     // translate arrow to vector head
        point = simulator_.getScreenCoordinates(point);
    }

    ofDrawTriangle(arrow_coordinates[0], arrow_coordinates[1], arrow_coordinates[2]);
}

}  // namespace physicsvisuals
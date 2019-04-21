#pragma once

#include <deque>

#include "ofMain.h"

using glm::vec2;

namespace physicsvisuals {

class CelestialBody {
public:
    /**
     * Parameters are hard-coded for now, will have legit constructor later.
     */
    CelestialBody() {
        position_.x = 4;
        velocity_.y = 1;
    }

    const vec2& getPosition() const;
    const std::deque<vec2>& getPositionLog() const;

    /**
     * Performs one step of Euler's method to calculate the new velocity and position of the planet.
     * The parameter time_step specifies the step size.
     * 
     * Also updates position_log_.
     */
    void updateVelocityAndPosition(double time_step);

    static const size_t kMaxPositionsStored = 1000;

private:
    vec2 position_;
    vec2 velocity_;

    /**
     * Stores the past positions of the planet with the most recent
     * positions first, for the purpose of drawing a trail. The number of
     * positions stored is limited by kMaxPositionsStored; when this size is exceeded
     * the oldest positions will be discarded from the back of the list. This
     * prevents the class from storing too much unneeded information.
     * 
     */
    std::deque<vec2> position_log_;
};

}  // namespace physicsvisuals
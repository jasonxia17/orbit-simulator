#pragma once

#include <deque>

#include "ofMain.h"
#include "physical_constants.hpp"

using glm::vec2;

namespace physicsvisuals {

class OrbitSimulator;
// must be forward declared, since it's not defined until after this file is included.

class CelestialBody {
public:
    /**
     * Creates a celestial body with a reference to its simulator.
     */
    CelestialBody(const OrbitSimulator& simulator);

    /**
     * Sets position and velocity to values provided in parameters.
     * Also clears the trail of the planet.
     */
    void resetMotion(const vec2& initial_position, const vec2& initial_velocity);

    const vec2& getPosition() const;
    const vec2& getVelocity() const;

    /**
     * Performs one step of Euler's method to calculate the new velocity and position of the planet.
     * The parameter time_step specifies the step size.
     * 
     * Also updates position_log_.
     */
    void updateVelocityAndPosition(double time_step);

    /**
     * Returns true if planet is too close to star
     */
    bool crashedIntoStar() const;

    void drawBody() const;

    void drawTrail() const;

    void drawVelocityVector() const;

private:
    vec2 position_;
    vec2 velocity_;

    /**
     * Stores the past positions of the planet with the most recent
     * positions first, for the purpose of drawing a trail. The number of
     * positions stored is limited by kMaxPositionsStored; when this size is exceeded
     * the oldest positions will be discarded from the back of the list. This
     * prevents the class from storing too much unneeded information.
     */
    std::deque<vec2> position_log_;

    /**
     * Cap on size of position_log_
     */
    static const size_t kMaxPositionsStored = 1000;

    /**
     * Reference to parent simulator. Necessary for planet's drawing functions.
     */
    const OrbitSimulator& simulator_;
};

}  // namespace physicsvisuals

#include "ofApp.hpp" // contains definition of OrbitSimulator class
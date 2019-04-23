#pragma once

#include <deque>

#include "ofMain.h"

using glm::vec2;

namespace physicsvisuals {

class OrbitSimulator;
// must be forward declared, since it's not defined until after this file is included.

class CelestialBody {
public:
    /**
     * Creates a celestial body with a reference to its simulator.
     * Velocity color is set to the complement of body color.
     * Also sets the ofParameters for initial position and velocity.
     */
    CelestialBody(const OrbitSimulator& simulator,
                  double mass, double radius,
                  ofColor body_color, ofColor velocity_color,
                  vec2 initial_position = vec2(0, 0),
                  vec2 initial_velocity = vec2(0, 0));

    /**
     * Sets position and velocity to the initial values specified
     * by the ofParameters initial_position_ and initial_velocity_
     * (which are controlled by the GUI panel)
     * Also clears the trail of the planet.
     */
    void resetMotion();

    const vec2& getPosition() const;
    const vec2& getVelocity() const;

    /**
     * Performs one step of Euler's method to calculate
     * the new velocity and position of the planet, based on the force exerted by star.
     * The parameter time_step specifies the step size.
     * 
     * Also updates position_log_.
     */
    void updateVelocityAndPosition(double time_step, const CelestialBody& star);

    /**
     * Returns true if planet is too close to another body
     */
    bool crashedIntoAnotherBody(const CelestialBody& other) const;

    void drawBody() const;

    void drawTrail() const;

    void drawVelocityVector() const;

    const double mass_;
    const double radius_;
    const ofColor body_color_;
    const ofColor velocity_color_;

    // These initial parameters are public because the GUI panel in the OrbitSimulator
    // needs to access/modify them.

    ofParameter<vec2> initial_position_;
    ofParameter<vec2> initial_velocity_;

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

#include "orbit_simulator.hpp"  // contains definition of OrbitSimulator class
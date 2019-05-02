#pragma once

#include <deque>
#include <vector>

#include "ofMain.h"

using glm::vec2;

namespace physicsvisuals {

class OrbitSimulator;

class CelestialBody {
public:
    /**
     * Creates a celestial body
     * 
     * @param simulator: reference to body's simulator (needed for drawing)
     * @param mass: in kilograms, can be adjusted with GUI afterwards,
     *              also determines radius of body
     * @param initial_position: in meters, can be adjusted with GUI
     * @param initial_velocity: in meters/second, can be adjusted with GUI
     * @param body_color: the color used to draw the body and its trail
     * @param velocity_color: the color used to draw the velocity vector,
     *                        defaults to orange if unspecified
     */
    CelestialBody(const OrbitSimulator& simulator, double mass,
                  const vec2& initial_position, const vec2& initial_velocity,
                  ofColor body_color, ofColor velocity_color = ofColor::orange);

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
     * Calculates the radius of the planet, which is proportional to the
     * cube root of the mass.
     */
    double getRadius() const;

    /**
     * 1/2 mv^2, in Joules
     */
    double calculateKineticEnergy() const;

    /**
     * Gravitational potential energy with respect to the star.
     * This quantity is always negative, and it goes to 0 at infinity.
     */
    double calculatePotentialEnergy(const CelestialBody& star) const;

    /**
     * Performs one step of Euler's method to calculate
     * the new velocity and position of the planet, based on the force exerted by star.
     * The parameter time_step specifies the step size.
     * 
     * Also updates position_log_.
     */
    void updateVelocityAndPosition(double time_step, const CelestialBody& star);

    /**
     * Same as method above, except it will update based on the force exerted by all bodies
     * in the simulation, which is passed as body_list. If the vector contains this planet,
     * it will be skipped (planet can't exert an external force on itself).
     */
    void updateVelocityAndPosition(double time_step, const std::vector<CelestialBody>& body_list);

    /**
     * Returns true if planet is too close to another body
     */
    bool crashedIntoAnotherBody(const CelestialBody& other) const;

    void drawBody() const;

    void drawTrail() const;

    void drawVelocityVector() const;

    /**
     * See constructor for details about color variables.
     */
    const ofColor body_color_;

    const ofColor velocity_color_;

    /**
     * These parameters are controlled by the GUI panel in the simulator.
     * They must be public to allow the GUI panel to modify the parameters.
     */
    ofParameter<double> mass_;  // TODO: make this an ofParameter

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
#pragma once

#include <vector>

#include "celestial_body.hpp"
#include "ofMain.h"

using glm::vec2;

namespace physicsvisuals {

class OrbitSimulator : public ofBaseApp {
public:
    /**
     * Function used for one time setup. Sets the title and background of the app.
     */
    void setup();

    /**
     * If the simulation is RUNNING, this method executes one step of Euler on the planet
     * and increments the time counter. (Called on every frame.)
     */
    void update();

    /**
     * Draw the star, planet, and a trail behind the planet.
     * Also displays numerical information on the screen. (Called on every frame.)
     */
    void draw();

    /**
     * Responds to these keys: space (start simulation), p (pause/unpause), r (restart),
     * -/= (zoom in/out).
     */
    void keyPressed(int key);

private:
    /**
     * Displays numerical information about the orbit on the screen.
     */
    void drawNumericalInfo() const;

    /**
     * Draws a circle at the sun and planet's positions.
     */
    void drawSunAndPlanet() const;

    void drawPlanetTrail() const;

    void drawPlanetVelocityVector() const;

    /** 
     * Transforms Cartesian coordinates into canvas coordinates.
     * real_coordinates is passed by copy because it's modified by the method.
     */
    vec2 getScreenCoordinates(vec2 real_coordinates) const;

    CelestialBody planet_;

    double time_elapsed_ = 0;

    /**
     * If a planet's Cartesian coordinates change by x, its screen coordinates
     * will change by scale_factor_ * x.
     */
    double scale_factor_ = 100;
};
}  // namespace physicsvisuals

#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "celestial_body.hpp"  // definition of CelestialBody class
#include "ofMain.h"
#include "ofxGui.h"
#include "physical_constants.hpp"

using glm::vec2;

namespace physicsvisuals {

class OrbitSimulator : public ofBaseApp {
private:
    enum AppState {
        RUNNING,
        PAUSED,
        GETTING_USER_INPUT,
        PLANET_CRASHED,
        WELCOME_SCREEN,
    };

public:
    /**
     * Constructor that calls the constructor for Celestial Body.
     */
    OrbitSimulator();

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
     * Responds to these keys: space (start simulation), p (pause/unpause), r (reset),
     * -/= (zoom in/out).
     */
    void keyPressed(int key);

    /**
     * Getter for scale_factor_.
     * If a planet's Cartesian coordinates change by x, its screen coordinates
     * will change by scale_factor_ * x.
     */
    double getScaleFactor() const;

    /** 
     * Transforms Cartesian coordinates into canvas coordinates.
     * real_coordinates is passed by copy because it's modified by the method.
     */
    vec2 getScreenCoordinates(vec2 real_coordinates) const;

private:
    /**
     * Displays numerical information about the orbit on the screen.
     */
    void drawNumericalInfo() const;

    AppState current_state_ = WELCOME_SCREEN;

    CelestialBody planet_;

    /**
     * In this simulation, the star is stationary, so it shouldn't need to be modified.
     * This is a physical simplification, but the star movements should be negligible.
     */
    const CelestialBody star_;

    double time_elapsed_ = 0;

    /**
     * See getScaleFactor documentation
     */
    double scale_factor_ = 100;

    ofxPanel input_panel_;

    ofTrueTypeFont app_font_;
};
}  // namespace physicsvisuals
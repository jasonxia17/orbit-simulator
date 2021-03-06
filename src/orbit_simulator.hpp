#pragma once

#include <sstream>
#include <string>
#include <vector>

#include "celestial_body.hpp"  // definition of CelestialBody class
#include "ofMain.h"
#include "ofxGui.h"

using glm::vec2;

namespace physicsvisuals {

class OrbitSimulator : public ofBaseApp {
public:
    /**
     * Constructor that calls the constructor for Celestial Body.
     */
    OrbitSimulator();

    /**
     * Function used for one time setup. Sets the title and background of the app.
     */
    void setup() override;

    /**
     * If the simulation is RUNNING, this method executes one step of Euler on the planet
     * and increments the time counter. (Called on every frame.)
     */
    void update() override;

    /**
     * Draw the star, planet, and a trail behind the planet.
     * Also displays numerical information on the screen. (Called on every frame.)
     */
    void draw() override;

    /**
     * Responds to these keys: space (start simulation), p (pause/unpause), r (reset),
     * -/= (zoom in/out).
     */
    void keyPressed(int key) override;

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

    /**
     * Conventionally denoted by the letter G in physics. This is a fake value which
     * the simulator uses for convenience (to keep numbers small). Since the value
     * is a property of the simulation and not a true physical constant, it's stored
     * as a class instance variable instead of a global constant.
     * 
     * Measured in standard SI units (N*m^2/kg^2)
     */
    const double kGravitationalConstant = 1.0;

protected:
    enum AppState {
        GETTING_USER_INPUT,
        RUNNING,
        PAUSED,
        PLANET_CRASHED,
    };

    /**
     * Displays information about how to use the app.
     */
    void drawInstructions() const;

    /**
     * Displays a message if a crash occurs.
     */
    void drawCrashMessage() const;

    /**
     * Measured in seconds.
     */
    double time_elapsed_ = 0;

    AppState current_state_ = GETTING_USER_INPUT;

private:
    /**
     * Displays numerical information about the orbit on the screen.
     */
    void drawNumericalInfo() const;

    CelestialBody planet_;

    /**
     * In this simulation, the star is stationary.
     * This is a physical simplification, but the star movements should be negligible.
     * However, it must be non-const so that the user can change its mass.
     */
    CelestialBody star_;

    /**
     * See getScaleFactor documentation
     */
    double scale_factor_ = 100;

    /**
     * This is the Cartesian point which will appear at the center of the screen.
     */
    vec2 screen_center_;

    ofxPanel input_panel_;

    ofTrueTypeFont app_font_;
};
}  // namespace physicsvisuals
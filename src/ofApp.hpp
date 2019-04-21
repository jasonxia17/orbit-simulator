#pragma once

#include <vector>
#include <string>
#include <sstream>

#include "celestial_body.hpp"
#include "ofMain.h"
#include "ofxGui.h"

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

private:
    /**
     * Displays numerical information about the orbit on the screen.
     */
    void drawNumericalInfo() const;

    /**
     * Draws a circle at the star and planet's positions.
     */
    void drawStarAndPlanet() const;

    void drawPlanetTrail() const;

    void drawPlanetVelocityVector() const;

    /** 
     * Transforms Cartesian coordinates into canvas coordinates.
     * real_coordinates is passed by copy because it's modified by the method.
     */
    vec2 getScreenCoordinates(vec2 real_coordinates) const;

    AppState current_state_ = WELCOME_SCREEN;

    CelestialBody planet_;

    double time_elapsed_ = 0;

    /**
     * If a planet's Cartesian coordinates change by x, its screen coordinates
     * will change by scale_factor_ * x.
     */
    double scale_factor_ = 100;

    ofxPanel input_panel_;
    ofParameter<vec2> initial_position_;
    ofParameter<vec2> initial_velocity_;

    ofTrueTypeFont app_font_;
};
}  // namespace physicsvisuals

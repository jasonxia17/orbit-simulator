#include "orbit_simulator.hpp"

namespace {  // anonymous namespace with rounding helper methods

// this function was taken from
// https://stackoverflow.com/questions/1343890/rounding-number-to-2-decimal-places-in-c

string toRoundedString(const double val) {
    stringstream ss;
    ss << fixed;      // fixed point instead of floating
    ss.precision(2);  // set # places after decimal
    ss << val;
    return ss.str();
}

string toRoundedString(const vec2& val) {
    return "(" + toRoundedString(val.x) + ", " + toRoundedString(val.y) + ")";
}

}  // end anonymous namespace

namespace physicsvisuals {

OrbitSimulator::OrbitSimulator()
    : planet_(*this, 1, 0.15, ofColor::blue, ofColor::orange, vec2(4, 0), vec2(0, 1)),
      star_(*this, 1, 0.35, ofColor::yellow, ofColor::yellow) {}

void OrbitSimulator::setup() {
    ofSetWindowTitle("Going in Circles");
    ofBackground(ofColor::black);

    ofTrueTypeFontSettings font_settings("../fonts/Liberation-Mono-Regular.ttf", 16);
    app_font_.load(font_settings);

    input_panel_.setup();
    input_panel_.add(planet_.initial_position_);
    input_panel_.add(planet_.initial_velocity_);
}

void OrbitSimulator::update() {
    if (current_state_ == GETTING_USER_INPUT) {
        planet_.resetMotion();
        // must be called on every frame to ensure that planet responds to
        // initial parameters set in GUI
    }

    if (current_state_ == RUNNING) {
        if (planet_.crashedIntoAnotherBody(star_)) {
            current_state_ = PLANET_CRASHED;
            return;
        }

        const double kTimeStep = 0.01;
        planet_.updateVelocityAndPosition(kTimeStep);
        time_elapsed_ += kTimeStep;
    }
}

void OrbitSimulator::draw() {
    if (current_state_ == WELCOME_SCREEN) {
        // TODO: display welcome message
        return;
    }

    star_.drawBody();
    planet_.drawTrail();
    planet_.drawVelocityVector();
    planet_.drawBody();

    if (current_state_ == GETTING_USER_INPUT) {
        input_panel_.draw();
    }

    if (current_state_ == RUNNING || current_state_ == PAUSED) {
        drawNumericalInfo();
    }

    if (current_state_ == PLANET_CRASHED) {
        ofSetColor(ofColor::white);
        app_font_.drawString("The planet crashed :(\nPress r to reset", 50, 50);
    }
}

void OrbitSimulator::drawNumericalInfo() const {
    float left_margin = 30;
    float vertical_spacing = 45;  // space between consecutive lines of test

    ofSetColor(ofColor::white);
    app_font_.drawString("Time Elapsed (s): " + toRoundedString(time_elapsed_),
                         left_margin, 1 * vertical_spacing);

    ofSetColor(planet_.body_color_);
    app_font_.drawString("Position (m): " + toRoundedString(planet_.getPosition()),
                         left_margin, 2 * vertical_spacing);

    ofSetColor(planet_.velocity_color_);
    app_font_.drawString("Velocity (m/s): " + toRoundedString(planet_.getVelocity()),
                         left_margin, 3 * vertical_spacing);
}

void OrbitSimulator::keyPressed(int key) {
    // Welcome screen only responds to the space bar
    if (current_state_ == WELCOME_SCREEN) {
        if (key == ' ') {
            current_state_ = GETTING_USER_INPUT;
        }
        return;
    }

    const double kZoomFactor = 1.03;  // amount of zoom per key press

    if (key == '-') {  // zooming out
        scale_factor_ /= kZoomFactor;
    } else if (key == '=') {  // zooming in
        scale_factor_ *= kZoomFactor;

    } else if (key == ' ') {  // starting simulation
        if (current_state_ == GETTING_USER_INPUT) {
            current_state_ = RUNNING;
        }

    } else if (key == 'p') {  // pausing and unpausing
        if (current_state_ == RUNNING) {
            current_state_ = PAUSED;
        } else if (current_state_ == PAUSED) {
            current_state_ = RUNNING;
        }

    } else if (key == 'r') {  // resetting the simulation
        time_elapsed_ = 0;
        current_state_ = GETTING_USER_INPUT;
    }
}

double OrbitSimulator::getScaleFactor() const {
    return scale_factor_;
}

vec2 OrbitSimulator::getScreenCoordinates(vec2 real_coordinates) const {
    vec2 center(ofGetWindowWidth(), ofGetWindowHeight());
    center /= 2;

    real_coordinates.y *= -1;  // canvas y-coordinates are the reverse of Cartesian y-coordinates

    return scale_factor_ * real_coordinates + center;
}

}  // namespace physicsvisuals
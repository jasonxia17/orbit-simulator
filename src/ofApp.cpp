#include "ofApp.hpp"

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
    : planet_(*this) {}

void OrbitSimulator::setup() {
    ofSetWindowTitle("Going in Circles");
    ofBackground(ofColor::black);

    ofTrueTypeFontSettings font_settings("../fonts/Liberation-Mono-Regular.ttf", 16);
    app_font_.load(font_settings);

    vec2 default_val(2, 2);
    vec2 input_bound(10, 10);

    input_panel_.setup();
    input_panel_.add(initial_position_.set("Initial Position", default_val, -input_bound, input_bound));
    input_panel_.add(initial_velocity_.set("Initial Velocity", default_val, -input_bound, input_bound));
}

void OrbitSimulator::update() {
    if (current_state_ == GETTING_USER_INPUT) {
        // reset planet based on provided parameters
        planet_.resetMotion(initial_position_, initial_velocity_);
    }

    if (current_state_ == RUNNING) {
        if (planet_.crashedIntoStar()) {
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

    planet_.drawTrail();
    planet_.drawVelocityVector();
    planet_.drawBody();

    // draws the Star
    ofSetColor(ofColor::yellow);
    ofDrawCircle(getScreenCoordinates(vec2(0, 0)), kStarRadius * scale_factor_);

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

    ofSetColor(ofColor::blue);
    app_font_.drawString("Position (m): " + toRoundedString(planet_.getPosition()),
                         left_margin, 2 * vertical_spacing);

    ofSetColor(ofColor::orange);
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
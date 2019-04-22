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

    drawPlanetTrail();
    drawPlanetVelocityVector();
    drawStarAndPlanet();

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

void OrbitSimulator::drawStarAndPlanet() const {
    const vec2 origin;

    // draws the Star
    ofSetColor(ofColor::yellow);
    ofDrawCircle(getScreenCoordinates(origin), kStarRadius * scale_factor_);

    // draws the orbiting planet
    ofSetColor(ofColor::blue);
    ofDrawCircle(getScreenCoordinates(planet_.getPosition()), kPlanetRadius * scale_factor_);
}

void OrbitSimulator::drawPlanetTrail() const {
    ofSetLineWidth(3);

    auto trail = planet_.getPositionLog();

    ofColor trail_color = ofColor::blue;
    const double kMaxOpacity = 255;

    if (trail.empty()) {
        return;
        // otherwise trail.size() - 1 = size_t(0) - 1 = huge number --> segfault
    }

    for (size_t i = 0; i < trail.size() - 1; ++i) {
        double opacity_fraction = 1 - (double)i / CelestialBody::kMaxPositionsStored;
        trail_color.a = kMaxOpacity * opacity_fraction;
        // linearly decrease opacity of trail for less recent positions

        ofSetColor(trail_color);
        ofDrawLine(getScreenCoordinates(trail[i]), getScreenCoordinates(trail[i + 1]));
    }
}

void OrbitSimulator::drawPlanetVelocityVector() const {
    ofSetLineWidth(4);
    ofSetColor(ofColor::orange);

    // A velocity v will show up as a line with length kVectorScaleFactor * v
    const double kVectorScaleFactor = 0.35;
    vec2 vector_head = planet_.getPosition() + kVectorScaleFactor * planet_.getVelocity();
    ofDrawLine(getScreenCoordinates(planet_.getPosition()), getScreenCoordinates(vector_head));

    // Part 2: Draw triangular arrow at vector head

    std::vector<vec2> arrow_coordinates{vec2(0, -0.1), vec2(0, 0.1), vec2(0.2, 0)};
    // Currently, this is an arrow at the origin pointing directly to the right

    float arrow_angle = glm::orientedAngle(vec2(1, 0), glm::normalize(planet_.getVelocity()));
    // signed angle between velocity and positive-x axis, in the interval [-pi, pi]
    // vector parameters need to be normalized when using the orientedAngle function
    // arrow_angle must be a float instead of double to maintain consistent template types

    for (vec2& point : arrow_coordinates) {
        point = glm::rotate(point, arrow_angle);  // rotate arrow to be parallel to vector
        point += vector_head;                     // translate arrow to vector head
        point = getScreenCoordinates(point);
    }

    ofDrawTriangle(arrow_coordinates[0], arrow_coordinates[1], arrow_coordinates[2]);
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

vec2 OrbitSimulator::getScreenCoordinates(vec2 real_coordinates) const {
    vec2 center(ofGetWindowWidth(), ofGetWindowHeight());
    center /= 2;

    real_coordinates.y *= -1;  // canvas y-coordinates are the reverse of Cartesian y-coordinates

    return scale_factor_ * real_coordinates + center;
}

}  // namespace physicsvisuals
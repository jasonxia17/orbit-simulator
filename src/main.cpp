#include "orbit_simulator.hpp"
#include "ofMain.h"

#define DISPLAY_MODE OF_WINDOW  // Can be OF_WINDOW or OF_FULLSCREEN

int main() {
    ofSetupOpenGL(1200, 900, DISPLAY_MODE);  // setup the GL context
    ofSetFrameRate(100);

    // this kicks off the running of my app
    ofRunApp(new physicsvisuals::OrbitSimulator());
}

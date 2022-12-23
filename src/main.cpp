#include <random>
#include "Simulator.hpp"
#include "Constants.hpp"

//========================================================================
int main( ){
	ofSetupOpenGL(VRWX, HUWY, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:

	CollisionSystem *sys = new CollisionSystem();

	sys->fps = 60.;
    sys->dts = 1/sys->fps;
    ofSetFrameRate(sys->fps);
    ofBackground(20, 20, 20);

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> Rx(100., 800.);
    std::uniform_real_distribution<> Ry(100., 800.);
    std::uniform_real_distribution<> V(-300., 300.);
    std::uniform_real_distribution<> R(5., 10.);
    double rho = 1;

    sys->N = 250;

    Particle p;
    double rad;
    double M;
    for (int n=0; n<sys->N; n++){
        rad = R(gen);
        M = 4*M_PI*rad*rad*rad*rho/3;
        p = Particle(Rx(gen), Ry(gen), V(gen), V(gen), rad, M);
        sys->particles.push_back(p);
    }

	sys->N+=1;
	p = Particle(500., 500., 5., 5., 50., 4*M_PI*50*50*50*0.1/3, 50, 255, 255);
	sys->particles.push_back(p);

	ofRunApp(sys);
}

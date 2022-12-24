#ifndef SIMULATORHEADERDEF
#define SIMULATORHEADERDEF

#include <sstream>
#include "Particle.hpp"
#include "PriorityQueue.hpp"
#include "ofMain.h"


class Event{

    private:
        double time;                        // Event time
        Particle* a;                   
        Particle* b;
        int counta, countb;                 // To store collisions when event was initialised
        friend class CollisionSystem;       // Has access to the private attributes

    public:
        Event();
        Event(const Event &rhs);
        Event(double t, Particle* a_, Particle* b_);
        bool operator <(const Event &rhs);
        bool operator ==(const Event &rhs);
        bool operator >(const Event &rhs);
        bool isValid();

};


class CollisionSystem: public ofBaseApp{

    public:
        int N;                              // Number of Particles
        MaxPQ<Event> pq;                    // Event Priority Queue
        std::vector<Particle> particles;    // Vector of Particles

        double fps;                         // Simulation FPS
        double t;                           // Running time
        double tend;                        // End time
        double dts;                         // Delta time

        CollisionSystem();
        void predict(Particle* a);
        void execute(Event &e);
        void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};

#endif
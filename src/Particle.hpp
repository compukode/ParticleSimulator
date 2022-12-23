#ifndef PARTICLEHEADERDEF
#define PARTICLEHEADERDEF

#include <iostream>
#include <cmath>
#include "Constants.hpp"


class Particle{

    private:
        double rx, ry;
        double vx, vy;
        double rad;
        double mass;
        int r, g, b;
        friend class CollisionSystem;

    public:

        Particle();

        Particle(double rx, double ry, double vx, double vy,
                 double rad, double mass);
        
        Particle(double rx, double ry, double vx, double vy,
                 double rad, double mass, int red, int green, int blue);

        Particle(const Particle &old);

        int count;

        void move(double dt);
        void print();

        double timeToHit(Particle &that);
        double timeToHitVWall();
        double timeToHitHWall();

        void bounceParticle(Particle &that, double dt);
        void bounceVWall();
        void bounceHWall();
};

#endif
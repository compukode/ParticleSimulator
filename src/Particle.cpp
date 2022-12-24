#include "Particle.hpp"


Particle::Particle(){
    rx = 0.0;
    ry = 0.0;
    vx = 0.0;
    vy = 0.0;
    rad = 0.0;
    mass = 0.0;
    count = 0;
    r = 255;
    g = 255;
    b = 255;
}


Particle::Particle(double r_x, double r_y, double v_x, double v_y,
                   double rad_, double mass_){

    rx = r_x;
    ry = r_y;
    vx = v_x;
    vy = v_y;
    rad = rad_;
    mass = mass_;
    count = 0;
    r = 255;
    g = 255;
    b = 255;

}


Particle::Particle(double r_x, double r_y, double v_x, double v_y,
                   double rad_, double mass_, int red, int green, int blue){

    rx = r_x;
    ry = r_y;
    vx = v_x;
    vy = v_y;
    rad = rad_;
    mass = mass_;
    count = 0;
    r = red;
    g = green;
    b = blue;

}


Particle::Particle(const Particle &old){
    
    rx = old.rx;
    ry = old.ry;
    vx = old.vx;
    vy = old.vy;
    rad = old.rad;
    mass = old.mass;
    count = old.count;
    r = old.r;
    g = old.g;
    b = old.b;

}

void Particle::move(double dt){
    rx = rx + vx*dt;
    ry = ry + vy*dt;
}


void Particle::print(){
    std::cout << "Rad: " << rad << " Mass: " << mass << std::endl;
    std::cout << "Pos: " << rx << " " << ry << std::endl;
    std::cout << "Vel: " << vx << " " << vy << std::endl;
}


double Particle::timeToHit(Particle &that){

    if (this == &that){
        return INF;
    }

    double sig = rad + that.rad;
    double drx = rx - that.rx;
    double dry = ry - that.ry;
    double dvx = vx - that.vx;
    double dvy = vy - that.vy;

    double dvdr = dvx*drx + dvy*dry;
    if (dvdr >= 0.0){
        return INF;
    }

    double dvdv = dvx*dvx + dvy*dvy;
    double drdr = drx*drx + dry*dry;
    double d = dvdr*dvdr - dvdv*(drdr - sig*sig);

    if (d < 0){
        return INF;
    }

    double sqrtd = sqrt(d);

    double dt = -(dvdr + sqrtd)/dvdv;
    if (dt < 0.0){
        dt = INF;
    }

    return dt;

}


void Particle::bounceParticle(Particle &that, double dt){

    double drx, dry;
    double dvx, dvy;
    double dvdr;
    double sig;
    double J, Jx, Jy;
    
    drx = that.rx - rx; dry = that.ry - ry;
    dvx = that.vx - vx; dvy = that.vy - vy;
    sig = that.rad + rad;
    dvdr = drx*dvx + dry*dvy;

    J = 2*mass*that.mass*dvdr/((mass+that.mass)*sig);
    Jx = J*drx/sig;
    Jy = J*dry/sig;

    vx += Jx/mass;
    vy += Jy/mass;
    that.vx -= Jx/that.mass;
    that.vy -= Jy/that.mass;

    count += 1;
    that.count += 1;

    // std::cout << "Particle Collision" << std::endl;
}


double Particle::timeToHitHWall(){
    if (vy > 0){
        return (HUWY - ry - rad)/vy;
    }
    else if (vy < 0){
        return (HDWY - ry + rad)/vy;
    }
    else{
        return INF;
    }
}


void Particle::bounceHWall(){
    vy = -vy;
    count += 1;
    // std::cout << "Bounce H wall" << std::endl;
}


double Particle::timeToHitVWall(){
    if (vx > 0){
        return (VRWX - rx - rad)/vx;
    }
    else if (vx < 0){
        return (VLWX - rx + rad)/vx;
    }
    else{
        return INF;
    }
}


void Particle::bounceVWall(){
    vx = -vx;
    count += 1;
    // std::cout << "Bounce V Wall" << std::endl;
}
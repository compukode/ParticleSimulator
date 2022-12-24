#include "Simulator.hpp"
#include <cstdlib>


Event::Event(){
    time = INF;
    a = nullptr;
    b = nullptr;
    counta = 0;
    countb = 0;
}


Event::Event(const Event &rhs){
    time = rhs.time;
    a = rhs.a;
    b = rhs.b;
    counta = rhs.counta;
    countb = rhs.countb;
}


Event::Event(double t, Particle* a_, Particle* b_){
    
    if ((a_!=nullptr) && (b_!=nullptr)){
        time = t;
        a = a_;
        b = b_;
        counta = a_->count;
        countb = b_->count;
    }
    else if ((a_==nullptr) && (b_!=nullptr)){
        time = t;
        a = a_;
        b = b_;
        counta = 0;
        countb = b_->count;
    }
    else if ((a_!=nullptr) && (b_==nullptr)){
        time = t;
        a = a_;
        b = b_;
        counta = a_->count;
        countb = 0;
    }
    else {
        time = t;
        a = a_;
        b = b_;
        counta = 0;
        countb = 0;
    }
}


bool Event::operator <(const Event &rhs){
    if (time > rhs.time){
        return true;
    }
    else{
        return false;
    }
}


bool Event::operator >(const Event &rhs){
    if (time > rhs.time){
        return false;
    }
    else{
        return true;
    }
}


bool Event::operator ==(const Event &rhs){
    if (time == rhs.time){
        return true;
    }
    else{
        return false;
    }
}


bool Event::isValid(){
    if (a == nullptr && b == nullptr){
        return true;
    }
    else if (a == nullptr){
        if (countb == b->count){
            return true;
        }
        else{
            return false;
        }
    }
    else if (b == nullptr){
        if (counta == a->count){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if ((counta == a->count) && (countb == b->count)){
            return true;
        }
        else{
            return false;
        }
    } 
}


CollisionSystem::CollisionSystem(){
    fps = 60;
    N = 0;
    t = 0.0;
    tend = 0.0;
    dts = 1/fps;
    pq = MaxPQ<Event>();
}


void CollisionSystem::setup(){

    for (int i=0; i<N; i++){
        predict(&particles[i]);
    }

    Event st(t, nullptr, nullptr);
    pq.insert(st);
}


void CollisionSystem::predict(Particle* a){

    double dt;
    Particle *b;

    if (a == nullptr){
        return;
    }
    
    for (int i=0; i<N; i++){
        dt = a->timeToHit(particles[i]);
        b = &particles[i];
        Event evp(t+dt, a, b);
        pq.insert(evp);
    }

    dt = a->timeToHitHWall();
    Event evhw(t+dt, a, nullptr);
    pq.insert(evhw);

    dt = a->timeToHitVWall();
    Event evvw(t+dt, nullptr, a);
    pq.insert(evvw);

}


void CollisionSystem::execute(Event &e){

    for (int i=0; i<N; i++){
        particles[i].move(e.time - t);
    }

    if (e.a != nullptr && e.b != nullptr){
        e.a->bounceParticle(*e.b, e.time-t);
    }
    else if (e.a == nullptr && e.b != nullptr){
        e.b->bounceVWall();
    }
    else if (e.a != nullptr && e.b == nullptr){
        e.a->bounceHWall();
    }

    t = e.time;
        
    predict(e.a);
    predict(e.b); 
}


void CollisionSystem::update(){

    double rtime = t;
    // std::cout << "Running Time: " << rtime << " Next Event: " << pq.getMax().time << std::endl;
    // std::stringstream strm;
	// strm << "Time: " << rtime << " Fps: " << ofGetFrameRate();
	// ofSetWindowTitle(strm.str());

    ofSetWindowTitle("ParticleSimulator");

    Event ev;
    Event inv;

    while (pq.getMax().time - rtime < dts){
        if (pq.getMax().isValid()){
            ev = pq.delMax();
            execute(ev);
        }
        else{
            inv = pq.delMax();
        }
    }

    pq.insert(Event(rtime+dts, nullptr, nullptr));
        
}


void CollisionSystem::draw(){
    ofSetColor(0, 0, 0);
    for (int i=0; i<N; i++){
        ofSetColor(particles[i].r, particles[i].g, particles[i].b);
        ofDrawCircle(particles[i].rx, particles[i].ry, particles[i].rad);
    }
    ofSetColor(0, 0, 0);
}

//-------------------------------------------------------------------------//

//--------------------------------------------------------------
void CollisionSystem::keyPressed(int key){

}

//--------------------------------------------------------------
void CollisionSystem::keyReleased(int key){

}

//--------------------------------------------------------------
void CollisionSystem::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void CollisionSystem::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void CollisionSystem::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void CollisionSystem::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void CollisionSystem::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void CollisionSystem::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void CollisionSystem::windowResized(int w, int h){

}

//--------------------------------------------------------------
void CollisionSystem::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void CollisionSystem::dragEvent(ofDragInfo dragInfo){ 

}
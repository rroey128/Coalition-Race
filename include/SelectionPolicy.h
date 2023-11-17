#pragma once
#include "vector"
using namespace std;

class Simulation;
class Party;
class Agent;

class SelectionPolicy {
    public:
virtual Party* select(vector<Party*> partys,Simulation &sim, Agent *Agent) = 0;
virtual SelectionPolicy* clone()  = 0;
virtual ~SelectionPolicy() = default;
 };

class MandatesSelectionPolicy: public SelectionPolicy{
    public:
     Party* select(vector<Party*> partys,Simulation &sim, Agent *Agent);
     virtual MandatesSelectionPolicy* clone();
 };

class EdgeWeightSelectionPolicy: public SelectionPolicy{ 
    public:
     Party* select(vector<Party*> partys,Simulation &sim, Agent *Agent);
     virtual EdgeWeightSelectionPolicy* clone();
};
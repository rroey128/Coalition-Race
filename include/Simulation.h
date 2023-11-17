#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;

class Simulation
{
private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition *> mCoalitions;

public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    Graph &getGraph2();
    const vector<Agent> &getAgents() const;
    vector<Agent> &getAgents2();
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
};

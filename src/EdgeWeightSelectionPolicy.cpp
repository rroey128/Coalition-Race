#include "SelectionPolicy.h"
#include <vector>
#include "Simulation.h"
using std::vector;
class Simulation;
class Party;


EdgeWeightSelectionPolicy *EdgeWeightSelectionPolicy::clone()
{
    return new EdgeWeightSelectionPolicy(*this);
}

Party *EdgeWeightSelectionPolicy::select(vector<Party *> partys, Simulation &sim, Agent *Agent)
{
    int MaxtWeight = sim.getGraph2().getEdgeWeight(Agent->getPartyId(), partys[0]->getPartyID());
    Party *Best = partys[0];
    for (unsigned int i = 1; i < partys.size(); i++)
    {
        int currSum = sim.getGraph2().getEdgeWeight(Agent->getPartyId(), partys[i]->getPartyID());
        if (currSum > MaxtWeight)
        {
            Best = partys[i];
            MaxtWeight = currSum;
        }
    }

    return Best;
}

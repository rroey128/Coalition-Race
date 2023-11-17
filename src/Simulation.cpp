#include "Simulation.h"
#include "Coalition.h"
class Coalition;
Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), mCoalitions()
{

    for (unsigned int i = 0; i < mAgents.size(); i++)
    {
        mCoalitions.push_back(new Coalition(mGraph.getParty2(mAgents[i].getPartyId()), mAgents[i].getId())); // should be in heap ?
        mAgents[i].setCoalition(mCoalitions.back());                                                         // DELETE !!!!coalitions from heap afterwards!!!! DO NOT FORGET !!!!
        mAgents[i].setCoalitionID(mCoalitions.back()->getCoalitionID());
    }
}

void Simulation::step()
{

    for (int i = 0; i < mGraph.getNumVertices(); i++)
    {
        if (((mGraph.getParty(i)).getState()) != Joined)
            ((mGraph.getParty2(i)))->step(*this);
    }
    for (unsigned int i = 0; i < mAgents.size(); i++)
    {
        mAgents[i].step(*this);
    }
}

bool Simulation::shouldTerminate() const
{
    bool shouldTer = false;
    const Graph graph = getGraph();
    // check if there is 61 coalition
    for (unsigned int i = 0; i < mCoalitions.size() && shouldTer == false; i++)
    {
        if (mCoalitions[i]->getMandates() >= 61)
            shouldTer = true;
    }

    // check if all partys are joined
    if (shouldTer == false)
    {
        int NumberOfjoinedPartys = 0;
        for (int i = 0; i < graph.getNumVertices(); i++)
        {
            if (graph.getParty(i).getState() == Joined)
                NumberOfjoinedPartys++;
        }
        if (NumberOfjoinedPartys == graph.getNumVertices())
            shouldTer = true;
    }

    return shouldTer;
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::getGraph2()
{

    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

vector<Agent> &Simulation::getAgents2()
{
    return mAgents;
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> output;
    for (unsigned int i = 0; i < mCoalitions.size(); i++)
    {
        vector<int> partysID;
        for (unsigned int j = 0; j < mCoalitions[i]->getPartys().size(); j++)
        {
            partysID.push_back(mCoalitions[i]->getPartys()[j]->getPartyID());
        }
        output.push_back(partysID);
    }
    return output;
}

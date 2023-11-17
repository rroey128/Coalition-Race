#include "Agent.h"
#include "Simulation.h"
#include "Coalition.h"
#include "SelectionPolicy.h"
class SelectionPolicy;
class Simulation;

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy),
                                                                           myCoalition(nullptr), CoalitionID()
{

}

// copy constructor
Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone()), myCoalition(other.myCoalition),
                                   CoalitionID(other.CoalitionID)
{

    if (this->myCoalition)
        this->myCoalition->refc++;
}
Agent &Agent::operator=(const Agent &other) //  assignment operator
{
    if (this != &other)
    {
        this->mAgentId = other.mAgentId;
        this->mPartyId = other.mPartyId;
        (*(this->mSelectionPolicy)) = *(other.mSelectionPolicy);
        this->myCoalition = other.myCoalition;
        this->CoalitionID = other.CoalitionID;

        if (myCoalition)
        {
            this->myCoalition->refc++;
        }
    }
    return *this;
}
Agent &Agent::operator=(Agent &&other) // move assignment operator
{
    if (mSelectionPolicy)
        delete mSelectionPolicy;
    if (myCoalition)
        delete myCoalition;

    this->mAgentId = other.mAgentId;
    this->mPartyId = other.mPartyId;
    this->mSelectionPolicy = other.mSelectionPolicy;
    myCoalition = other.myCoalition;
    this->CoalitionID = other.CoalitionID;

    other.mSelectionPolicy = nullptr;
    other.myCoalition = nullptr;

    return *this;
}

Agent::Agent(Agent &&other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), myCoalition(other.myCoalition), CoalitionID(other.CoalitionID)

{ // move constructor

    other.mSelectionPolicy = nullptr;
    other.myCoalition = nullptr;
}

Agent::~Agent()
{
    if (mSelectionPolicy)
        delete mSelectionPolicy;

    if (this->myCoalition)
    {
        this->myCoalition->refc--;

        if (this->myCoalition->refc == 0)
            delete this->myCoalition;
    }
};

void Agent::setCoalitionID(int ID)
{
    this->CoalitionID = ID;
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

int Agent::getCoalitionID()
{
    return this->myCoalition->getCoalitionID();
}

Coalition *Agent::getCoalition()
{
    return this->myCoalition;
}

vector<int> Agent::FilterOffers(Simulation &sim)
{
    Graph graph = sim.getGraph();
    vector<int> neighbors = graph.getNeighbors(this->getPartyId());

    vector<int> Output;
    for (int x : neighbors)
    {
        bool oK = true;
        Party *currParty = graph.getParty2(x);
        if (currParty->getState() != Joined)
        {
            vector<int> offers = currParty->getOffers();
            for (unsigned int i = 0; i < offers.size() && oK == true; i++)
            {
                if (sim.getAgents2()[offers[i]].getCoalitionID() == this->getCoalitionID())
                {
                    oK = false;
                }
            }
            if (oK == true)
                Output.push_back(x);
        }
    }
    return Output;
}

void Agent::step(Simulation &sim)
{
    vector<int> filteredOffers = FilterOffers(sim);
    vector<Party *> filteredPartys;

    if (filteredOffers.size() != 0)
    {
        for (unsigned int i = 0; i < filteredOffers.size(); i++)
            filteredPartys.push_back(sim.getGraph2().getParty2(filteredOffers[i]));

        Party *toJoin = mSelectionPolicy->select(filteredPartys, sim, this);
        const int PARTYIDCHECK = this->getId();
        toJoin->addOffer(PARTYIDCHECK);
        if (toJoin->getState() == Waiting)
        {
            toJoin->setState(CollectingOffers);
        }
    }
}

void Agent::setCoalition(Coalition *coalition)
{
    this->myCoalition = coalition;
}

void Agent::SetPartyID(int other)
{
    mPartyId = other;
}
void Agent::SetID(int other)
{
    mAgentId = other;
}

#pragma once

#include <vector>
#include "Graph.h"

class SelectionPolicy;
class Coalition;
class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(const Agent &agent);
    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    void setCoalition(Coalition *coalition);
    vector<int> FilterOffers(Simulation &sim);
    int getCoalitionID();
    Coalition *getCoalition();
    void SetPartyID(int other);
    void SetID(int other);
    virtual ~Agent();
    Agent& operator=(const Agent &other);
    void setCoalitionID(int ID);
    Agent (Agent&& other);
    Agent& operator=( Agent&& other);


private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    Coalition *myCoalition;
    int CoalitionID;   
};

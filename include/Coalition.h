#pragma once
#include <vector>
class Party;
class Agent;
using std::vector;
#include "Graph.h"


class Coalition
{
public :
    Coalition(Party *party, int ID);
    int getMandates();
    vector<Party*> getPartys();
    void addParty(Party *party); //update mandates number
    int getCoalitionID();


private :
    friend class Agent;
    friend class Party;
    int Mandates;
    int CoalitionID;
    vector<Party*> partys;
    unsigned int refc;
};

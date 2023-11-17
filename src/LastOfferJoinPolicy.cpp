#include "JoinPolicy.h"
#include <vector>
#include "Simulation.h"
#include "Coalition.h"

class Simulation;
class Party;
using std::vector;

int LastOfferJoinPolicy::join(Simulation &sim, Party *me)
{
    vector<int> MyOption = me->getOffers();

    int bestOfferAgentID = MyOption.back();
    sim.getAgents2()[bestOfferAgentID].getCoalition()->addParty(me);

    return bestOfferAgentID;
}

LastOfferJoinPolicy *LastOfferJoinPolicy::clone()
{
    return new LastOfferJoinPolicy(*this);
}

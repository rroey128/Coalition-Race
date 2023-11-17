#include "JoinPolicy.h"
#include <vector>
#include "Simulation.h"
#include "Coalition.h"

class Simulation;
class Party;
using std::vector;

int MandatesJoinPolicy::join(Simulation &sim, Party *me)
{

  vector<int> MyOption = me->getOffers();

  Coalition *best = sim.getAgents2()[MyOption[0]].getCoalition();
  int bestOfferAgentID = 0;
  for (int ID : MyOption)
  {
    Coalition *Temp = sim.getAgents2()[ID].getCoalition();

    if (Temp->getMandates() > best->getMandates())
    {
      best = Temp;
      bestOfferAgentID = ID;
    }
  }
  best->addParty(me);

  return bestOfferAgentID;
}

MandatesJoinPolicy *MandatesJoinPolicy::clone()
{
  return new MandatesJoinPolicy(*this);
}
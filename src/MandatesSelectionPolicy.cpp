#include "SelectionPolicy.h"
#include <vector>
#include "Simulation.h"

using namespace std;
class Simulation;
class Party;
using std::vector;

MandatesSelectionPolicy *MandatesSelectionPolicy::clone()
{

    return new MandatesSelectionPolicy(*this);
}

Party *MandatesSelectionPolicy::select(vector<Party *> partys, Simulation &sim, Agent *Agent)
{
    Party *best = partys[0];

    for (unsigned int i = 1; i < partys.size(); i++)
    {

        if (partys[i]->getMandates() > best->getMandates())
            best = partys[i];
    }

    return best;
}
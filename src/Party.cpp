#include "Party.h"
#include <vector>
class JoinPolicy;
#include "JoinPolicy.h"
#include "Simulation.h"
#include "Coalition.h"

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),
                                                                  Timer(0), offers()
{
}
// copy constructor
Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy->clone()),
                                   mState(other.mState), Timer(other.Timer), offers(other.offers)
{
}

Party &Party::operator=(const Party &other) //  assignment operator
{
    if (this != &other)
    {
        this->mId = other.mId;
        this->mName = other.mName;
        this->mMandates = other.mMandates;
        (*(this->mJoinPolicy)) = *(other.mJoinPolicy);
        this->mState = other.mState;
        this->Timer = other.Timer;
        this->offers = other.offers;
    }
    return *this;
}

Party &Party::operator=(Party &&other) // move assignment operator
{
    if (mJoinPolicy)
        delete mJoinPolicy;
    this->mId = other.mId;
    this->mName = other.mName;
    this->mMandates = other.mMandates;
    mJoinPolicy = other.mJoinPolicy;
    this->mState = other.mState;
    this->Timer = other.Timer;
    this->offers = other.offers;

    return *this;
}
// move constructor
Party::Party(Party &&other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), Timer(other.Timer), offers(other.offers)
{

    other.mJoinPolicy = nullptr;
}
Party::~Party()
{

    if (mJoinPolicy)
        delete mJoinPolicy;
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

std::vector<int> Party::getOffers()
{
    return this->offers;
}

void Party::addOffer(int toAdd)
{
    this->offers.push_back(toAdd);
}

int Party::getPartyID()
{

    return this->mId;
}

int Party::getMandates() const
{
    return mMandates;
}

const string &Party::getName() const
{
    return mName;
}

void Party::step(Simulation &s)
{
    if (this->getState() == CollectingOffers && Timer != 3)
    {
        Timer++;
    }

    if (Timer == 3)
    {
        this->setState(Joined);

        int AgentID = mJoinPolicy->join(s, this);

        // clone agent
        Agent agent((s.getAgents2()[AgentID]));
        agent.SetID(s.getAgents2().size());
        agent.SetPartyID(this->getPartyID());
        s.getAgents2().push_back(agent);
    }
}

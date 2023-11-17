#pragma once
#include <string>
#include <vector>

using std::string;


class JoinPolicy;
class Simulation;
class Agent;


enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 
    Party(const Party &other);

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
     int getPartyID();
     std::vector<int> getOffers();
     void addOffer(int toAdd);
     Party& operator=(const Party &other);
     Party& operator=( Party &&other);
     Party (Party&& other);
     virtual ~Party();

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int Timer;
    std::vector<int> offers;//agent ids

};

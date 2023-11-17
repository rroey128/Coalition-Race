#pragma once
class Simulation;
class Party;

class JoinPolicy {

public:
virtual int join(Simulation &sim, Party* me) = 0;
virtual JoinPolicy* clone()  = 0;
virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy {
public:
   int join(Simulation &sim, Party* me);
   virtual MandatesJoinPolicy* clone();
};

class LastOfferJoinPolicy : public JoinPolicy {
public:
 int join(Simulation &sim, Party* me);
 virtual LastOfferJoinPolicy* clone();
};
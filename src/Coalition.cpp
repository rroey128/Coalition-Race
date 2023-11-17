#include "Coalition.h"

Coalition::Coalition(Party *party, int ID) : Mandates(party->getMandates()), CoalitionID(ID), partys(), refc(1)
{
    partys.push_back(party);
}

int Coalition::getMandates()
{
    return this->Mandates;
}

vector<Party *> Coalition::getPartys()
{
    return this->partys;
}

void Coalition::addParty(Party *party)
{
    this->partys.push_back(party);
    this->Mandates = this->Mandates + party->getMandates();
}

int Coalition::getCoalitionID()
{

    return this->CoalitionID;
}
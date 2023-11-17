#include "Graph.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges)
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{

    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

vector<int> Graph::getNeighbors(int partyID)
{

    vector<int> neighbors;
    for (unsigned int i = 0; i < mEdges.size(); i++)
    {
        if (mEdges[partyID][i] != 0)
            neighbors.push_back(i);
    }

    return neighbors;
}

Party *Graph::getParty2(int PartyId)
{
    return &mVertices[PartyId];
}

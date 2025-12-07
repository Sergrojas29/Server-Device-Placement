#pragma once

#include "node.hpp"
#include "pointInfo.hpp"

namespace sortedkdtree
{
    struct NearestResult
    {
        Node *parentNode;
        Node *bestNode;
        double bestDistanceSqrd;
        bool goLeft;
        explicit NearestResult() : parentNode(nullptr), bestNode(nullptr), bestDistanceSqrd(std::numeric_limits<double>::max()), goLeft(false) {};
    };
} // sortedkdtree
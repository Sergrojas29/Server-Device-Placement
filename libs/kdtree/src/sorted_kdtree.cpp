#include "sorted_kdtree.hpp"

namespace sortedkdtree
{

    // Public Members
    void sortedKDTree::insertSort(std::vector<PointInfo> &Point_info_Vec)
    {
        std::span<PointInfo> pointSpan(Point_info_Vec);
        recursiveInsertSort(Root, pointSpan, 0);

        // Reordered List set to class
        this->sortedList = std::move(Point_info_Vec);        
    };

    PointInfo sortedKDTree::findNearestNeighbor(const Point &target)
    {

        NearestResult Results;
        recursiveFindNearestNeighbor(target, Root, 0, Results, Root, Results.goLeft);

        PointInfo bestPointInfo = {Results.bestNode->point, Results.bestNode->HANDLE};
        if (Results.goLeft)
        {
            Results.parentNode->left.reset();
        }
        else
        {
            Results.parentNode->right.reset();
        }
        return bestPointInfo;
    };

    using ABlist = std::vector<std::vector<PointInfo>>;
    ABlist sortedKDTree::ABseperation()
    {
        std::vector<PointInfo> Ackt;
        std::vector<PointInfo> Bckt;
        
        int count = 0;
        auto AorB = [&count](const PointInfo& _)
        {
            bool ret = (count % 2) == 0;
            count++;
            return ret;
        };
        
        
        std::partition_copy(this->sortedList.begin(),this->sortedList.end(),
        std::back_inserter(Ackt),
        std::back_inserter(Bckt),
        AorB);
        
        ABlist ABCkt{std::move(Ackt), std::move(Bckt)};
        return ABCkt;
    }

    // Private Members

    void sortedKDTree::recursiveFindNearestNeighbor(const Point &target, NodePtr &current, int depth, NearestResult &Results, NodePtr &parentNode, bool goLeft)
    {
        if (!current)
            return;

        if (current->isLeaf)
        {
            updateResults(target, current, Results, parentNode, goLeft);
        }

        int AXIS = depth % Dimension_;
        bool go_left = (target[AXIS] < current->axis);
        NodePtr &firstNode = go_left ? current->left : current->right;
        NodePtr &otherNode = go_left ? current->right : current->left;

        recursiveFindNearestNeighbor(target, firstNode, depth + 1, Results, current, go_left);

        // r' = (target[axis]-current[axis]) ** 2
        double primeRadius = (target[AXIS] - current->axis);
        double primeRadiusSqrd = primeRadius * primeRadius;

        if (primeRadiusSqrd < Results.bestDistanceSqrd)
        {
            recursiveFindNearestNeighbor(target, otherNode, depth + 1, Results, current, !go_left);
        }
    };

    void sortedKDTree::recursiveInsertSort(NodePtr &current, std::span<PointInfo> &PointInfoSpan, int depth)
    {

        //*Create Unique Node Pointer
        if (!current)
            current = std::make_unique<Node>();

        int SIZE = PointInfoSpan.size();
        //*Base Case for Leaf
        if (SIZE == 1)
        {
            current->point = PointInfoSpan[0].point;
            current->HANDLE = PointInfoSpan[0].HANDLE;
            current->isLeaf = true;
            return;
        }

        int AXIS = depth % Dimension_;
        int INDEX_MEDIAN = SIZE / 2;

        //*Sort by Axis
        std::sort(PointInfoSpan.begin(), PointInfoSpan.end(), [&AXIS](const PointInfo &a, const PointInfo &b)
                  { return a.point[AXIS] < b.point[AXIS]; });

        //*Set Node Axis
        current->axis = PointInfoSpan[INDEX_MEDIAN].point[AXIS];

        std::span<PointInfo> leftSpan = PointInfoSpan.first(INDEX_MEDIAN);
        std::span<PointInfo> rightSpan = PointInfoSpan.last(SIZE - INDEX_MEDIAN);

        //* RecursiveInsert
        recursiveInsertSort(current->left, leftSpan, depth + 1);
        recursiveInsertSort(current->right, rightSpan, depth + 1);
    }

    void sortedKDTree::updateResults(const Point &target, const NodePtr &current, NearestResult &Results, NodePtr &parentNode, bool goLeft)
    {

        double newDistance = squaredEuclideanDistance(target, current->point);
        if (newDistance < Results.bestDistanceSqrd)
        {
            Results.bestDistanceSqrd = newDistance;
            Results.bestNode = current.get();
            Results.parentNode = parentNode.get();
            Results.goLeft = goLeft;
        }
        return;
    }
} // namespace sortedkdtree
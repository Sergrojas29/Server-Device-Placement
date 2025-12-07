#include "node.hpp"
#include "distance.hpp"
#include "pointInfo.hpp"
#include "nearestResult.hpp"

namespace sortedkdtree

{
    class sortedKDTree
    {
    private:
        NodePtr Root;
        std::vector<PointInfo> sortedList;
        int Dimension_;
        int depth_;

    public:
        sortedKDTree(int dimension) : Root(nullptr), Dimension_(dimension), depth_(0) {};
        ~sortedKDTree() {};

        void insertSort(std::vector<PointInfo> &Point_info_Vec);
        PointInfo findNearestNeighbor(const Point &target);

        using ABlist = std::vector<std::vector<PointInfo>>;
        ABlist ABseperation();

    private:
        void recursiveFindNearestNeighbor(const Point &target, NodePtr &current, int depth, NearestResult &Results, NodePtr &parentNode, bool goLeft);

        void recursiveInsertSort(NodePtr &current, std::span<PointInfo> &PointInfoSpan, int depth);

        void updateResults(const Point &target, const NodePtr &current, NearestResult &Results, NodePtr &parentNode , bool goLeft);


    };

} // namespace sortedkdtree
#pragma once
#include <vector>
#include <array>
#include <memory>
#include <cmath>
#include <span>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <optional>
#include <limits>
#include <sstream>
namespace sortedkdtree{

    //2D Tree
    using Point =  std::array<double,2>;
    using PointVec = std::vector<Point>;

       
    
    
    struct Node
    {
        int axis;
        Point point;
        std::string HANDLE;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        bool isLeaf;
        explicit Node():left(nullptr), right(nullptr), isLeaf(false){}
    };
    
    using NodePtr = std::unique_ptr<Node> ;
    
}




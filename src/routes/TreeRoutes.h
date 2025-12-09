#pragma once

#include "crow.h"
#include "sorted_kdtree.hpp"

inline crow::Blueprint make_tree_blueprint()
{

    // Create blueprint with URL prefix "/tree"
    crow::Blueprint bp("tree");

    CROW_BP_ROUTE(bp, "/info")
    ([]
     {
        crow::json::wvalue r;
        r["status"] = "Tree API OK";
        return r; });

    // POST - GET ALL POINTS
    CROW_BP_ROUTE(bp, "/insertAll").methods(crow::HTTPMethod::POST)([](const crow::request &req) {
        auto body = crow::json::load(req.body);

        // if(!body) return crow::response(400, "Invalid JSON");
        
        std::vector<sortedkdtree::PointInfo> pointInfoVec;

        for (auto &i : body["allPoint"])
        {
            sortedkdtree::PointInfo p;
            p.HANDLE = i["HANDLE"].s();

            for (size_t idx = 0; idx < 2; idx++)
            {
                p.point[idx] = i["point"][idx].i();
            }

            pointInfoVec.push_back(p);
        }
        
        for (auto &i : pointInfoVec)
        {
            std::cout << "HANDLE: " << i.HANDLE << "\n";

            std::cout << "point: (";
            for (auto& v : i.point)
                std::cout << v << " ";
            std::cout << ")\n";
        }


        crow::json::wvalue r;
        r["status"] = "Check Server console";
        r["VecResult"] = pointInfoVec.size();
        return r;

    });

    return bp;
} // make_tree_blueprint






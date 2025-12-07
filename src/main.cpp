#include "crow.h"
// #include "sorted_kdtree.hpp" // CMake knows where this is now!

int main() {
    crow::SimpleApp app;
    
    // You can use your class immediately
    // SortedKDTree myTree; 

    CROW_ROUTE(app, "/search")([](){
        return "KDTree search results...";
    });

    app.port(18080).multithreaded().run();
}
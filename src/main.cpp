#include "crow.h"
#include "routes/TreeRoutes.h"


int main() {
    crow::SimpleApp app;

    // Register the blueprint
    // This mounts all routes in TreeRoutes.h under the prefix "/tree"
    crow::Blueprint tree = make_tree_blueprint();
    app.register_blueprint(tree);
    


    CROW_ROUTE(app, "/")([](){
        return "Server is running! Try POST /tree/add";
    });

    app.port(8080).multithreaded().run();
}
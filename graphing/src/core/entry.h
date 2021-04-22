#include "util/logger.h"
#include "core/application.h"


extern application* create_application();

int main(int argc, char** argv) {
    logger::init();

    auto app = create_application();
    app->run();
    delete app;
}
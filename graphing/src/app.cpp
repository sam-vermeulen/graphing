#include "core/entry.h"
#include "core/application.h"

class app : public application {
public:
    app()
    {

    }
};

application* create_application() {
    return new app();
}
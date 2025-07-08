#include "src/logger.h"

int main(){
    log("This is an info message", LOG_TYPE_INFO);
    log("This is a warning message", LOG_TYPE_WARNING);
    log("This is an error message (you should be scared!!!)", LOG_TYPE_ERROR);
    return 0;
}
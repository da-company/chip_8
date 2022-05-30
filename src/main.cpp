#include <iostream>
#include "application.hpp"

int main(int argc, char *argv[]) {
    auto program = new Application("");

    return program->run();
}
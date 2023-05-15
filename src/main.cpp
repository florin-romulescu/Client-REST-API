#include "include/json.hpp"
#include "include/input.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    Input::mainLoop();

    return 0;
}
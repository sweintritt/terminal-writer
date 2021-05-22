#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <string>
#include <map>

void run(std::uniform_int_distribution<int> characterWait) {
    std::random_device rd;
    std::mt19937 r(rd());
    std::uniform_int_distribution<int> lineWait(15, 675);

    // a short break before starting
    std::this_thread::sleep_for(std::chrono::seconds(2));
    for (std::string line; std::getline(std::cin, line);) {

        for (unsigned int i = 0; i < line.size(); ++i) {
            std::cout << line[i] << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(characterWait(r)));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(lineWait(r)));
        std::cout << std::endl << std::flush;
    }
}

std::string getAvailableModes(std::map<std::string, std::function<std::uniform_int_distribution<int>()>> const& modes) {
    std::string availableModes;

    for (auto mode : modes) {
        availableModes.append(mode.first).append(", ");
    }

    return availableModes;
}

int main(int argc, char* argv[]) {
    std::map<std::string, std::function<std::uniform_int_distribution<int>()>> modes;
    modes.emplace("human", []() { return std::uniform_int_distribution<int>(75, 275); });
    modes.emplace("80s", []() { return std::uniform_int_distribution<int>(5, 25); });
    modes.emplace("80s-fast", []() { return std::uniform_int_distribution<int>(5, 15); });

    if (argc > 1) {
        std::string mode{argv[1]};

        if (modes.count(mode)) {
            run(modes[mode]());
        } else {
            std::cerr << "Unknown mode. Options are " << getAvailableModes(modes) << std::endl;
        }
    } else {
            std::cerr << "No mode given. Options are " << getAvailableModes(modes) << std::endl;
        }

    return 0;
}

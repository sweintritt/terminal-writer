
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <thread>

void run(std::uniform_int_distribution<int> characterWait);
std::string getAvailableModes(std::map<std::string, std::function<std::uniform_int_distribution<int>()>> const& modes);

typedef struct Mode {
    std::string name;
    std::string description;
    std::function<std::uniform_int_distribution<int>()> characterWait;
    std::function<std::uniform_int_distribution<int>()> lineWait;

    Mode() : name(), description(), characterWait(), lineWait() {}

    Mode(std::string _name,
         std::string _description,
         std::function<std::uniform_int_distribution<int>()> _characterWait,
         std::function<std::uniform_int_distribution<int>()> _lineWait) : name(_name), description(_description), characterWait(_characterWait), lineWait(_lineWait) { }
} Mode;

void run(Mode& mode) {
    std::random_device rd;
    std::mt19937 r(rd());
    auto lineWait = mode.lineWait();
    auto characterWait = mode.characterWait();

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

std::string getAvailableModes(std::map<std::string, Mode> const& modes) {
    std::string availableModes;

    for (auto mode : modes) {
        availableModes.append(mode.first).append(", ");
    }

    return availableModes;
}

int main(int argc, char* argv[]) {
    std::map<std::string, Mode> modes;
    modes.emplace("human", Mode("human", "Write like a real person", []() { return std::uniform_int_distribution<int>(75, 375); }, []() { return std::uniform_int_distribution<int>(15, 675); }));
    modes.emplace("80s", Mode("80s", "Write like a real person", []() { return std::uniform_int_distribution<int>(5, 25); }, []() { return std::uniform_int_distribution<int>(15, 675); }));
    modes.emplace("80s-fast", Mode("80s-fast", "Write like a real person", []() { return std::uniform_int_distribution<int>(5, 15); }, []() { return std::uniform_int_distribution<int>(15, 675); }));
    modes.emplace("wc4", Mode("wc4", "Like the mission screen in Wing Commander 4", []() { return std::uniform_int_distribution<int>(45, 55); }, []() { return std::uniform_int_distribution<int>(55, 275); }));

    if (argc > 1) {
        std::string mode{argv[1]};

        if (modes.count(mode)) {
            run(modes[mode]);
        } else {
            std::cerr << "Unknown mode. Options are " << getAvailableModes(modes) << std::endl;
        }
    } else {
        std::cerr << "No mode given. Options are " << getAvailableModes(modes) << std::endl;
    }

    return 0;
}

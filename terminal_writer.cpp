
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <thread>

/**
 * Settings for a write mode.
 */
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

void run(std::uniform_int_distribution<int> characterWait);
void showHelp(const std::map<std::string, Mode>& modes);

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

void showHelp(const std::map<std::string, Mode>& modes) {
    std::cout << "terminal-writer - Reads text from stdin an writes it to stdout like in old movies." << std::endl << std::endl;
    std::cout << "tw [MODE]" << std::endl << std::endl;
    std::cout << "Modes:" << std::endl << std::endl;

    for (auto mode : modes) {
        std::cout << "  " << std::setw(11) << std::left << mode.second.name << mode.second.description << std::endl;
    }
}

int main(int argc, char* argv[]) {
    std::map<std::string, Mode> modes;
    modes.emplace("human", Mode("human", "Writes like a real person.", []() { return std::uniform_int_distribution<int>(75, 375); }, []() { return std::uniform_int_distribution<int>(15, 675); }));
    modes.emplace("80s", Mode("80s", "Prints text like in old movies.", []() { return std::uniform_int_distribution<int>(5, 25); }, []() { return std::uniform_int_distribution<int>(15, 675); }));
    modes.emplace("80s-fast", Mode("80s-fast", "Prints text like in old movies, but a bit faster.", []() { return std::uniform_int_distribution<int>(5, 15); }, []() { return std::uniform_int_distribution<int>(15, 275); }));
    modes.emplace("wc4", Mode("wc4", "Like the mission screen in Wing Commander 4.", []() { return std::uniform_int_distribution<int>(45, 55); }, []() { return std::uniform_int_distribution<int>(45, 75); }));

    if (argc > 1) {
        std::string mode{argv[1]};

        if (modes.count(mode)) {
            run(modes[mode]);
        } else if (mode.compare("help") == 0) {
            showHelp(modes);
        } else {
            std::cerr << "Unknown mode: " << mode << std::endl;
            std::cerr << "See 'tw help' for more information." << std::endl;
        }
    } else {
        std::cerr << "No mode given." << std::endl;
        std::cerr << "See 'tw help' for more information." << std::endl;
    }

    return 0;
}

#include <iostream>
#include <chrono>
#include <random>
#include <thread>

void run(std::uniform_int_distribution<int>& characterWait) {
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

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string cmd{argv[1]};
        // TODO Add a map of lambda expressions

        if (cmd.compare("human") == 0) {
            std::uniform_int_distribution<int> human(75, 275);
            run(human);
        } else if (cmd.compare("80s") == 0) {
            std::uniform_int_distribution<int> eighties(5, 25);
            run(eighties);
        } else {
            std::cerr << "Unknown mode. Options are 'human' and '80s'" << std::endl;
        }
    } else {
            std::cerr << "No mode given. Options are 'human' and '80s'" << std::endl;
        }

    return 0;
}

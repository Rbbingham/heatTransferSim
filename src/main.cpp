//
// Created by rbb13 on 3/16/2023.
//

#include "InputParser.h"
#include "Room.h"
#include "omp.h"

#include <cstdio>
#include <unordered_map>

void usage ();

int main (int argc, char *argv[]) {
    InputParser input(argc, argv);

    if (input.cmdOptionExists("-h") ||  input.cmdOptionExists("--help")) {
        usage();
        return 0;
    }

    if (argc != 17 && argc != 9) {
        printf("    Invalid number of arguments\n"
               "    Type ./heatTransferSim -h for help\n");
        return 0;
    }

    std::unordered_map <char, std::string> commands = {
            {'n', input.getCmdOption("-n")},
            {'r', input.getCmdOption("-r")},
            {'c', input.getCmdOption("-c")},
            {'t', input.getCmdOption("-t")},
            {'k', input.getCmdOption("-k")},
            {'s', input.getCmdOption("-s")}
    };

    const std::string& inFile = input.getCmdOption("--input");
    const std::string& outFile = input.getCmdOption("--output");

    Room matrix(std::stoi(commands['r']), std::stoi(commands['c']), std::stod(commands['t']));
    matrix.print();

    return 0;
}

void usage () {
    std::printf("NAME\n"
                "   Heat_Transfer\n"
                "SYNOPSIS\n"
                "   ./Heat_Transfer [-n NUM_THREADS] [-r NUM_ROWS] [-c NUM_COLS] [-t BASE_TEMP] [-k RATE] [-s TIMESTEPS]\n"
                "   [--input INPUT_FILE] [--output OUTPUT_FILE]\n"
    );
}
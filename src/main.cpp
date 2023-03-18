//
// Created by rbb13 on 3/16/2023.
//

#include "InputParser.h"
#include "Room.h"
#include "omp.h"

#include <cstdio>
#include <unordered_map>
#include <fstream>
#include <vector>

void usage ();

int main (int argc, char *argv[]) {
    InputParser input(argc, argv);
    std::vector<std::tuple<int, int, double>> heaters;

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
            {'s', input.getCmdOption("-s")},
            {'i', input.getCmdOption("--input")},
            {'o', input.getCmdOption("--output")}
    };

    Room oldMatrix(std::stoi(commands['r']), std::stoi(commands['c']), std::stod(commands['t']));

    std::ifstream inFile("../../" + commands['i']);

    if (inFile.good()) {
        int ht;
        inFile >> ht;

        while (ht--) {
            int row, col;
            double temp;

            inFile >> row >> col >> temp;
            heaters.emplace_back(std::make_tuple(row, col, temp));
        }
    }

    inFile.close();

    Room newMatrix = oldMatrix;
    int timesteps = std::stoi(commands['s']);
    const double k = std::stod(commands['k']);

    while (timesteps--) {
        oldMatrix.setHeat(heaters);
        oldMatrix.print();
        printf("\n\n");

        for (int i = 1; i < newMatrix.getRows() - 1; ++i) {
            for (int j = 1; j < newMatrix.getCols() - 1; ++j) {
                newMatrix.calculateTemp(oldMatrix, i, j, k);
            }
        }

        oldMatrix = newMatrix;
    }

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
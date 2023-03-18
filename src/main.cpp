/*
 * Author: Robert Bingham
 * Description: a heat distribution simulation based on the formula:
 *      Tnew = (Told + (k*(Ttop + Tbottom + Tleft + Tright + Ttop_left + Tbottom_left + Ttop_right + Tbottom_right))/8.0)/2.0.
 *      Each 'T' represents a temperature value in a matrix and 'k' represents the transfer rate.
 */

#include "InputParser.h"
#include "room.h"
#include "omp.h"

#include <cstdio>
#include <unordered_map>
#include <fstream>
#include <vector>

// manual page for program
void usage ();

int main (int argc, char *argv[]) {
    // initialize command line parser and vector for heater positions
    InputParser input(argc, argv);
    std::vector<std::tuple<int, int, double>> heaters;

    // if command -h or --help was given, output usage
    if (input.cmdOptionExists("-h") ||  input.cmdOptionExists("--help")) {
        usage();
        return 0;
    }

    // don't run program if invalid number of arguments
    if (argc != 17 && argc != 9) {
        printf("    Invalid number of arguments\n"
               "    Type ./heatTransferSim -h for help\n");
        return 0;
    }

    // store our arguments in map
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

    // initialize the matrix with basetemp = k
    Room oldMatrix(std::stoi(commands['r']), std::stoi(commands['c']), std::stod(commands['t']));

    std::ifstream inFile("../../" + commands['i']);

    // get heater positions from file
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

    // initialize a copy of the old matrix and set heaters
    Room newMatrix = oldMatrix;
    oldMatrix.setHeat(heaters);

    int timesteps = std::stoi(commands['s']);
    double k = std::stod(commands['k']);
    const int thread_count = std::stoi(commands['n']);
    double totalTime = 0;

    // outputs starting matrix
    printf("Starting matrix: \n");
    oldMatrix.print();
    printf("\n\n");

    while (timesteps--) {
        double start = omp_get_wtime();
        double end;

        // parallelize with each thread having a row to themselves
        omp_set_num_threads(thread_count);
        #pragma omp parallel for default(none) shared(newMatrix, oldMatrix, k)
        for (int i = 1; i < newMatrix.getRows() - 1; ++i) {
            for (int j = 1; j < newMatrix.getCols() - 1; ++j) {
                newMatrix.calculateTemp(oldMatrix, i, j, k);
            }
        }

        end = omp_get_wtime();

        // copy values to the old matrix and reset the heaters
        oldMatrix = newMatrix;
        oldMatrix.setHeat(heaters);

        // print values and time elapsed
        oldMatrix.print();
        printf("Time elapsed: %f\n\n", end - start);
        totalTime += (end - start);
    }

    printf("Total time elapsed: %f", totalTime);

    // output to file
    std::ofstream outFile("../../" + commands['o']);
    if (outFile.good()) {
        for (int i = 0; i < oldMatrix.getRows() - 2; ++i) {
            for (int j = 0; j < oldMatrix.getCols() - 2; ++j) {
                outFile << oldMatrix.getTemp(i, j) << ", ";
            }
            outFile << "\n";
        }
    }

    outFile.close();

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
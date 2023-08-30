#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Structure to represent a block
struct Block {
    string name;
    int width;
    int height;
    int x_position;
    int y_position;
};

int main() {
    ifstream inputFile("blocks.txt"); // Replace "blocks.txt" with your input file name
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }

    ofstream pltFile("plot_blocks.plt"); // Output Gnuplot script file
    if (!pltFile) {
        cerr << "Error: Unable to create plt file." << endl;
        return 1;
    }

    pltFile << "set terminal pngcairo enhanced" << endl;
    pltFile << "set output 'blocks.png'" << endl;
    pltFile << "set size ratio -1" << endl;
    pltFile << "set xrange [0:1000]" << endl; // Adjust the x-axis range as needed
    pltFile << "set yrange [0:1000]" << endl; // Adjust the y-axis range as needed

    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        Block block;

        if (iss >> block.name >> block.width >> block.height >> block.x_position >> block.y_position) {
            pltFile << "set object rect from "
                    << block.x_position << ", "
                    << block.y_position << " to "
                    << block.x_position + block.width << ", "
                    << block.y_position + block.height
                    << " fc rgb 'blue' fill solid border lc rgb 'black' lw 1" << endl;
        } else {
            cerr << "Error: Invalid line in input file: " << line << endl;
        }
    }

    pltFile << "plot NaN notitle" << endl;
    inputFile.close();
    pltFile.close();

    cout << "Gnuplot script generated in 'plot_blocks.plt'" << endl;
    return 0;
}
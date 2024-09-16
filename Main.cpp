#include <iostream>
#include "core.h"
#include "AtomsSimulation.h"
#include "FileSystem.h"
#include "SimSettings.h"
#include "Atom.h"

using namespace sf;
using namespace std;



int main(int argc, char** argv[]) {
    

    RANDOM

    AtomsSimulation sim;
    sim.Run();


    return 0;
}

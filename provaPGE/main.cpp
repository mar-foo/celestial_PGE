#include "Interface.h"

int main() {

	Celestial_Simulation simulation;

	if (simulation.Construct(720, 480, 1, 1))
		simulation.Start();

	return 0;
}

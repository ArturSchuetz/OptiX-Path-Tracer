#include <CameraUtils/BowApplication.h>

#include <optix-path-tracer/cuda_config.h>

#include "Application.h"

#include <iostream>
#include <optix.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int /*argc*/, char* /*argv[]*/)
{
	std::cout << std::endl;
	std::cout << "=======================================================================" << std::endl;
	std::cout << "[Controls:]" << std::endl;
	std::cout << "Use [W][A][S][D] to move around the scene." << std::endl;
	std::cout << "Use [SPACE] to move upwards." << std::endl;
	std::cout << "Use [CTRL] to move downwards." << std::endl;
	std::cout << "Use [LEFT SHIFT] to increase moving speed." << std::endl;
	std::cout << "Move the Mouse while pressing the [Right Mousebutton] to look around." << std::endl;
	std::cout << "=======================================================================" << std::endl;
	std::cout << std::endl;

	SimpleDirectionalLightApp app;
	app.Run();

	return 0;
}

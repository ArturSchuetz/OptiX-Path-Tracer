#include "Application.h"

#include <optix-path-tracer/cuda_config.h>

#include <iostream>     // std::cout, std::endl
#include <iomanip>      // std::setw


//------------------------------------------------------------------------------
//
//  Helper functions
//
//------------------------------------------------------------------------------

struct UsageReportLogger
{
	void log(int lvl, const char* tag, const char* msg)
	{
		std::cout << "[" << lvl << "][" << std::left << std::setw(12) << tag << "] " << msg;
	}
};


// Static callback
void usageReportCallback(int lvl, const char* tag, const char* msg, void* cbdata)
{
	// Route messages to a C++ object (the "logger"), as a real app might do.
	// We could have printed them directly in this simple case.

	UsageReportLogger* logger = reinterpret_cast<UsageReportLogger*>(cbdata);
	logger->log(lvl, tag, msg);
}


// ======================================================================
// ======================================================================


SimpleDirectionalLightApp::SimpleDirectionalLightApp()
{

}


SimpleDirectionalLightApp::~SimpleDirectionalLightApp()
{

}

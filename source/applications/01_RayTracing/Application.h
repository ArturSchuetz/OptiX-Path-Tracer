#include <CameraUtils/BowApplication.h>
#include <CameraUtils/FirstPersonCamera.h>

struct UsageReportLogger;

class SimpleDirectionalLightApp : public bow::Application
{
public:
	SimpleDirectionalLightApp();
	~SimpleDirectionalLightApp();

private:
	std::string GetWindowTitle(void) { return "Fresnel Reflections And Specularity"; }
};
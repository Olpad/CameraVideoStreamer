/**
 * @class Application
 * @brief Main application point. Creates and initializes all the services.
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Context.h"
#include "./Configuration/BasicINIConfigReader.h"
#include "./Logs/BasicTxtLogger.h"
#include "./Devices/BasicCameraHandler.h"
#include <iostream>
#include <gst/gst.h>

class Application
{
public:
	Application();

	virtual ~Application();

protected:
	Context* m_context;

	void PreInitializeApp();
};

#endif /* APPLICATION_H_ */

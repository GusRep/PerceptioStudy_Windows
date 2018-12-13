#pragma once
//#pragma comment(lib, "ws2_32.lib")
 
#include "ATC3DG.h"


//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by Sample.rc
//

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        101
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1000
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif


class CSystem
{
public:
	SYSTEM_CONFIGURATION	m_config;
};

class CSensor
{
public:
	SENSOR_CONFIGURATION	m_config;
};

class CXmtr
{
public:
	TRANSMITTER_CONFIGURATION	m_config;
};


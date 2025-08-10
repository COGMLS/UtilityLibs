#pragma once

/********************************************************************
 * Version Library Experimental Features Control for C components
 * 
 * This file is destined to only control the experimental features
 * available to C components in Version Library. Any C++ feature is
 * controlled by .hpp file
 * 
********************************************************************/

#ifndef VERSION_LIBRARY_EXPERIMENTAL_FEATURES_CONTROL_H
#define VERSION_LIBRARY_EXPERIMENTAL_FEATURES_CONTROL_H

#include "VersionLibVersionInfo.h"

//
// Alpha Features:
//

#if VERSION_LIB_BUILD_TYPE == 1
#endif // !VERSION_LIB_BUILD_TYPE is Alpha

//
// Beta Features:
//

#if VERSION_LIB_BUILD_TYPE == 2
#endif // !VERSION_LIB_BUILD_TYPE is Beta

//
// Release Candidate Features:
//

#if VERSION_LIB_BUILD_TYPE == 3
#endif // !VERSION_LIB_BUILD_TYPE is Release Candidate

//
// Experimental Features for Release version:
//

#if VERSION_LIB_BUILD_TYPE == 4
#endif // !VERSION_LIB_BUILD_TYPE is Release

#endif // !VERSION_LIBRARY_EXPERIMENTAL_FEATURES_CONTROL_H
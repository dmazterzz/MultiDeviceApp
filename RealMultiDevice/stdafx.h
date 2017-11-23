// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#ifndef WINVER                      // Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0600               // Target Windows Vista or later.
#endif

#ifndef _WIN32_WINNT                // Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0600         // Target Windows Vista or later.
#endif

#ifndef _WIN32_WINDOWS              // Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0600       //  Target Windows Vista or later.
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN         // Exclude rarely-used stuff from Windows headers
#endif
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <windows.h>
#include <commdlg.h>
#include <new>
#include <shlwapi.h>
#include <propvarutil.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

#include <PortableDeviceApi.h>      // Include this header for Windows Portable Device API interfaces
#include <PortableDevice.h>         // Include this header for Windows Portable Device definitions
#include "CommonFunctions.h"        // Includes common prototypes for functions used across source files

#define SELECTION_BUFFER_SIZE 81    // Buffer size for user selection

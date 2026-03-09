// winmm_proxy.h
// BZR Open Shim - winmm.dll proxy forward declarations
// All winmm exports are forwarded to the real System32 winmm.dll.
// The DllMain in dllmain.cpp bootstraps the BZCP loader.
//
// BZR.exe loads winmm.dll from its own directory before System32.
// This shim intercepts that load, forwards all real calls, and injects patches.

#pragma once
#define _WINMM_
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <mmsystem.h>

// Handle to the real winmm.dll in System32
extern HMODULE g_hRealWinmm;

// Load the real winmm.dll - called once in DllMain DLL_PROCESS_ATTACH
bool LoadRealWinmm();
void FreeRealWinmm();
FARPROC ResolveRealWinmmProc(const char* name);

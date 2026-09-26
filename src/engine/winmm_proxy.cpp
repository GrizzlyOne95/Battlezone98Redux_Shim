// winmm_proxy.cpp
// BZR Open Shim - proxy loader for the real winmm.dll
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "winmm_proxy.h"
#include "shim_log.h"
#include <cstdio>

HMODULE g_hRealWinmm = nullptr;

// Legacy thunk exports that need naked tail-jump forwarders.
#define LEGACY_NAKED_EXPORTS(X) \
    X(WOW32DriverCallback) \
    X(WOW32ResolveMultiMediaHandle) \
    X(WOWAppExit) \
    X(aux32Message) \
    X(joy32Message) \
    X(mci32Message) \
    X(mid32Message) \
    X(mmGetCurrentTask) \
    X(mmTaskBlock) \
    X(mmTaskCreate) \
    X(mmTaskSignal) \
    X(mmTaskYield) \
    X(mod32Message) \
    X(mxd32Message) \
    X(tid32Message) \
    X(wid32Message) \
    X(wod32Message)

#define DECL_LEGACY_SLOT(name) static FARPROC g_fp_##name = nullptr;
LEGACY_NAKED_EXPORTS(DECL_LEGACY_SLOT)
#undef DECL_LEGACY_SLOT

FARPROC ResolveRealWinmmProc(const char* name)
{
    if (!g_hRealWinmm)
    {
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "winmm", "Attempted to resolve %s before real winmm.dll was loaded", name ? name : "<null>");
        return nullptr;
    }

    FARPROC proc = GetProcAddress(g_hRealWinmm, name);
    if (!proc)
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "winmm", "GetProcAddress failed for %s (err=%lu)", name ? name : "<null>", GetLastError());
    return proc;
}

bool LoadRealWinmm()
{
    char path[MAX_PATH] = {};
    const UINT len = GetSystemDirectoryA(path, MAX_PATH);
    if (len == 0 || len >= MAX_PATH)
    {
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "winmm", "GetSystemDirectoryA failed (len=%u err=%lu)", len, GetLastError());
        return false;
    }

    strncat_s(path, "\\winmm.dll", MAX_PATH);
    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "winmm", "Loading real winmm.dll from %s", path);

    g_hRealWinmm = LoadLibraryA(path);
    if (!g_hRealWinmm)
    {
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Error, "winmm", "LoadLibraryA failed for %s (err=%lu)", path, GetLastError());
        return false;
    }

#define RESOLVE_LEGACY_SLOT(name) \
    g_fp_##name = ResolveRealWinmmProc(#name); \
    if (!g_fp_##name) BZROpenShim::LogShimA(BZROpenShim::LogLevel::Warn, "winmm", "Legacy export %s was not found", #name);
    LEGACY_NAKED_EXPORTS(RESOLVE_LEGACY_SLOT)
#undef RESOLVE_LEGACY_SLOT

    BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "winmm", "Real winmm.dll loaded successfully at 0x%p", g_hRealWinmm);
    return true;
}

void FreeRealWinmm()
{
    if (g_hRealWinmm)
    {
        BZROpenShim::LogShimA(BZROpenShim::LogLevel::Info, "winmm", "Freeing real winmm.dll handle 0x%p", g_hRealWinmm);
        FreeLibrary(g_hRealWinmm);
        g_hRealWinmm = nullptr;
    }
}

// ---------------------------------------------------------------------------
// Helper macro: each export resolves its proc lazily on first call
// ---------------------------------------------------------------------------
// Resolved once the real DLL is loaded. A real winmm.dll without the export (Wine's lacks some of
// the rarely used ones) gets the function's own "not supported" answer
// instead of a call through a null pointer, and one log line instead of one
// per call.
#define FORWARD(name, failure, args) \
    static decltype(&::name) _fn_##name = nullptr; \
    static bool _resolved_##name = false; \
    if (!_resolved_##name) \
    { \
        _fn_##name = reinterpret_cast<decltype(&::name)>(ResolveRealWinmmProc(#name)); \
        _resolved_##name = g_hRealWinmm != nullptr; \
    } \
    if (!_fn_##name) \
        return failure; \
    return _fn_##name args

#if defined(_M_IX86)
#define FORWARD_NAKED(name) \
    extern "C" __declspec(naked) void WINAPI name() \
    { \
        __asm { \
            jmp dword ptr [g_fp_##name] \
        } \
    }
#else
#error BZR Open Shim winmm proxy requires Win32/x86 build for naked legacy forwarders.
#endif

// ---------------------------------------------------------------------------
// All winmm.dll exports forwarded to the real DLL.
// The list mirrors the export table of the system winmm.dll (SysWOW64); a proxy
// has to reproduce every name the loader may bind.
// ---------------------------------------------------------------------------

extern "C"
{
    WINMMAPI MCIERROR  WINAPI mciSendCommandA(MCIDEVICEID a, UINT b, DWORD_PTR c, DWORD_PTR d)      { FORWARD(mciSendCommandA, MCIERR_UNSUPPORTED_FUNCTION, (a,b,c,d)); }
    WINMMAPI MCIERROR  WINAPI mciSendCommandW(MCIDEVICEID a, UINT b, DWORD_PTR c, DWORD_PTR d)      { FORWARD(mciSendCommandW, MCIERR_UNSUPPORTED_FUNCTION, (a,b,c,d)); }
    WINMMAPI MCIERROR  WINAPI mciSendStringA(LPCSTR a, LPSTR b, UINT c, HWND d)                    { FORWARD(mciSendStringA, MCIERR_UNSUPPORTED_FUNCTION, (a,b,c,d)); }
    WINMMAPI MCIERROR  WINAPI mciSendStringW(LPCWSTR a, LPWSTR b, UINT c, HWND d)                  { FORWARD(mciSendStringW, MCIERR_UNSUPPORTED_FUNCTION, (a,b,c,d)); }
    WINMMAPI BOOL      WINAPI mciGetErrorStringA(MCIERROR a, LPSTR b, UINT c)                       { FORWARD(mciGetErrorStringA, FALSE, (a,b,c)); }
    WINMMAPI BOOL      WINAPI mciGetErrorStringW(MCIERROR a, LPWSTR b, UINT c)                      { FORWARD(mciGetErrorStringW, FALSE, (a,b,c)); }
    WINMMAPI BOOL      WINAPI mciSetYieldProc(MCIDEVICEID a, YIELDPROC b, DWORD c)                  { FORWARD(mciSetYieldProc, FALSE, (a,b,c)); }
    WINMMAPI HTASK     WINAPI mciGetCreatorTask(MCIDEVICEID a)                                       { FORWARD(mciGetCreatorTask, nullptr, (a)); }
    WINMMAPI YIELDPROC WINAPI mciGetYieldProc(MCIDEVICEID a, LPDWORD b)                             { FORWARD(mciGetYieldProc, nullptr, (a,b)); }
    WINMMAPI BOOL      WINAPI mciExecute(LPCSTR a)                                                   { FORWARD(mciExecute, FALSE, (a)); }
    WINMMAPI MCIDEVICEID WINAPI mciGetDeviceIDA(LPCSTR a)                                            { FORWARD(mciGetDeviceIDA, 0, (a)); }
    WINMMAPI MCIDEVICEID WINAPI mciGetDeviceIDW(LPCWSTR a)                                           { FORWARD(mciGetDeviceIDW, 0, (a)); }
    WINMMAPI MCIDEVICEID WINAPI mciGetDeviceIDFromElementIDA(DWORD a, LPCSTR b)                      { FORWARD(mciGetDeviceIDFromElementIDA, 0, (a,b)); }
    WINMMAPI MCIDEVICEID WINAPI mciGetDeviceIDFromElementIDW(DWORD a, LPCWSTR b)                     { FORWARD(mciGetDeviceIDFromElementIDW, 0, (a,b)); }
    WINMMAPI DWORD_PTR WINAPI mciGetDriverData(MCIDEVICEID a)                                        { FORWARD(mciGetDriverData, 0, (a)); }
    WINMMAPI BOOL      WINAPI mciSetDriverData(MCIDEVICEID a, DWORD_PTR b)                           { FORWARD(mciSetDriverData, FALSE, (a,b)); }

    WINMMAPI BOOL  WINAPI PlaySoundA(LPCSTR a, HMODULE b, DWORD c)                                  { FORWARD(PlaySoundA, FALSE, (a,b,c)); }
    WINMMAPI BOOL  WINAPI PlaySoundW(LPCWSTR a, HMODULE b, DWORD c)                                 { FORWARD(PlaySoundW, FALSE, (a,b,c)); }
    WINMMAPI BOOL  WINAPI sndPlaySoundA(LPCSTR a, UINT b)                                            { FORWARD(sndPlaySoundA, FALSE, (a,b)); }
    WINMMAPI BOOL  WINAPI sndPlaySoundW(LPCWSTR a, UINT b)                                           { FORWARD(sndPlaySoundW, FALSE, (a,b)); }

    WINMMAPI DWORD WINAPI timeGetTime_fwd()                                                        { FORWARD(timeGetTime, 0, ()); } // see exports .def

    WINMMAPI MMRESULT WINAPI timeBeginPeriod(UINT a)   { FORWARD(timeBeginPeriod, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI timeEndPeriod(UINT a)     { FORWARD(timeEndPeriod, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI timeGetDevCaps(LPTIMECAPS a, UINT b)  { FORWARD(timeGetDevCaps, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI timeGetSystemTime(LPMMTIME a, UINT b) { FORWARD(timeGetSystemTime, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI timeKillEvent(UINT a)     { FORWARD(timeKillEvent, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI timeSetEvent(UINT a, UINT b, LPTIMECALLBACK c, DWORD_PTR d, UINT e) { FORWARD(timeSetEvent, MMSYSERR_NOTSUPPORTED, (a,b,c,d,e)); }

    WINMMAPI MMRESULT WINAPI waveOutOpen(LPHWAVEOUT a, UINT b, LPCWAVEFORMATEX c, DWORD_PTR d, DWORD_PTR e, DWORD f) { FORWARD(waveOutOpen, MMSYSERR_NOTSUPPORTED, (a,b,c,d,e,f)); }
    WINMMAPI MMRESULT WINAPI waveOutClose(HWAVEOUT a)  { FORWARD(waveOutClose, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI waveOutWrite(HWAVEOUT a, LPWAVEHDR b, UINT c)                          { FORWARD(waveOutWrite, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveOutPause(HWAVEOUT a)  { FORWARD(waveOutPause, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI waveOutRestart(HWAVEOUT a){ FORWARD(waveOutRestart, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI waveOutReset(HWAVEOUT a)  { FORWARD(waveOutReset, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI waveOutBreakLoop(HWAVEOUT a){ FORWARD(waveOutBreakLoop, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI waveOutPrepareHeader(HWAVEOUT a, LPWAVEHDR b, UINT c)                  { FORWARD(waveOutPrepareHeader, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveOutUnprepareHeader(HWAVEOUT a, LPWAVEHDR b, UINT c)                { FORWARD(waveOutUnprepareHeader, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveOutGetPosition(HWAVEOUT a, LPMMTIME b, UINT c)                     { FORWARD(waveOutGetPosition, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveOutGetPitch(HWAVEOUT a, LPDWORD b)                                 { FORWARD(waveOutGetPitch, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI waveOutSetPitch(HWAVEOUT a, DWORD b)                                   { FORWARD(waveOutSetPitch, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI waveOutGetPlaybackRate(HWAVEOUT a, LPDWORD b)                          { FORWARD(waveOutGetPlaybackRate, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI waveOutSetPlaybackRate(HWAVEOUT a, DWORD b)                            { FORWARD(waveOutSetPlaybackRate, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI waveOutGetVolume(HWAVEOUT a, LPDWORD b)                                { FORWARD(waveOutGetVolume, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI waveOutSetVolume(HWAVEOUT a, DWORD b)                                  { FORWARD(waveOutSetVolume, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI waveOutGetErrorTextA(MMRESULT a, LPSTR b, UINT c)                      { FORWARD(waveOutGetErrorTextA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveOutGetErrorTextW(MMRESULT a, LPWSTR b, UINT c)                     { FORWARD(waveOutGetErrorTextW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI UINT     WINAPI waveOutGetNumDevs()                                                      { FORWARD(waveOutGetNumDevs, 0, ()); }
    WINMMAPI MMRESULT WINAPI waveOutGetDevCapsA(UINT_PTR a, LPWAVEOUTCAPSA b, UINT c)               { FORWARD(waveOutGetDevCapsA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveOutGetDevCapsW(UINT_PTR a, LPWAVEOUTCAPSW b, UINT c)               { FORWARD(waveOutGetDevCapsW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveOutGetID(HWAVEOUT a, LPUINT b)                                     { FORWARD(waveOutGetID, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI waveOutMessage(HWAVEOUT a, UINT b, DWORD_PTR c, DWORD_PTR d)           { FORWARD(waveOutMessage, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }

    WINMMAPI MMRESULT WINAPI waveInOpen(LPHWAVEIN a, UINT b, LPCWAVEFORMATEX c, DWORD_PTR d, DWORD_PTR e, DWORD f) { FORWARD(waveInOpen, MMSYSERR_NOTSUPPORTED, (a,b,c,d,e,f)); }
    WINMMAPI MMRESULT WINAPI waveInClose(HWAVEIN a)    { FORWARD(waveInClose, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI waveInAddBuffer(HWAVEIN a, LPWAVEHDR b, UINT c)                        { FORWARD(waveInAddBuffer, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveInStart(HWAVEIN a)    { FORWARD(waveInStart, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI waveInStop(HWAVEIN a)     { FORWARD(waveInStop, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI waveInReset(HWAVEIN a)    { FORWARD(waveInReset, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI waveInPrepareHeader(HWAVEIN a, LPWAVEHDR b, UINT c)                    { FORWARD(waveInPrepareHeader, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveInUnprepareHeader(HWAVEIN a, LPWAVEHDR b, UINT c)                  { FORWARD(waveInUnprepareHeader, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveInGetPosition(HWAVEIN a, LPMMTIME b, UINT c)                       { FORWARD(waveInGetPosition, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveInGetErrorTextA(MMRESULT a, LPSTR b, UINT c)                       { FORWARD(waveInGetErrorTextA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveInGetErrorTextW(MMRESULT a, LPWSTR b, UINT c)                      { FORWARD(waveInGetErrorTextW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI UINT     WINAPI waveInGetNumDevs()                                                       { FORWARD(waveInGetNumDevs, 0, ()); }
    WINMMAPI MMRESULT WINAPI waveInGetDevCapsA(UINT_PTR a, LPWAVEINCAPSA b, UINT c)                 { FORWARD(waveInGetDevCapsA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveInGetDevCapsW(UINT_PTR a, LPWAVEINCAPSW b, UINT c)                 { FORWARD(waveInGetDevCapsW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI waveInGetID(HWAVEIN a, LPUINT b)                                       { FORWARD(waveInGetID, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI waveInMessage(HWAVEIN a, UINT b, DWORD_PTR c, DWORD_PTR d)             { FORWARD(waveInMessage, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }

    WINMMAPI MMRESULT WINAPI midiOutOpen(LPHMIDIOUT a, UINT b, DWORD_PTR c, DWORD_PTR d, DWORD e)   { FORWARD(midiOutOpen, MMSYSERR_NOTSUPPORTED, (a,b,c,d,e)); }
    WINMMAPI MMRESULT WINAPI midiOutClose(HMIDIOUT a)  { FORWARD(midiOutClose, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI midiOutShortMsg(HMIDIOUT a, DWORD b)                                    { FORWARD(midiOutShortMsg, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI midiOutLongMsg(HMIDIOUT a, LPMIDIHDR b, UINT c)                        { FORWARD(midiOutLongMsg, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiOutPrepareHeader(HMIDIOUT a, LPMIDIHDR b, UINT c)                  { FORWARD(midiOutPrepareHeader, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiOutUnprepareHeader(HMIDIOUT a, LPMIDIHDR b, UINT c)                { FORWARD(midiOutUnprepareHeader, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiOutReset(HMIDIOUT a)  { FORWARD(midiOutReset, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI midiOutGetVolume(HMIDIOUT a, LPDWORD b)                                { FORWARD(midiOutGetVolume, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI midiOutSetVolume(HMIDIOUT a, DWORD b)                                  { FORWARD(midiOutSetVolume, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI midiOutCacheDrumPatches(HMIDIOUT a, UINT b, WORD* c, UINT d)           { FORWARD(midiOutCacheDrumPatches, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }
    WINMMAPI MMRESULT WINAPI midiOutCachePatches(HMIDIOUT a, UINT b, WORD* c, UINT d)               { FORWARD(midiOutCachePatches, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }
    WINMMAPI MMRESULT WINAPI midiOutGetErrorTextA(MMRESULT a, LPSTR b, UINT c)                      { FORWARD(midiOutGetErrorTextA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiOutGetErrorTextW(MMRESULT a, LPWSTR b, UINT c)                     { FORWARD(midiOutGetErrorTextW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI UINT     WINAPI midiOutGetNumDevs()                                                      { FORWARD(midiOutGetNumDevs, 0, ()); }
    WINMMAPI MMRESULT WINAPI midiOutGetDevCapsA(UINT_PTR a, LPMIDIOUTCAPSA b, UINT c)               { FORWARD(midiOutGetDevCapsA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiOutGetDevCapsW(UINT_PTR a, LPMIDIOUTCAPSW b, UINT c)               { FORWARD(midiOutGetDevCapsW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiOutGetID(HMIDIOUT a, LPUINT b)                                     { FORWARD(midiOutGetID, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI midiOutMessage(HMIDIOUT a, UINT b, DWORD_PTR c, DWORD_PTR d)           { FORWARD(midiOutMessage, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }

    WINMMAPI MMRESULT WINAPI midiInOpen(LPHMIDIIN a, UINT b, DWORD_PTR c, DWORD_PTR d, DWORD e)     { FORWARD(midiInOpen, MMSYSERR_NOTSUPPORTED, (a,b,c,d,e)); }
    WINMMAPI MMRESULT WINAPI midiInClose(HMIDIIN a)    { FORWARD(midiInClose, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI midiInAddBuffer(HMIDIIN a, LPMIDIHDR b, UINT c)                        { FORWARD(midiInAddBuffer, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiInStart(HMIDIIN a)    { FORWARD(midiInStart, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI midiInStop(HMIDIIN a)     { FORWARD(midiInStop, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI midiInReset(HMIDIIN a)    { FORWARD(midiInReset, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI midiInPrepareHeader(HMIDIIN a, LPMIDIHDR b, UINT c)                    { FORWARD(midiInPrepareHeader, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiInUnprepareHeader(HMIDIIN a, LPMIDIHDR b, UINT c)                  { FORWARD(midiInUnprepareHeader, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiInGetErrorTextA(MMRESULT a, LPSTR b, UINT c)                       { FORWARD(midiInGetErrorTextA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiInGetErrorTextW(MMRESULT a, LPWSTR b, UINT c)                      { FORWARD(midiInGetErrorTextW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI UINT     WINAPI midiInGetNumDevs()                                                       { FORWARD(midiInGetNumDevs, 0, ()); }
    WINMMAPI MMRESULT WINAPI midiInGetDevCapsA(UINT_PTR a, LPMIDIINCAPSA b, UINT c)                 { FORWARD(midiInGetDevCapsA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiInGetDevCapsW(UINT_PTR a, LPMIDIINCAPSW b, UINT c)                 { FORWARD(midiInGetDevCapsW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiInGetID(HMIDIIN a, LPUINT b)                                       { FORWARD(midiInGetID, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI midiInMessage(HMIDIIN a, UINT b, DWORD_PTR c, DWORD_PTR d)             { FORWARD(midiInMessage, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }
    WINMMAPI MMRESULT WINAPI midiConnect(HMIDI a, HMIDIOUT b, LPVOID c)                             { FORWARD(midiConnect, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiDisconnect(HMIDI a, HMIDIOUT b, LPVOID c)                          { FORWARD(midiDisconnect, MMSYSERR_NOTSUPPORTED, (a,b,c)); }

    WINMMAPI MMRESULT WINAPI midiStreamOpen(LPHMIDISTRM a, LPUINT b, DWORD c, DWORD_PTR d, DWORD_PTR e, DWORD f) { FORWARD(midiStreamOpen, MMSYSERR_NOTSUPPORTED, (a,b,c,d,e,f)); }
    WINMMAPI MMRESULT WINAPI midiStreamClose(HMIDISTRM a) { FORWARD(midiStreamClose, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI midiStreamOut(HMIDISTRM a, LPMIDIHDR b, UINT c)                        { FORWARD(midiStreamOut, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiStreamPause(HMIDISTRM a) { FORWARD(midiStreamPause, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI midiStreamPosition(HMIDISTRM a, LPMMTIME b, UINT c)                    { FORWARD(midiStreamPosition, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiStreamProperty(HMIDISTRM a, LPBYTE b, DWORD c)                     { FORWARD(midiStreamProperty, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI midiStreamRestart(HMIDISTRM a) { FORWARD(midiStreamRestart, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI midiStreamStop(HMIDISTRM a)  { FORWARD(midiStreamStop, MMSYSERR_NOTSUPPORTED, (a)); }

    WINMMAPI UINT  WINAPI auxGetNumDevs()              { FORWARD(auxGetNumDevs, 0, ()); }
    WINMMAPI MMRESULT WINAPI auxGetDevCapsA(UINT_PTR a, LPAUXCAPSA b, UINT c)                       { FORWARD(auxGetDevCapsA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI auxGetDevCapsW(UINT_PTR a, LPAUXCAPSW b, UINT c)                       { FORWARD(auxGetDevCapsW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT  WINAPI auxGetVolume(UINT a, LPDWORD b)                                        { FORWARD(auxGetVolume, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT  WINAPI auxSetVolume(UINT a, DWORD b)                                          { FORWARD(auxSetVolume, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT  WINAPI auxOutMessage(UINT a, UINT b, DWORD_PTR c, DWORD_PTR d)                 { FORWARD(auxOutMessage, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }

    WINMMAPI UINT  WINAPI mixerGetNumDevs()            { FORWARD(mixerGetNumDevs, 0, ()); }
    WINMMAPI MMRESULT WINAPI mixerOpen(LPHMIXER a, UINT b, DWORD_PTR c, DWORD_PTR d, DWORD e)       { FORWARD(mixerOpen, MMSYSERR_NOTSUPPORTED, (a,b,c,d,e)); }
    WINMMAPI MMRESULT WINAPI mixerClose(HMIXER a)      { FORWARD(mixerClose, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI DWORD   WINAPI mixerMessage(HMIXER a, UINT b, DWORD_PTR c, DWORD_PTR d)                { FORWARD(mixerMessage, 0, (a,b,c,d)); }
    WINMMAPI MMRESULT WINAPI mixerGetDevCapsA(UINT_PTR a, LPMIXERCAPSA b, UINT c)                   { FORWARD(mixerGetDevCapsA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mixerGetDevCapsW(UINT_PTR a, LPMIXERCAPSW b, UINT c)                   { FORWARD(mixerGetDevCapsW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mixerGetID(HMIXEROBJ a, UINT* b, DWORD c)                              { FORWARD(mixerGetID, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mixerGetLineInfoA(HMIXEROBJ a, LPMIXERLINEA b, DWORD c)                { FORWARD(mixerGetLineInfoA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mixerGetLineInfoW(HMIXEROBJ a, LPMIXERLINEW b, DWORD c)                { FORWARD(mixerGetLineInfoW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mixerGetLineControlsA(HMIXEROBJ a, LPMIXERLINECONTROLSA b, DWORD c)    { FORWARD(mixerGetLineControlsA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mixerGetLineControlsW(HMIXEROBJ a, LPMIXERLINECONTROLSW b, DWORD c)    { FORWARD(mixerGetLineControlsW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mixerGetControlDetailsA(HMIXEROBJ a, LPMIXERCONTROLDETAILS b, DWORD c) { FORWARD(mixerGetControlDetailsA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mixerGetControlDetailsW(HMIXEROBJ a, LPMIXERCONTROLDETAILS b, DWORD c) { FORWARD(mixerGetControlDetailsW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mixerSetControlDetails(HMIXEROBJ a, LPMIXERCONTROLDETAILS b, DWORD c)  { FORWARD(mixerSetControlDetails, MMSYSERR_NOTSUPPORTED, (a,b,c)); }

    WINMMAPI MMRESULT WINAPI joyGetDevCapsA(UINT_PTR a, LPJOYCAPSA b, UINT c)                       { FORWARD(joyGetDevCapsA, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI joyGetDevCapsW(UINT_PTR a, LPJOYCAPSW b, UINT c)                       { FORWARD(joyGetDevCapsW, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI UINT     WINAPI joyGetNumDevs()                                                          { FORWARD(joyGetNumDevs, 0, ()); }
    WINMMAPI MMRESULT WINAPI joyGetPos(UINT a, LPJOYINFO b)                                         { FORWARD(joyGetPos, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI joyGetPosEx(UINT a, LPJOYINFOEX b)                                     { FORWARD(joyGetPosEx, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI joyGetThreshold(UINT a, LPUINT b)                                      { FORWARD(joyGetThreshold, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI joyReleaseCapture(UINT a)                                               { FORWARD(joyReleaseCapture, MMSYSERR_NOTSUPPORTED, (a)); }
    WINMMAPI MMRESULT WINAPI joySetCapture(HWND a, UINT b, UINT c, BOOL d)                          { FORWARD(joySetCapture, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }
    WINMMAPI MMRESULT WINAPI joySetThreshold(UINT a, UINT b)                                        { FORWARD(joySetThreshold, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI joyConfigChanged(DWORD a)                                               { FORWARD(joyConfigChanged, MMSYSERR_NOTSUPPORTED, (a)); }

    WINMMAPI UINT  WINAPI mmsystemGetVersion()         { FORWARD(mmsystemGetVersion, 0, ()); }

    WINMMAPI HMMIO WINAPI mmioOpenA(LPSTR a, LPMMIOINFO b, DWORD c)                                  { FORWARD(mmioOpenA, nullptr, (a,b,c)); }
    WINMMAPI HMMIO WINAPI mmioOpenW(LPWSTR a, LPMMIOINFO b, DWORD c)                                 { FORWARD(mmioOpenW, nullptr, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mmioClose(HMMIO a, UINT b)                                             { FORWARD(mmioClose, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI LONG   WINAPI mmioRead(HMMIO a, HPSTR b, LONG c)                                       { FORWARD(mmioRead, -1, (a,b,c)); }
    WINMMAPI LONG   WINAPI mmioWrite(HMMIO a, const char* b, LONG c)                                { FORWARD(mmioWrite, -1, (a,b,c)); }
    WINMMAPI LONG   WINAPI mmioSeek(HMMIO a, LONG b, int c)                                         { FORWARD(mmioSeek, -1, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mmioGetInfo(HMMIO a, LPMMIOINFO b, UINT c)                             { FORWARD(mmioGetInfo, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mmioSetInfo(HMMIO a, LPCMMIOINFO b, UINT c)                            { FORWARD(mmioSetInfo, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mmioSetBuffer(HMMIO a, LPSTR b, LONG c, UINT d)                        { FORWARD(mmioSetBuffer, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }
    WINMMAPI MMRESULT WINAPI mmioFlush(HMMIO a, UINT b)                                             { FORWARD(mmioFlush, MMSYSERR_NOTSUPPORTED, (a,b)); }
    WINMMAPI MMRESULT WINAPI mmioAdvance(HMMIO a, LPMMIOINFO b, UINT c)                             { FORWARD(mmioAdvance, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mmioDescend(HMMIO a, LPMMCKINFO b, const MMCKINFO* c, UINT d)          { FORWARD(mmioDescend, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }
    WINMMAPI MMRESULT WINAPI mmioAscend(HMMIO a, LPMMCKINFO b, UINT c)                              { FORWARD(mmioAscend, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mmioCreateChunk(HMMIO a, LPMMCKINFO b, UINT c)                         { FORWARD(mmioCreateChunk, MMSYSERR_NOTSUPPORTED, (a,b,c)); }
    WINMMAPI MMRESULT WINAPI mmioRenameA(LPCSTR a, LPCSTR b, const MMIOINFO* c, DWORD d)            { FORWARD(mmioRenameA, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }
    WINMMAPI MMRESULT WINAPI mmioRenameW(LPCWSTR a, LPCWSTR b, const MMIOINFO* c, DWORD d)         { FORWARD(mmioRenameW, MMSYSERR_NOTSUPPORTED, (a,b,c,d)); }
    WINMMAPI LRESULT  WINAPI mmioSendMessage(HMMIO a, UINT b, LPARAM c, LPARAM d)                   { FORWARD(mmioSendMessage, 0, (a,b,c,d)); }
    WINMMAPI LPMMIOPROC WINAPI mmioInstallIOProcA(FOURCC a, LPMMIOPROC b, DWORD c)                  { FORWARD(mmioInstallIOProcA, nullptr, (a,b,c)); }
    WINMMAPI LPMMIOPROC WINAPI mmioInstallIOProcW(FOURCC a, LPMMIOPROC b, DWORD c)                  { FORWARD(mmioInstallIOProcW, nullptr, (a,b,c)); }
    WINMMAPI FOURCC WINAPI mmioStringToFOURCCA(LPCSTR a, UINT b)                                    { FORWARD(mmioStringToFOURCCA, 0, (a,b)); }
    WINMMAPI FOURCC WINAPI mmioStringToFOURCCW(LPCWSTR a, UINT b)                                   { FORWARD(mmioStringToFOURCCW, 0, (a,b)); }

    WINMMAPI HDRVR  WINAPI OpenDriver(LPCWSTR a, LPCWSTR b, LPARAM c)                               { FORWARD(OpenDriver, nullptr, (a,b,c)); }
    WINMMAPI LRESULT WINAPI CloseDriver(HDRVR a, LONG b, LONG c)                                    { FORWARD(CloseDriver, 0, (a,b,c)); }
    WINMMAPI LRESULT WINAPI SendDriverMessage(HDRVR a, UINT b, LPARAM c, LPARAM d)                  { FORWARD(SendDriverMessage, 0, (a,b,c,d)); }
    WINMMAPI HMODULE WINAPI DrvGetModuleHandle(HDRVR a)                                              { FORWARD(DrvGetModuleHandle, nullptr, (a)); }
    WINMMAPI HMODULE WINAPI GetDriverModuleHandle(HDRVR a)                                           { FORWARD(GetDriverModuleHandle, nullptr, (a)); }
    WINMMAPI LRESULT WINAPI DefDriverProc(DWORD_PTR a, HDRVR b, UINT c, LPARAM d, LPARAM e)         { FORWARD(DefDriverProc, 0, (a,b,c,d,e)); }
    WINMMAPI BOOL    WINAPI DriverCallback(DWORD_PTR a, DWORD b, HDRVR c, DWORD d, DWORD_PTR e, DWORD_PTR f, DWORD_PTR g) { FORWARD(DriverCallback, FALSE, (a,b,c,d,e,f,g)); }
    WINMMAPI BOOL    WINAPI NotifyCallbackData(HDRVR a, UINT b, DWORD_PTR c, DWORD_PTR d, DWORD_PTR e) { FORWARD(NotifyCallbackData, FALSE, (a,b,c,d,e)); }

    // Non-MMSYSTEM legacy/thunk exports in WINMM that are not declared in mmsystem.h.
    // Use naked tail-jumps to preserve unknown calling conventions/argument shapes.
    FORWARD_NAKED(WOW32DriverCallback)
    FORWARD_NAKED(WOW32ResolveMultiMediaHandle)
    FORWARD_NAKED(WOWAppExit)
    FORWARD_NAKED(aux32Message)
    FORWARD_NAKED(joy32Message)
    FORWARD_NAKED(mci32Message)
    WINMMAPI BOOL WINAPI mciDriverNotify_proxy(HANDLE a, MCIDEVICEID b, UINT c)           { FORWARD(mciDriverNotify, FALSE, (a,b,c)); }
    WINMMAPI UINT WINAPI mciDriverYield(MCIDEVICEID a)                                    { FORWARD(mciDriverYield, 0, (a)); }
    WINMMAPI BOOL WINAPI mciFreeCommandResource(UINT a)                                   { FORWARD(mciFreeCommandResource, FALSE, (a)); }
    WINMMAPI UINT WINAPI mciLoadCommandResource_proxy(HANDLE a, LPCWSTR b, UINT c)        { FORWARD(mciLoadCommandResource, 0, (a,b,c)); }
    FORWARD_NAKED(mid32Message)
    WINMMAPI UINT WINAPI mmDrvInstall_proxy(HDRVR a, LPCWSTR b, DRIVERMSGPROC c, UINT d)  { FORWARD(mmDrvInstall, 0, (a,b,c,d)); }
    FORWARD_NAKED(mmGetCurrentTask)
    FORWARD_NAKED(mmTaskBlock)
    FORWARD_NAKED(mmTaskCreate)
    FORWARD_NAKED(mmTaskSignal)
    FORWARD_NAKED(mmTaskYield)
    FORWARD_NAKED(mod32Message)
    FORWARD_NAKED(mxd32Message)
    FORWARD_NAKED(tid32Message)
    FORWARD_NAKED(wid32Message)
    FORWARD_NAKED(wod32Message)
} // extern "C"

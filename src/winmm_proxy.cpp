// winmm_proxy.cpp
// BZR Open Shim - proxy loader for the real winmm.dll
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT

#include "winmm_proxy.h"
#include "bzr_hooks.h"
#include "shim_log.h"
#include <cstdio>

HMODULE g_hRealWinmm = nullptr;

namespace
{
    void LogHudBridgeCall(const char* functionName, const char* spriteName)
    {
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Info,
            "hudbridge",
            "%s sprite=%s",
            functionName ? functionName : "<null>",
            spriteName ? spriteName : "<null>");
    }

    void LogHudBridgeResult(const char* functionName, const char* spriteName, BOOL result)
    {
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Info,
            "hudbridge",
            "%s sprite=%s => %s",
            functionName ? functionName : "<null>",
            spriteName ? spriteName : "<null>",
            result ? "true" : "false");
    }
}

extern "C" WINMMAPI BOOL WINAPI OpenShimSetUnderAttackAlertMode(int mode)
{
    return BZROpenShim::SetUnderAttackAlertModeFromBridge(mode) ? TRUE : FALSE;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimSetTargetReticlePopupMode(int mode)
{
    return BZROpenShim::SetTargetReticlePopupModeFromBridge(mode) ? TRUE : FALSE;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimSetBomberAiRangeEnabled(BOOL enabled)
{
    return BZROpenShim::SetBomberAiRangeEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimSetHowitzerVolleyEnabled(BOOL enabled)
{
    return BZROpenShim::SetHowitzerVolleyEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimSetWeaponMaskCarrierBiasEnabled(BOOL enabled)
{
    return BZROpenShim::SetWeaponMaskCarrierBiasEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimSetAiOdfGameplayTuningEnabled(BOOL enabled)
{
    return BZROpenShim::SetAiOdfGameplayTuningEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimSetTurretAimPitchEnabled(BOOL enabled)
{
    return BZROpenShim::SetTurretAimPitchEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimSetAttackRevealEnabled(BOOL enabled)
{
    return BZROpenShim::SetAttackRevealEnabledFromBridge(enabled != FALSE) ? TRUE : FALSE;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimResetMissionHookOverrides()
{
    return BZROpenShim::ResetMissionHookOverridesFromBridge() ? TRUE : FALSE;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimGetHudSpriteRect(LPCSTR name, int* x, int* y, int* w, int* h)
{
    LogHudBridgeCall("OpenShimGetHudSpriteRect", name);
    const BOOL result = BZROpenShim::GetHudSpriteRectFromBridge(name, x, y, w, h) ? TRUE : FALSE;
    if (result)
    {
        BZROpenShim::LogShimA(
            BZROpenShim::LogLevel::Info,
            "hudbridge",
            "OpenShimGetHudSpriteRect sprite=%s => true rect=(%d,%d,%d,%d)",
            name ? name : "<null>",
            x ? *x : 0,
            y ? *y : 0,
            w ? *w : 0,
            h ? *h : 0);
    }
    else
    {
        LogHudBridgeResult("OpenShimGetHudSpriteRect", name, result);
    }
    return result;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimSetHudSpriteRect(LPCSTR name, int x, int y, int w, int h)
{
    BZROpenShim::LogShimA(
        BZROpenShim::LogLevel::Info,
        "hudbridge",
        "OpenShimSetHudSpriteRect sprite=%s rect=(%d,%d,%d,%d)",
        name ? name : "<null>",
        x,
        y,
        w,
        h);
    const BOOL result = BZROpenShim::SetHudSpriteRectFromBridge(name, x, y, w, h) ? TRUE : FALSE;
    LogHudBridgeResult("OpenShimSetHudSpriteRect", name, result);
    return result;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimSetHudSpriteVisible(LPCSTR name, BOOL visible)
{
    BZROpenShim::LogShimA(
        BZROpenShim::LogLevel::Info,
        "hudbridge",
        "OpenShimSetHudSpriteVisible sprite=%s visible=%s",
        name ? name : "<null>",
        visible ? "true" : "false");
    const BOOL result = BZROpenShim::SetHudSpriteVisibleFromBridge(name, visible != FALSE) ? TRUE : FALSE;
    LogHudBridgeResult("OpenShimSetHudSpriteVisible", name, result);
    return result;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimRestoreHudSprite(LPCSTR name)
{
    LogHudBridgeCall("OpenShimRestoreHudSprite", name);
    const BOOL result = BZROpenShim::RestoreHudSpriteFromBridge(name) ? TRUE : FALSE;
    LogHudBridgeResult("OpenShimRestoreHudSprite", name, result);
    return result;
}

extern "C" WINMMAPI BOOL WINAPI OpenShimRestoreAllHudSprites()
{
    BZROpenShim::LogShimA(
        BZROpenShim::LogLevel::Info,
        "hudbridge",
        "OpenShimRestoreAllHudSprites");
    const BOOL result = BZROpenShim::RestoreAllHudSpritesFromBridge() ? TRUE : FALSE;
    BZROpenShim::LogShimA(
        BZROpenShim::LogLevel::Info,
        "hudbridge",
        "OpenShimRestoreAllHudSprites => %s",
        result ? "true" : "false");
    return result;
}

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
#define FORWARD(name) \
    static decltype(&::name) _fn_##name = nullptr; \
    if (!_fn_##name) _fn_##name = reinterpret_cast<decltype(&::name)>(ResolveRealWinmmProc(#name)); \
    return _fn_##name

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
// The complete export list was extracted from winmm.bin via Ghidra.
// ---------------------------------------------------------------------------

extern "C"
{
    WINMMAPI MCIERROR  WINAPI mciSendCommandA(MCIDEVICEID a, UINT b, DWORD_PTR c, DWORD_PTR d)      { FORWARD(mciSendCommandA)(a,b,c,d); }
    WINMMAPI MCIERROR  WINAPI mciSendCommandW(MCIDEVICEID a, UINT b, DWORD_PTR c, DWORD_PTR d)      { FORWARD(mciSendCommandW)(a,b,c,d); }
    WINMMAPI MCIERROR  WINAPI mciSendStringA(LPCSTR a, LPSTR b, UINT c, HWND d)                    { FORWARD(mciSendStringA)(a,b,c,d); }
    WINMMAPI MCIERROR  WINAPI mciSendStringW(LPCWSTR a, LPWSTR b, UINT c, HWND d)                  { FORWARD(mciSendStringW)(a,b,c,d); }
    WINMMAPI BOOL      WINAPI mciGetErrorStringA(MCIERROR a, LPSTR b, UINT c)                       { FORWARD(mciGetErrorStringA)(a,b,c); }
    WINMMAPI BOOL      WINAPI mciGetErrorStringW(MCIERROR a, LPWSTR b, UINT c)                      { FORWARD(mciGetErrorStringW)(a,b,c); }
    WINMMAPI BOOL      WINAPI mciSetYieldProc(MCIDEVICEID a, YIELDPROC b, DWORD c)                  { FORWARD(mciSetYieldProc)(a,b,c); }
    WINMMAPI HTASK     WINAPI mciGetCreatorTask(MCIDEVICEID a)                                       { FORWARD(mciGetCreatorTask)(a); }
    WINMMAPI YIELDPROC WINAPI mciGetYieldProc(MCIDEVICEID a, LPDWORD b)                             { FORWARD(mciGetYieldProc)(a,b); }
    WINMMAPI BOOL      WINAPI mciExecute(LPCSTR a)                                                   { FORWARD(mciExecute)(a); }
    WINMMAPI MCIDEVICEID WINAPI mciGetDeviceIDA(LPCSTR a)                                            { FORWARD(mciGetDeviceIDA)(a); }
    WINMMAPI MCIDEVICEID WINAPI mciGetDeviceIDW(LPCWSTR a)                                           { FORWARD(mciGetDeviceIDW)(a); }
    WINMMAPI MCIDEVICEID WINAPI mciGetDeviceIDFromElementIDA(DWORD a, LPCSTR b)                      { FORWARD(mciGetDeviceIDFromElementIDA)(a,b); }
    WINMMAPI MCIDEVICEID WINAPI mciGetDeviceIDFromElementIDW(DWORD a, LPCWSTR b)                     { FORWARD(mciGetDeviceIDFromElementIDW)(a,b); }
    WINMMAPI DWORD_PTR WINAPI mciGetDriverData(MCIDEVICEID a)                                        { FORWARD(mciGetDriverData)(a); }
    WINMMAPI BOOL      WINAPI mciSetDriverData(MCIDEVICEID a, DWORD_PTR b)                           { FORWARD(mciSetDriverData)(a,b); }

    WINMMAPI BOOL  WINAPI PlaySoundA(LPCSTR a, HMODULE b, DWORD c)                                  { FORWARD(PlaySoundA)(a,b,c); }
    WINMMAPI BOOL  WINAPI PlaySoundW(LPCWSTR a, HMODULE b, DWORD c)                                 { FORWARD(PlaySoundW)(a,b,c); }
    WINMMAPI BOOL  WINAPI sndPlaySoundA(LPCSTR a, UINT b)                                            { FORWARD(sndPlaySoundA)(a,b); }
    WINMMAPI BOOL  WINAPI sndPlaySoundW(LPCWSTR a, UINT b)                                           { FORWARD(sndPlaySoundW)(a,b); }

    WINMMAPI DWORD WINAPI timeGetTime_fwd()                                                        { FORWARD(timeGetTime)(); } // see exports .def

    WINMMAPI MMRESULT WINAPI timeBeginPeriod(UINT a)   { FORWARD(timeBeginPeriod)(a); }
    WINMMAPI MMRESULT WINAPI timeEndPeriod(UINT a)     { FORWARD(timeEndPeriod)(a); }
    WINMMAPI MMRESULT WINAPI timeGetDevCaps(LPTIMECAPS a, UINT b)  { FORWARD(timeGetDevCaps)(a,b); }
    WINMMAPI MMRESULT WINAPI timeGetSystemTime(LPMMTIME a, UINT b) { FORWARD(timeGetSystemTime)(a,b); }
    WINMMAPI MMRESULT WINAPI timeKillEvent(UINT a)     { FORWARD(timeKillEvent)(a); }
    WINMMAPI MMRESULT WINAPI timeSetEvent(UINT a, UINT b, LPTIMECALLBACK c, DWORD_PTR d, UINT e) { FORWARD(timeSetEvent)(a,b,c,d,e); }

    WINMMAPI MMRESULT WINAPI waveOutOpen(LPHWAVEOUT a, UINT b, LPCWAVEFORMATEX c, DWORD_PTR d, DWORD_PTR e, DWORD f) { FORWARD(waveOutOpen)(a,b,c,d,e,f); }
    WINMMAPI MMRESULT WINAPI waveOutClose(HWAVEOUT a)  { FORWARD(waveOutClose)(a); }
    WINMMAPI MMRESULT WINAPI waveOutWrite(HWAVEOUT a, LPWAVEHDR b, UINT c)                          { FORWARD(waveOutWrite)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveOutPause(HWAVEOUT a)  { FORWARD(waveOutPause)(a); }
    WINMMAPI MMRESULT WINAPI waveOutRestart(HWAVEOUT a){ FORWARD(waveOutRestart)(a); }
    WINMMAPI MMRESULT WINAPI waveOutReset(HWAVEOUT a)  { FORWARD(waveOutReset)(a); }
    WINMMAPI MMRESULT WINAPI waveOutBreakLoop(HWAVEOUT a){ FORWARD(waveOutBreakLoop)(a); }
    WINMMAPI MMRESULT WINAPI waveOutPrepareHeader(HWAVEOUT a, LPWAVEHDR b, UINT c)                  { FORWARD(waveOutPrepareHeader)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveOutUnprepareHeader(HWAVEOUT a, LPWAVEHDR b, UINT c)                { FORWARD(waveOutUnprepareHeader)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveOutGetPosition(HWAVEOUT a, LPMMTIME b, UINT c)                     { FORWARD(waveOutGetPosition)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveOutGetPitch(HWAVEOUT a, LPDWORD b)                                 { FORWARD(waveOutGetPitch)(a,b); }
    WINMMAPI MMRESULT WINAPI waveOutSetPitch(HWAVEOUT a, DWORD b)                                   { FORWARD(waveOutSetPitch)(a,b); }
    WINMMAPI MMRESULT WINAPI waveOutGetPlaybackRate(HWAVEOUT a, LPDWORD b)                          { FORWARD(waveOutGetPlaybackRate)(a,b); }
    WINMMAPI MMRESULT WINAPI waveOutSetPlaybackRate(HWAVEOUT a, DWORD b)                            { FORWARD(waveOutSetPlaybackRate)(a,b); }
    WINMMAPI MMRESULT WINAPI waveOutGetVolume(HWAVEOUT a, LPDWORD b)                                { FORWARD(waveOutGetVolume)(a,b); }
    WINMMAPI MMRESULT WINAPI waveOutSetVolume(HWAVEOUT a, DWORD b)                                  { FORWARD(waveOutSetVolume)(a,b); }
    WINMMAPI MMRESULT WINAPI waveOutGetErrorTextA(MMRESULT a, LPSTR b, UINT c)                      { FORWARD(waveOutGetErrorTextA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveOutGetErrorTextW(MMRESULT a, LPWSTR b, UINT c)                     { FORWARD(waveOutGetErrorTextW)(a,b,c); }
    WINMMAPI UINT     WINAPI waveOutGetNumDevs()                                                      { FORWARD(waveOutGetNumDevs)(); }
    WINMMAPI MMRESULT WINAPI waveOutGetDevCapsA(UINT_PTR a, LPWAVEOUTCAPSA b, UINT c)               { FORWARD(waveOutGetDevCapsA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveOutGetDevCapsW(UINT_PTR a, LPWAVEOUTCAPSW b, UINT c)               { FORWARD(waveOutGetDevCapsW)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveOutGetID(HWAVEOUT a, LPUINT b)                                     { FORWARD(waveOutGetID)(a,b); }
    WINMMAPI MMRESULT WINAPI waveOutMessage(HWAVEOUT a, UINT b, DWORD_PTR c, DWORD_PTR d)           { FORWARD(waveOutMessage)(a,b,c,d); }

    WINMMAPI MMRESULT WINAPI waveInOpen(LPHWAVEIN a, UINT b, LPCWAVEFORMATEX c, DWORD_PTR d, DWORD_PTR e, DWORD f) { FORWARD(waveInOpen)(a,b,c,d,e,f); }
    WINMMAPI MMRESULT WINAPI waveInClose(HWAVEIN a)    { FORWARD(waveInClose)(a); }
    WINMMAPI MMRESULT WINAPI waveInAddBuffer(HWAVEIN a, LPWAVEHDR b, UINT c)                        { FORWARD(waveInAddBuffer)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveInStart(HWAVEIN a)    { FORWARD(waveInStart)(a); }
    WINMMAPI MMRESULT WINAPI waveInStop(HWAVEIN a)     { FORWARD(waveInStop)(a); }
    WINMMAPI MMRESULT WINAPI waveInReset(HWAVEIN a)    { FORWARD(waveInReset)(a); }
    WINMMAPI MMRESULT WINAPI waveInPrepareHeader(HWAVEIN a, LPWAVEHDR b, UINT c)                    { FORWARD(waveInPrepareHeader)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveInUnprepareHeader(HWAVEIN a, LPWAVEHDR b, UINT c)                  { FORWARD(waveInUnprepareHeader)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveInGetPosition(HWAVEIN a, LPMMTIME b, UINT c)                       { FORWARD(waveInGetPosition)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveInGetErrorTextA(MMRESULT a, LPSTR b, UINT c)                       { FORWARD(waveInGetErrorTextA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveInGetErrorTextW(MMRESULT a, LPWSTR b, UINT c)                      { FORWARD(waveInGetErrorTextW)(a,b,c); }
    WINMMAPI UINT     WINAPI waveInGetNumDevs()                                                       { FORWARD(waveInGetNumDevs)(); }
    WINMMAPI MMRESULT WINAPI waveInGetDevCapsA(UINT_PTR a, LPWAVEINCAPSA b, UINT c)                 { FORWARD(waveInGetDevCapsA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveInGetDevCapsW(UINT_PTR a, LPWAVEINCAPSW b, UINT c)                 { FORWARD(waveInGetDevCapsW)(a,b,c); }
    WINMMAPI MMRESULT WINAPI waveInGetID(HWAVEIN a, LPUINT b)                                       { FORWARD(waveInGetID)(a,b); }
    WINMMAPI MMRESULT WINAPI waveInMessage(HWAVEIN a, UINT b, DWORD_PTR c, DWORD_PTR d)             { FORWARD(waveInMessage)(a,b,c,d); }

    WINMMAPI MMRESULT WINAPI midiOutOpen(LPHMIDIOUT a, UINT b, DWORD_PTR c, DWORD_PTR d, DWORD e)   { FORWARD(midiOutOpen)(a,b,c,d,e); }
    WINMMAPI MMRESULT WINAPI midiOutClose(HMIDIOUT a)  { FORWARD(midiOutClose)(a); }
    WINMMAPI MMRESULT WINAPI midiOutShortMsg(HMIDIOUT a, DWORD b)                                    { FORWARD(midiOutShortMsg)(a,b); }
    WINMMAPI MMRESULT WINAPI midiOutLongMsg(HMIDIOUT a, LPMIDIHDR b, UINT c)                        { FORWARD(midiOutLongMsg)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiOutPrepareHeader(HMIDIOUT a, LPMIDIHDR b, UINT c)                  { FORWARD(midiOutPrepareHeader)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiOutUnprepareHeader(HMIDIOUT a, LPMIDIHDR b, UINT c)                { FORWARD(midiOutUnprepareHeader)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiOutReset(HMIDIOUT a)  { FORWARD(midiOutReset)(a); }
    WINMMAPI MMRESULT WINAPI midiOutGetVolume(HMIDIOUT a, LPDWORD b)                                { FORWARD(midiOutGetVolume)(a,b); }
    WINMMAPI MMRESULT WINAPI midiOutSetVolume(HMIDIOUT a, DWORD b)                                  { FORWARD(midiOutSetVolume)(a,b); }
    WINMMAPI MMRESULT WINAPI midiOutCacheDrumPatches(HMIDIOUT a, UINT b, WORD* c, UINT d)           { FORWARD(midiOutCacheDrumPatches)(a,b,c,d); }
    WINMMAPI MMRESULT WINAPI midiOutCachePatches(HMIDIOUT a, UINT b, WORD* c, UINT d)               { FORWARD(midiOutCachePatches)(a,b,c,d); }
    WINMMAPI MMRESULT WINAPI midiOutGetErrorTextA(MMRESULT a, LPSTR b, UINT c)                      { FORWARD(midiOutGetErrorTextA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiOutGetErrorTextW(MMRESULT a, LPWSTR b, UINT c)                     { FORWARD(midiOutGetErrorTextW)(a,b,c); }
    WINMMAPI UINT     WINAPI midiOutGetNumDevs()                                                      { FORWARD(midiOutGetNumDevs)(); }
    WINMMAPI MMRESULT WINAPI midiOutGetDevCapsA(UINT_PTR a, LPMIDIOUTCAPSA b, UINT c)               { FORWARD(midiOutGetDevCapsA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiOutGetDevCapsW(UINT_PTR a, LPMIDIOUTCAPSW b, UINT c)               { FORWARD(midiOutGetDevCapsW)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiOutGetID(HMIDIOUT a, LPUINT b)                                     { FORWARD(midiOutGetID)(a,b); }
    WINMMAPI MMRESULT WINAPI midiOutMessage(HMIDIOUT a, UINT b, DWORD_PTR c, DWORD_PTR d)           { FORWARD(midiOutMessage)(a,b,c,d); }

    WINMMAPI MMRESULT WINAPI midiInOpen(LPHMIDIIN a, UINT b, DWORD_PTR c, DWORD_PTR d, DWORD e)     { FORWARD(midiInOpen)(a,b,c,d,e); }
    WINMMAPI MMRESULT WINAPI midiInClose(HMIDIIN a)    { FORWARD(midiInClose)(a); }
    WINMMAPI MMRESULT WINAPI midiInAddBuffer(HMIDIIN a, LPMIDIHDR b, UINT c)                        { FORWARD(midiInAddBuffer)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiInStart(HMIDIIN a)    { FORWARD(midiInStart)(a); }
    WINMMAPI MMRESULT WINAPI midiInStop(HMIDIIN a)     { FORWARD(midiInStop)(a); }
    WINMMAPI MMRESULT WINAPI midiInReset(HMIDIIN a)    { FORWARD(midiInReset)(a); }
    WINMMAPI MMRESULT WINAPI midiInPrepareHeader(HMIDIIN a, LPMIDIHDR b, UINT c)                    { FORWARD(midiInPrepareHeader)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiInUnprepareHeader(HMIDIIN a, LPMIDIHDR b, UINT c)                  { FORWARD(midiInUnprepareHeader)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiInGetErrorTextA(MMRESULT a, LPSTR b, UINT c)                       { FORWARD(midiInGetErrorTextA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiInGetErrorTextW(MMRESULT a, LPWSTR b, UINT c)                      { FORWARD(midiInGetErrorTextW)(a,b,c); }
    WINMMAPI UINT     WINAPI midiInGetNumDevs()                                                       { FORWARD(midiInGetNumDevs)(); }
    WINMMAPI MMRESULT WINAPI midiInGetDevCapsA(UINT_PTR a, LPMIDIINCAPSA b, UINT c)                 { FORWARD(midiInGetDevCapsA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiInGetDevCapsW(UINT_PTR a, LPMIDIINCAPSW b, UINT c)                 { FORWARD(midiInGetDevCapsW)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiInGetID(HMIDIIN a, LPUINT b)                                       { FORWARD(midiInGetID)(a,b); }
    WINMMAPI MMRESULT WINAPI midiInMessage(HMIDIIN a, UINT b, DWORD_PTR c, DWORD_PTR d)             { FORWARD(midiInMessage)(a,b,c,d); }
    WINMMAPI MMRESULT WINAPI midiConnect(HMIDI a, HMIDIOUT b, LPVOID c)                             { FORWARD(midiConnect)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiDisconnect(HMIDI a, HMIDIOUT b, LPVOID c)                          { FORWARD(midiDisconnect)(a,b,c); }

    WINMMAPI MMRESULT WINAPI midiStreamOpen(LPHMIDISTRM a, LPUINT b, DWORD c, DWORD_PTR d, DWORD_PTR e, DWORD f) { FORWARD(midiStreamOpen)(a,b,c,d,e,f); }
    WINMMAPI MMRESULT WINAPI midiStreamClose(HMIDISTRM a) { FORWARD(midiStreamClose)(a); }
    WINMMAPI MMRESULT WINAPI midiStreamOut(HMIDISTRM a, LPMIDIHDR b, UINT c)                        { FORWARD(midiStreamOut)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiStreamPause(HMIDISTRM a) { FORWARD(midiStreamPause)(a); }
    WINMMAPI MMRESULT WINAPI midiStreamPosition(HMIDISTRM a, LPMMTIME b, UINT c)                    { FORWARD(midiStreamPosition)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiStreamProperty(HMIDISTRM a, LPBYTE b, DWORD c)                     { FORWARD(midiStreamProperty)(a,b,c); }
    WINMMAPI MMRESULT WINAPI midiStreamRestart(HMIDISTRM a) { FORWARD(midiStreamRestart)(a); }
    WINMMAPI MMRESULT WINAPI midiStreamStop(HMIDISTRM a)  { FORWARD(midiStreamStop)(a); }

    WINMMAPI UINT  WINAPI auxGetNumDevs()              { FORWARD(auxGetNumDevs)(); }
    WINMMAPI MMRESULT WINAPI auxGetDevCapsA(UINT_PTR a, LPAUXCAPSA b, UINT c)                       { FORWARD(auxGetDevCapsA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI auxGetDevCapsW(UINT_PTR a, LPAUXCAPSW b, UINT c)                       { FORWARD(auxGetDevCapsW)(a,b,c); }
    WINMMAPI MMRESULT  WINAPI auxGetVolume(UINT a, LPDWORD b)                                        { FORWARD(auxGetVolume)(a,b); }
    WINMMAPI MMRESULT  WINAPI auxSetVolume(UINT a, DWORD b)                                          { FORWARD(auxSetVolume)(a,b); }
    WINMMAPI MMRESULT  WINAPI auxOutMessage(UINT a, UINT b, DWORD_PTR c, DWORD_PTR d)                 { FORWARD(auxOutMessage)(a,b,c,d); }

    WINMMAPI UINT  WINAPI mixerGetNumDevs()            { FORWARD(mixerGetNumDevs)(); }
    WINMMAPI MMRESULT WINAPI mixerOpen(LPHMIXER a, UINT b, DWORD_PTR c, DWORD_PTR d, DWORD e)       { FORWARD(mixerOpen)(a,b,c,d,e); }
    WINMMAPI MMRESULT WINAPI mixerClose(HMIXER a)      { FORWARD(mixerClose)(a); }
    WINMMAPI DWORD   WINAPI mixerMessage(HMIXER a, UINT b, DWORD_PTR c, DWORD_PTR d)                { FORWARD(mixerMessage)(a,b,c,d); }
    WINMMAPI MMRESULT WINAPI mixerGetDevCapsA(UINT_PTR a, LPMIXERCAPSA b, UINT c)                   { FORWARD(mixerGetDevCapsA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mixerGetDevCapsW(UINT_PTR a, LPMIXERCAPSW b, UINT c)                   { FORWARD(mixerGetDevCapsW)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mixerGetID(HMIXEROBJ a, UINT* b, DWORD c)                              { FORWARD(mixerGetID)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mixerGetLineInfoA(HMIXEROBJ a, LPMIXERLINEA b, DWORD c)                { FORWARD(mixerGetLineInfoA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mixerGetLineInfoW(HMIXEROBJ a, LPMIXERLINEW b, DWORD c)                { FORWARD(mixerGetLineInfoW)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mixerGetLineControlsA(HMIXEROBJ a, LPMIXERLINECONTROLSA b, DWORD c)    { FORWARD(mixerGetLineControlsA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mixerGetLineControlsW(HMIXEROBJ a, LPMIXERLINECONTROLSW b, DWORD c)    { FORWARD(mixerGetLineControlsW)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mixerGetControlDetailsA(HMIXEROBJ a, LPMIXERCONTROLDETAILS b, DWORD c) { FORWARD(mixerGetControlDetailsA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mixerGetControlDetailsW(HMIXEROBJ a, LPMIXERCONTROLDETAILS b, DWORD c) { FORWARD(mixerGetControlDetailsW)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mixerSetControlDetails(HMIXEROBJ a, LPMIXERCONTROLDETAILS b, DWORD c)  { FORWARD(mixerSetControlDetails)(a,b,c); }

    WINMMAPI MMRESULT WINAPI joyGetDevCapsA(UINT_PTR a, LPJOYCAPSA b, UINT c)                       { FORWARD(joyGetDevCapsA)(a,b,c); }
    WINMMAPI MMRESULT WINAPI joyGetDevCapsW(UINT_PTR a, LPJOYCAPSW b, UINT c)                       { FORWARD(joyGetDevCapsW)(a,b,c); }
    WINMMAPI UINT     WINAPI joyGetNumDevs()                                                          { FORWARD(joyGetNumDevs)(); }
    WINMMAPI MMRESULT WINAPI joyGetPos(UINT a, LPJOYINFO b)                                         { FORWARD(joyGetPos)(a,b); }
    WINMMAPI MMRESULT WINAPI joyGetPosEx(UINT a, LPJOYINFOEX b)                                     { FORWARD(joyGetPosEx)(a,b); }
    WINMMAPI MMRESULT WINAPI joyGetThreshold(UINT a, LPUINT b)                                      { FORWARD(joyGetThreshold)(a,b); }
    WINMMAPI MMRESULT WINAPI joyReleaseCapture(UINT a)                                               { FORWARD(joyReleaseCapture)(a); }
    WINMMAPI MMRESULT WINAPI joySetCapture(HWND a, UINT b, UINT c, BOOL d)                          { FORWARD(joySetCapture)(a,b,c,d); }
    WINMMAPI MMRESULT WINAPI joySetThreshold(UINT a, UINT b)                                        { FORWARD(joySetThreshold)(a,b); }
    WINMMAPI MMRESULT WINAPI joyConfigChanged(DWORD a)                                               { FORWARD(joyConfigChanged)(a); }

    WINMMAPI UINT  WINAPI mmsystemGetVersion()         { FORWARD(mmsystemGetVersion)(); }

    WINMMAPI HMMIO WINAPI mmioOpenA(LPSTR a, LPMMIOINFO b, DWORD c)                                  { FORWARD(mmioOpenA)(a,b,c); }
    WINMMAPI HMMIO WINAPI mmioOpenW(LPWSTR a, LPMMIOINFO b, DWORD c)                                 { FORWARD(mmioOpenW)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mmioClose(HMMIO a, UINT b)                                             { FORWARD(mmioClose)(a,b); }
    WINMMAPI LONG   WINAPI mmioRead(HMMIO a, HPSTR b, LONG c)                                       { FORWARD(mmioRead)(a,b,c); }
    WINMMAPI LONG   WINAPI mmioWrite(HMMIO a, const char* b, LONG c)                                { FORWARD(mmioWrite)(a,b,c); }
    WINMMAPI LONG   WINAPI mmioSeek(HMMIO a, LONG b, int c)                                         { FORWARD(mmioSeek)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mmioGetInfo(HMMIO a, LPMMIOINFO b, UINT c)                             { FORWARD(mmioGetInfo)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mmioSetInfo(HMMIO a, LPCMMIOINFO b, UINT c)                            { FORWARD(mmioSetInfo)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mmioSetBuffer(HMMIO a, LPSTR b, LONG c, UINT d)                        { FORWARD(mmioSetBuffer)(a,b,c,d); }
    WINMMAPI MMRESULT WINAPI mmioFlush(HMMIO a, UINT b)                                             { FORWARD(mmioFlush)(a,b); }
    WINMMAPI MMRESULT WINAPI mmioAdvance(HMMIO a, LPMMIOINFO b, UINT c)                             { FORWARD(mmioAdvance)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mmioDescend(HMMIO a, LPMMCKINFO b, const MMCKINFO* c, UINT d)          { FORWARD(mmioDescend)(a,b,c,d); }
    WINMMAPI MMRESULT WINAPI mmioAscend(HMMIO a, LPMMCKINFO b, UINT c)                              { FORWARD(mmioAscend)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mmioCreateChunk(HMMIO a, LPMMCKINFO b, UINT c)                         { FORWARD(mmioCreateChunk)(a,b,c); }
    WINMMAPI MMRESULT WINAPI mmioRenameA(LPCSTR a, LPCSTR b, const MMIOINFO* c, DWORD d)            { FORWARD(mmioRenameA)(a,b,c,d); }
    WINMMAPI MMRESULT WINAPI mmioRenameW(LPCWSTR a, LPCWSTR b, const MMIOINFO* c, DWORD d)         { FORWARD(mmioRenameW)(a,b,c,d); }
    WINMMAPI LRESULT  WINAPI mmioSendMessage(HMMIO a, UINT b, LPARAM c, LPARAM d)                   { FORWARD(mmioSendMessage)(a,b,c,d); }
    WINMMAPI LPMMIOPROC WINAPI mmioInstallIOProcA(FOURCC a, LPMMIOPROC b, DWORD c)                  { FORWARD(mmioInstallIOProcA)(a,b,c); }
    WINMMAPI LPMMIOPROC WINAPI mmioInstallIOProcW(FOURCC a, LPMMIOPROC b, DWORD c)                  { FORWARD(mmioInstallIOProcW)(a,b,c); }
    WINMMAPI FOURCC WINAPI mmioStringToFOURCCA(LPCSTR a, UINT b)                                    { FORWARD(mmioStringToFOURCCA)(a,b); }
    WINMMAPI FOURCC WINAPI mmioStringToFOURCCW(LPCWSTR a, UINT b)                                   { FORWARD(mmioStringToFOURCCW)(a,b); }

    WINMMAPI HDRVR  WINAPI OpenDriver(LPCWSTR a, LPCWSTR b, LPARAM c)                               { FORWARD(OpenDriver)(a,b,c); }
    WINMMAPI LRESULT WINAPI CloseDriver(HDRVR a, LONG b, LONG c)                                    { FORWARD(CloseDriver)(a,b,c); }
    WINMMAPI LRESULT WINAPI SendDriverMessage(HDRVR a, UINT b, LPARAM c, LPARAM d)                  { FORWARD(SendDriverMessage)(a,b,c,d); }
    WINMMAPI HMODULE WINAPI DrvGetModuleHandle(HDRVR a)                                              { FORWARD(DrvGetModuleHandle)(a); }
    WINMMAPI HMODULE WINAPI GetDriverModuleHandle(HDRVR a)                                           { FORWARD(GetDriverModuleHandle)(a); }
    WINMMAPI LRESULT WINAPI DefDriverProc(DWORD_PTR a, HDRVR b, UINT c, LPARAM d, LPARAM e)         { FORWARD(DefDriverProc)(a,b,c,d,e); }
    WINMMAPI BOOL    WINAPI DriverCallback(DWORD_PTR a, DWORD b, HDRVR c, DWORD d, DWORD_PTR e, DWORD_PTR f, DWORD_PTR g) { FORWARD(DriverCallback)(a,b,c,d,e,f,g); }
    WINMMAPI BOOL    WINAPI NotifyCallbackData(HDRVR a, UINT b, DWORD_PTR c, DWORD_PTR d, DWORD_PTR e) { FORWARD(NotifyCallbackData)(a,b,c,d,e); }

    // Non-MMSYSTEM legacy/thunk exports in WINMM that are not declared in mmsystem.h.
    // Use naked tail-jumps to preserve unknown calling conventions/argument shapes.
    FORWARD_NAKED(WOW32DriverCallback)
    FORWARD_NAKED(WOW32ResolveMultiMediaHandle)
    FORWARD_NAKED(WOWAppExit)
    FORWARD_NAKED(aux32Message)
    FORWARD_NAKED(joy32Message)
    FORWARD_NAKED(mci32Message)
    WINMMAPI BOOL WINAPI mciDriverNotify_proxy(HANDLE a, MCIDEVICEID b, UINT c)           { FORWARD(mciDriverNotify)(a,b,c); }
    WINMMAPI UINT WINAPI mciDriverYield(MCIDEVICEID a)                                    { FORWARD(mciDriverYield)(a); }
    WINMMAPI BOOL WINAPI mciFreeCommandResource(UINT a)                                   { FORWARD(mciFreeCommandResource)(a); }
    WINMMAPI UINT WINAPI mciLoadCommandResource_proxy(HANDLE a, LPCWSTR b, UINT c)        { FORWARD(mciLoadCommandResource)(a,b,c); }
    FORWARD_NAKED(mid32Message)
    WINMMAPI UINT WINAPI mmDrvInstall_proxy(HDRVR a, LPCWSTR b, DRIVERMSGPROC c, UINT d)  { FORWARD(mmDrvInstall)(a,b,c,d); }
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

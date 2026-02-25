// trampolines.cpp / trampolines.h
// BZR Open Shim - clean-room replacement code for hop-fix hook targets.
//
// Copyright (C) 2025 BZR Open Shim contributors
// SPDX-License-Identifier: MIT
//
// Each trampoline is a __declspec(naked) x86 function that:
//   1. Executes the replacement logic derived from _bzcp.dll decompilation
//   2. Jumps back to BZR.exe via the corresponding g_RetAddr_* pointer
//
// The assembly was reconstructed from bzcp_hopfix_decompiled.txt and
// HOPFIX_ANALYSIS.md. It is NOT copied from the binary; it is a clean-room
// reimplementation of the described algorithm.

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <cstdint>

// -----------------------------------------------------------------------
// Return-address pointers (filled by patcher.cpp at patch time)
// -----------------------------------------------------------------------
namespace BZROpenShim
{
    extern void* g_RetAddr_HopFix1;
    extern void* g_RetAddr_HopFix2;
    extern void* g_RetAddr_HopFix3;
}

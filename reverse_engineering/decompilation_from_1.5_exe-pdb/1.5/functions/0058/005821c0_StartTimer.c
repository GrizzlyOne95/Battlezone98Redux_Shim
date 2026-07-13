/*
 * Entry: 005821c0
 * Name: StartTimer
 * Namespace: Global
 * Signature: void StartTimer(ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StartTimer(ulong param_1)

{
  dwPrevious = timeGetTime();
  bPaused = 0;
  fTimeStep = 0.0;
  dwOffset = 0;
  dwTime = param_1;
  dwTimeLocal = param_1;
  dwStartTime = dwPrevious;
  SetLoopTimes();
  return;
}

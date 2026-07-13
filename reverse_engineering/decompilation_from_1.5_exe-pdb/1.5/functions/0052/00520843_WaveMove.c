/*
 * Entry: 00520843
 * Name: WaveMove
 * Namespace: Global
 * Signature: void WaveMove(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl WaveMove(void)

{
  DWORD DVar1;
  
  if (-1 < waveMat) {
    DVar1 = timeGetTime();
    if (0x32 < DVar1 - lastWaveTime) {
      lastWaveIndex = lastWaveIndex + 1U & 0x7f;
      lastWaveTime = timeGetTime();
    }
    faceMask = 3;
  }
  return;
}

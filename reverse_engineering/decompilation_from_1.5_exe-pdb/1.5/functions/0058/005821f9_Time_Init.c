/*
 * Entry: 005821f9
 * Name: Time_Init
 * Namespace: Global
 * Signature: void Time_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Time_Init(void)

{
  timeBeginPeriod(1);
  dwFrameCount = 0;
  TICKS2SEC = 0.001;
  StartTimer(0);
  return;
}

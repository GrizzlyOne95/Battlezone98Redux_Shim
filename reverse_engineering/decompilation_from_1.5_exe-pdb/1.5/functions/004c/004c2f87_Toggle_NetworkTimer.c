/*
 * Entry: 004c2f87
 * Name: Toggle_NetworkTimer
 * Namespace: Global
 * Signature: void Toggle_NetworkTimer(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Toggle_NetworkTimer(void)

{
  int iVar1;
  
  iVar1 = Net_IsNetGame();
  if ((iVar1 != 0) && (Net::TimeLimit < 1)) {
    if (cockpitTimer.show != false) {
      CockpitTimer::HideTimer(&cockpitTimer);
      return;
    }
    CockpitTimer::ShowTimer(&cockpitTimer);
    return;
  }
  return;
}

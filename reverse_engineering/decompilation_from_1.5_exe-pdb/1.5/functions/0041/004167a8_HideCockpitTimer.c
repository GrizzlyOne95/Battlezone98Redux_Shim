/*
 * Entry: 004167a8
 * Name: HideCockpitTimer
 * Namespace: Global
 * Signature: void HideCockpitTimer(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl HideCockpitTimer(void)

{
  CockpitTimer::HideTimer(&cockpitTimer);
  return;
}

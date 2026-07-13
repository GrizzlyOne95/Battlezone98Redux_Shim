/*
 * Entry: 004c39cf
 * Name: ControlPanel_SatelliteEnabled
 * Namespace: Global
 * Signature: int ControlPanel_SatelliteEnabled(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ControlPanel_SatelliteEnabled(void)

{
  int iVar1;
  
  if (controlPanel.satelliteEnabled == 0) {
    iVar1 = UserPref_freeSatellite();
    if (iVar1 == 0) {
      iVar1 = UserPref_arcadeMode();
      if (iVar1 == 0) {
        return 0;
      }
    }
  }
  return 1;
}

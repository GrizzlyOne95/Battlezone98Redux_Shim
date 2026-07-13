/*
 * Entry: 004bf791
 * Name: UpdateRadarData
 * Namespace: Global
 * Signature: void UpdateRadarData(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UpdateRadarData(int param_1)

{
  int iVar1;
  int *piVar2;
  int local_8;
  
  local_8 = 0x1e0;
  piVar2 = &local_8;
  if (param_1 < 0x1e1) {
    piVar2 = &param_1;
  }
  iVar1 = *piVar2;
  RADAR_RADIUS = (iVar1 * 0x6e) / 0x1e0;
  RADAR_CENTER.x = (iVar1 * 0x78) / 0x1e0;
  RADAR_CENTER.y = param_1 - (iVar1 * 0x50) / 0x1e0;
  RADAR_BACKGROUND_POS.x = (iVar1 * -0x70) / 0x1e0;
  RADAR_BACKGROUND_POS.y = (iVar1 * -0x2e) / 0x1e0;
  return;
}

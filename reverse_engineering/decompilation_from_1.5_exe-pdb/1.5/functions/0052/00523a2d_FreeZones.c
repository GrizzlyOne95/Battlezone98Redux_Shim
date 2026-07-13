/*
 * Entry: 00523a2d
 * Name: FreeZones
 * Namespace: Global
 * Signature: void FreeZones(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl FreeZones(void)

{
  zixFree(ZoneFileMap.Buffer);
  zixFree(MZoneFileMap.Buffer);
  return;
}

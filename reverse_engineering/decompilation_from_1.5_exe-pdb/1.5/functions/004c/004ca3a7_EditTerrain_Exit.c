/*
 * Entry: 004ca3a7
 * Name: EditTerrain_Exit
 * Namespace: Global
 * Signature: void EditTerrain_Exit(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl EditTerrain_Exit(void)

{
  if (zoneDataChanged != 0) {
    CleanPathing();
    InitPathing();
    LabelConnectedRegions();
    ReloadPathing();
  }
  TerrainEditMode = 0;
  TerrainWireFrame = 0;
  SetEditMode(0);
  SelectTerrainView(0);
  UserProfilePtr->playOption = UserProfilePtr->playOption & 0xfffffffe;
  return;
}

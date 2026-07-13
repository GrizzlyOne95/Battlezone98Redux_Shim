/*
 * Entry: 004cd00d
 * Name: EditTerrain_Enter
 * Namespace: Global
 * Signature: void EditTerrain_Enter(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl EditTerrain_Enter(void)

{
  TerrainEditMode = 1;
  SetEditMode(1);
  SelectTerrainView(10);
  UserProfilePtr->playOption = UserProfilePtr->playOption | 1;
  EditTerrain_InitWorldMap();
  return;
}

/*
 * Entry: 00504726
 * Name: set_terrain_detail
 * Namespace: Global
 * Signature: int set_terrain_detail(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl set_terrain_detail(int param_1)

{
  SetTerrainPrefs((uint)(UserProfilePtr->graphicDetail).terrain);
  Terrain_Change_Texture_State();
  return 1;
}

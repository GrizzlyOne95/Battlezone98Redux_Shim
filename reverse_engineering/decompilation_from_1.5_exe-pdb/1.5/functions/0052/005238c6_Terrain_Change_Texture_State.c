/*
 * Entry: 005238c6
 * Name: Terrain_Change_Texture_State
 * Namespace: Global
 * Signature: void Terrain_Change_Texture_State(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Terrain_Change_Texture_State(void)

{
  if (TerrainLastQuality != (uint)(UserProfilePtr->graphicDetail).terrain) {
    Close_Terrain_Texture_Info();
    Set_Terrain_Texture_Info();
    return;
  }
  return;
}

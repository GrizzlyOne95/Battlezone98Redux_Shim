/*
 * Entry: 00521e1f
 * Name: SetTerrainPrefs
 * Namespace: Global
 * Signature: void SetTerrainPrefs(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetTerrainPrefs(int param_1)

{
  if (param_1 == 1) {
    flatROP = 0x109;
LAB_00521e9a:
    TerrainTextured = 0;
  }
  else {
    if (param_1 != 2) {
      if (param_1 == 3) {
        flatROP = 0x109;
        TerrainTextured = 1;
        TerrainPixelDoubling = 0;
        faceMask = 3;
        TerrainFirstMIP = 0;
        goto LAB_00521eb2;
      }
      flatROP = 0x108;
      goto LAB_00521e9a;
    }
    TerrainFirstMIP = ~((uint)D3IniFlags >> 0xe) & 1;
    flatROP = 0x109;
    TerrainTextured = 1;
  }
  TerrainPixelDoubling = 1;
  faceMask = 0xf;
LAB_00521eb2:
  if (useD3D == 0) {
    ClipSolidTile = __Clip_3D_Polygon;
    ClipTexturedTile = __Clip_3D_UV_Polygon;
  }
  else {
    if ((D3IniFlags & 1U) != 0) {
      LODInfo.mergeBSP = 0;
      TerrainSeparateDraw = 1;
      faceMask = 3;
    }
    ClipSolidTile = D3D_Clip_3D_Polygon;
    ClipTexturedTile = D3D_Clip_3D_UV_Polygon;
  }
  InitFogTable();
  return;
}

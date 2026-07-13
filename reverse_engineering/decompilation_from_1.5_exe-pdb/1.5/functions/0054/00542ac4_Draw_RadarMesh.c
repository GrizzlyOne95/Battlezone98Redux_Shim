/*
 * Entry: 00542ac4
 * Name: Draw_RadarMesh
 * Namespace: Global
 * Signature: int Draw_RadarMesh(_GRAPHIC_BUFFER * param_1, RADAR_MESH * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Draw_RadarMesh(_GRAPHIC_BUFFER *param_1,RADAR_MESH *param_2)

{
  if (useD3D == 0) {
    Radar_FBW_8(param_1,param_2);
  }
  else {
    (*RadarProc[D3RadarType & 7])(param_1,param_2);
  }
  return 1;
}

/*
 * Entry: 0051c72d
 * Name: GenerateSkyPos
 * Namespace: Global
 * Signature: void GenerateSkyPos(tagActiveSkyAnim * param_1, CAMERA * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GenerateSkyPos(tagActiveSkyAnim *param_1,CAMERA *param_2)

{
  int extraout_EAX;
  int extraout_EAX_00;
  int unaff_ESI;
  
  rand();
  rand();
  _ftol2_sse();
  _ftol2_sse();
  *(float *)(unaff_ESI + 0x10) = ((float)extraout_EAX_00 + 0.5) * Terrain.Grid_Size;
  *(float *)(unaff_ESI + 0x18) = ((float)extraout_EAX + 0.5) * Terrain.Grid_Size;
  return;
}

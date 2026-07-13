/*
 * Entry: 004047d7
 * Name: AiUtil_GetExtents
 * Namespace: Global
 * Signature: void AiUtil_GetExtents(float * param_1, float * param_2, float * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AiUtil_GetExtents(float *param_1,float *param_2,float *param_3,float *param_4)

{
  if (param_1 != (float *)0x0) {
    *param_1 = edgeMinX;
  }
  if (param_2 != (float *)0x0) {
    *param_2 = edgeMinZ;
  }
  if (param_3 != (float *)0x0) {
    *param_3 = edgeMaxX;
  }
  if (param_4 != (float *)0x0) {
    *param_4 = edgeMaxZ;
  }
  return;
}

/*
 * Entry: 004ed713
 * Name: GetMax
 * Namespace: Global
 * Signature: float GetMax(POINT_3D * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl GetMax(POINT_3D *param_1,long param_2)

{
  float fVar1;
  float *pfVar2;
  
  pfVar2 = &(param_1->Vector).z;
  fVar1 = *pfVar2;
  while (param_2 = param_2 + -1, param_2 != 0) {
    pfVar2 = pfVar2 + 6;
    if (fVar1 < *pfVar2) {
      fVar1 = *pfVar2;
    }
  }
  return fVar1;
}

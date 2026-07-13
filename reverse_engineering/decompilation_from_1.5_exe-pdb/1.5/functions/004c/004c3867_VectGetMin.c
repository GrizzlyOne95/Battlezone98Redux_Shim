/*
 * Entry: 004c3867
 * Name: VectGetMin
 * Namespace: Global
 * Signature: float VectGetMin(VECTOR_3D * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl VectGetMin(VECTOR_3D *param_1,long param_2)

{
  float fVar1;
  float *pfVar2;
  
  pfVar2 = &param_1->z;
  fVar1 = *pfVar2;
  while (param_2 = param_2 + -1, param_2 != 0) {
    pfVar2 = pfVar2 + 3;
    if (*pfVar2 < fVar1) {
      fVar1 = *pfVar2;
    }
  }
  return fVar1;
}

/*
 * Entry: 00521789
 * Name: PointInShadowBox
 * Namespace: Global
 * Signature: int PointInShadowBox(VECTOR_3D * param_1, PLANE * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PointInShadowBox(VECTOR_3D *param_1,PLANE *param_2)

{
  int in_ECX;
  float *pfVar1;
  float *in_EDX;
  int iVar2;
  
  iVar2 = 0;
  pfVar1 = (float *)(in_ECX + 4);
  do {
    if (pfVar1[2] < in_EDX[1] * *pfVar1 + pfVar1[1] * in_EDX[2] + pfVar1[-1] * *in_EDX) {
      return 0;
    }
    iVar2 = iVar2 + 1;
    pfVar1 = pfVar1 + 4;
  } while (iVar2 < 5);
  return 1;
}

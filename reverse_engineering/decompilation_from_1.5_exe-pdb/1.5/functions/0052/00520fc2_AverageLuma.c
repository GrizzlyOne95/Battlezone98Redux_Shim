/*
 * Entry: 00520fc2
 * Name: AverageLuma
 * Namespace: Global
 * Signature: void AverageLuma(POINT_3D * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AverageLuma(POINT_3D *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  POINT_3D *pPVar3;
  float *pfVar4;
  int iVar5;
  int in_ECX;
  undefined1 *puVar6;
  
  if (useD3D == 0) {
    fVar1 = 0.0;
    for (pPVar3 = param_1; 0 < (int)pPVar3;
        pPVar3 = (POINT_3D *)((int)&pPVar3[-1].Texel.field2_0x8 + 3)) {
      fVar1 = fVar1 + *(float *)(in_ECX + 0x14);
      in_ECX = in_ECX + 0x18;
    }
    fVar2 = (float)(int)param_1;
    if (0 < (int)param_1) {
      pfVar4 = (float *)(in_ECX + 0x14);
      do {
        pfVar4 = pfVar4 + -6;
        param_1 = (POINT_3D *)((int)&param_1[-1].Texel.field2_0x8 + 3);
        *pfVar4 = fVar1 / fVar2;
      } while (0 < (int)param_1);
    }
  }
  else {
    iVar5 = 0;
    for (pPVar3 = param_1; 0 < (int)pPVar3;
        pPVar3 = (POINT_3D *)((int)&pPVar3[-1].Texel.field2_0x8 + 3)) {
      iVar5 = iVar5 + (uint)*(byte *)(in_ECX + 0x14);
      in_ECX = in_ECX + 0x18;
    }
    iVar5 = iVar5 / (int)param_1;
    if (0 < (int)param_1) {
      puVar6 = (undefined1 *)(in_ECX + 0x14);
      do {
        puVar6 = puVar6 + -0x18;
        param_1 = (POINT_3D *)((int)&param_1[-1].Texel.field2_0x8 + 3);
        *puVar6 = (char)iVar5;
      } while (0 < (int)param_1);
      return;
    }
  }
  return;
}

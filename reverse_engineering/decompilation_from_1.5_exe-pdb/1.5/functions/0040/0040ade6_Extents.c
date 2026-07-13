/*
 * Entry: 0040ade6
 * Name: Extents
 * Namespace: Global
 * Signature: void Extents(AiPath * param_1, double * param_2, double * param_3, double * param_4, double * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Extents(AiPath *param_1,double *param_2,double *param_3,double *param_4,double *param_5)

{
  float *pfVar1;
  int in_ECX;
  int iVar2;
  double *unaff_EBX;
  double *unaff_EDI;
  undefined4 local_8;
  
  local_8 = 0;
  param_1->label = (char *)0x40000000;
  param_1->pointCount = 0x46293e59;
  *unaff_EDI = 1.0000000150474662e+30;
  *unaff_EBX = -1.0000000150474662e+30;
  *param_2 = -1.0000000150474662e+30;
  if (0 < *(int *)(in_ECX + 4)) {
    do {
      iVar2 = local_8 * 8;
      pfVar1 = (float *)(*(int *)(in_ECX + 8) + iVar2);
      if (*pfVar1 < (float)*unaff_EDI) {
        *unaff_EDI = (double)*pfVar1;
      }
      pfVar1 = (float *)(*(int *)(in_ECX + 8) + 4 + iVar2);
      if (*pfVar1 < (float)*(double *)param_1) {
        *(double *)param_1 = (double)*pfVar1;
      }
      pfVar1 = (float *)(*(int *)(in_ECX + 8) + iVar2);
      if ((float)*param_2 < *pfVar1) {
        *param_2 = (double)*pfVar1;
      }
      pfVar1 = (float *)(*(int *)(in_ECX + 8) + 4 + iVar2);
      if ((float)*unaff_EBX < *pfVar1) {
        *unaff_EBX = (double)*pfVar1;
      }
      local_8 = local_8 + 1;
    } while (local_8 < *(int *)(in_ECX + 4));
  }
  return;
}

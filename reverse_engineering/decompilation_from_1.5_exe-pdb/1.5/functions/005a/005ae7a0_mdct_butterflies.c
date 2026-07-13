/*
 * Entry: 005ae7a0
 * Name: mdct_butterflies
 * Namespace: Global
 * Signature: void mdct_butterflies(mdct_lookup * param_1, float * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mdct_butterflies(mdct_lookup *param_1,float *param_2,int param_3)

{
  int in_EAX;
  int iVar1;
  byte bVar2;
  int unaff_EBX;
  int iVar3;
  float *unaff_EBP;
  float *unaff_ESI;
  float *unaff_EDI;
  
  iVar3 = *(int *)(in_EAX + 4);
  if (0 < iVar3 + -6) {
    mdct_butterfly_first(unaff_EDI,unaff_ESI,unaff_EBX);
  }
  bVar2 = 1;
  for (iVar3 = iVar3 + -7; 0 < iVar3; iVar3 = iVar3 + -1) {
    iVar1 = 1 << (bVar2 & 0x1f);
    if (0 < iVar1) {
      do {
        mdct_butterfly_generic
                  ((float *)(4 << (bVar2 & 0x1f)),unaff_EBP,(int)unaff_EDI,(int)unaff_ESI);
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
    bVar2 = bVar2 + 1;
  }
  if (0 < (int)param_2) {
    iVar3 = ((int)param_2 - 1U >> 5) + 1;
    do {
      mdct_butterfly_32(unaff_EDI);
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return;
}

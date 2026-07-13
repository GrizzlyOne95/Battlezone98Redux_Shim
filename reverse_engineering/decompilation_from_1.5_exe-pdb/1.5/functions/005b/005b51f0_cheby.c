/*
 * Entry: 005b51f0
 * Name: cheby
 * Namespace: Global
 * Signature: void cheby(float * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl cheby(float *param_1,int param_2)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float *unaff_ESI;
  int unaff_EDI;
  int local_4;
  
  iVar4 = 2;
  *unaff_ESI = *unaff_ESI * 0.5;
  local_4 = unaff_EDI;
  if (1 < unaff_EDI) {
    do {
      local_4 = local_4 + -1;
      if (iVar4 <= unaff_EDI) {
        iVar2 = unaff_EDI;
        if (3 < local_4) {
          iVar3 = ((unaff_EDI - iVar4) - 3U >> 2) + 1;
          iVar2 = unaff_EDI + iVar3 * -4;
          pfVar1 = unaff_ESI + unaff_EDI + -2;
          do {
            iVar3 = iVar3 + -1;
            *pfVar1 = *pfVar1 - pfVar1[2];
            pfVar1[2] = pfVar1[2] + pfVar1[2];
            pfVar1[-1] = pfVar1[-1] - pfVar1[1];
            pfVar1[1] = pfVar1[1] + pfVar1[1];
            pfVar1[-2] = pfVar1[-2] - *pfVar1;
            *pfVar1 = *pfVar1 + *pfVar1;
            pfVar1[-3] = pfVar1[-3] - pfVar1[-1];
            pfVar1[-1] = pfVar1[-1] + pfVar1[-1];
            pfVar1 = pfVar1 + -4;
          } while (iVar3 != 0);
        }
        for (; iVar4 <= iVar2; iVar2 = iVar2 + -1) {
          unaff_ESI[iVar2 + -2] = unaff_ESI[iVar2 + -2] - unaff_ESI[iVar2];
          unaff_ESI[iVar2] = unaff_ESI[iVar2] + unaff_ESI[iVar2];
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 <= unaff_EDI);
  }
  return;
}

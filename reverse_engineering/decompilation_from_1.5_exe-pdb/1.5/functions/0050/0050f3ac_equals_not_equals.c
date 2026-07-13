/*
 * Entry: 0050f3ac
 * Name: equals_not_equals
 * Namespace: Global
 * Signature: double equals_not_equals(_domain * param_1, int * param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7, int * param_8, int * param_9, int * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl
equals_not_equals(_domain *param_1,int *param_2,int param_3,int *param_4,double *param_5,
                 char (*param_6) [80],int *param_7,int *param_8,int *param_9,int *param_10)

{
  int *piVar1;
  char (*pacVar2) [80];
  int iVar3;
  int extraout_EAX;
  int iVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  byte *pbVar8;
  bool bVar9;
  bool bVar10;
  double dVar11;
  double dVar12;
  int local_c;
  int local_8;
  
  pacVar2 = param_6;
  piVar1 = param_2;
  dVar11 = greater_than_less_than
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,&local_8,
                      (int *)&param_2,param_10);
  iVar4 = *piVar1;
  if (param_3 < iVar4) goto LAB_0050f449;
  pcVar7 = pacVar2[iVar4];
  uVar5 = param_3;
  if (*pcVar7 == 0x3d) {
    if (pcVar7[0x50] == 0x3d) {
      uVar5 = 1;
LAB_0050f400:
      *piVar1 = iVar4 + 1;
    }
  }
  else if (*pcVar7 == 0x21) {
    if (pcVar7[0x50] == 0x3d) {
      uVar5 = 0;
      goto LAB_0050f400;
    }
  }
  else {
    bVar10 = true;
    iVar4 = 3;
    pcVar6 = pcVar7;
    pbVar8 = &s_is;
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar10 = *pcVar6 == *pbVar8;
      pcVar6 = pcVar6 + 1;
      pbVar8 = pbVar8 + 1;
    } while (bVar10);
    uVar5 = (uint)bVar10;
    if (bVar10 == 0) {
      iVar4 = 5;
      bVar10 = false;
      iVar3 = 0;
      bVar9 = true;
      pbVar8 = &s_isnt;
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar10 = (byte)*pcVar7 < *pbVar8;
        bVar9 = *pcVar7 == *pbVar8;
        pcVar7 = pcVar7 + 1;
        pbVar8 = pbVar8 + 1;
      } while (bVar9);
      if (!bVar9) {
        iVar3 = (1 - (uint)bVar10) - (uint)(bVar10 != 0);
      }
      uVar5 = 0;
      if (iVar3 != 0) goto LAB_0050f449;
    }
  }
  *piVar1 = *piVar1 + 1;
  dVar12 = greater_than_less_than
                     (param_1,piVar1,param_3,param_4,param_5,param_6,param_7,&local_c,&param_3,
                      param_10);
  if ((local_8 == 0) || (local_c == 0)) {
    if (uVar5 == 0) {
      if (dVar12 != dVar11) goto LAB_0050f4d9;
    }
    else if (dVar12 == dVar11) {
LAB_0050f4d9:
      param_2 = (int *)0x1;
      goto LAB_0050f4cc;
    }
    param_2 = (int *)0x0;
  }
  else {
    if (uVar5 == 0) {
      bVar10 = param_2 != (int *)param_3;
    }
    else {
      bVar10 = param_2 == (int *)param_3;
    }
    param_2 = (int *)(uint)bVar10;
  }
LAB_0050f4cc:
  local_8 = 1;
LAB_0050f449:
  *param_8 = local_8;
  if (local_8 == 0) {
    _ftol2_sse();
    *param_9 = extraout_EAX;
    return dVar11;
  }
  *param_9 = (int)param_2;
  return (double)(int)param_2;
}

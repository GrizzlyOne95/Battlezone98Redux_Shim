/*
 * Entry: 0050f1ec
 * Name: greater_than_less_than
 * Namespace: Global
 * Signature: double greater_than_less_than(_domain * param_1, int * param_2, int param_3, int * param_4, double * param_5, char[80] * param_6, int * param_7, int * param_8, int * param_9, int * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

double __cdecl
greater_than_less_than
          (_domain *param_1,int *param_2,int param_3,int *param_4,double *param_5,
          char (*param_6) [80],int *param_7,int *param_8,int *param_9,int *param_10)

{
  int iVar1;
  int *piVar2;
  char (*pacVar3) [80];
  int extraout_EAX;
  int iVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  bool bVar8;
  double dVar9;
  double dVar10;
  char *local_1c;
  int local_18;
  int local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  pacVar3 = param_6;
  piVar2 = param_2;
  local_10 = 0;
  local_8 = 0;
  local_14 = 0;
  dVar9 = add_or_subtract(param_1,param_2,param_3,param_4,param_5,param_6,param_7,&local_18,
                          (int *)&param_2,param_10);
  iVar1 = *piVar2;
  iVar5 = local_18;
  if (iVar1 <= param_3) {
    local_1c = pacVar3[iVar1];
    bVar8 = true;
    iVar4 = 2;
    pcVar6 = local_1c;
    pcVar7 = ">";
    do {
      if (iVar4 == 0) break;
      iVar4 = iVar4 + -1;
      bVar8 = *pcVar6 == *pcVar7;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    } while (bVar8);
    local_c = (uint)bVar8;
    if (local_c == 0) {
      bVar8 = true;
      iVar4 = 2;
      pcVar6 = local_1c;
      pcVar7 = "<";
      do {
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar8 = *pcVar6 == *pcVar7;
        pcVar6 = pcVar6 + 1;
        pcVar7 = pcVar7 + 1;
      } while (bVar8);
      local_8 = (uint)bVar8;
      if (local_8 == 0) goto LAB_0050f381;
    }
    iVar5 = 2;
    bVar8 = true;
    *piVar2 = iVar1 + 1;
    pcVar6 = param_6[iVar1 + 1];
    pcVar7 = "=";
    do {
      if (iVar5 == 0) break;
      iVar5 = iVar5 + -1;
      bVar8 = *pcVar6 == *pcVar7;
      pcVar6 = pcVar6 + 1;
      pcVar7 = pcVar7 + 1;
    } while (bVar8);
    iVar5 = 1;
    if (bVar8) {
      if (local_c != 0) {
        local_c = 0;
        local_10 = 1;
      }
      if (local_8 != 0) {
        local_8 = 0;
        local_14 = 1;
      }
      *piVar2 = iVar1 + 2;
    }
    dVar10 = add_or_subtract(param_1,piVar2,param_3,param_4,param_5,param_6,param_7,&param_3,
                             (int *)&local_1c,param_10);
    if ((local_18 == 0) || (param_3 == 0)) {
      if ((local_10 != 0) && (param_2 = (int *)0x1, dVar10 < dVar9 == (dVar10 == dVar9))) {
        param_2 = (int *)0x0;
      }
      if ((local_14 != 0) && (param_2 = (int *)0x1, dVar10 < dVar9)) {
        param_2 = (int *)0x0;
      }
      if ((local_c != 0) && (param_2 = (int *)0x1, dVar9 <= dVar10)) {
        param_2 = (int *)0x0;
      }
      if ((local_8 != 0) && (param_2 = (int *)0x0, dVar9 < dVar10)) {
        param_2 = (int *)0x1;
      }
    }
    else {
      if (local_10 != 0) {
        param_2 = (int *)(uint)((int)local_1c <= (int)param_2);
      }
      if (local_14 != 0) {
        param_2 = (int *)(uint)((int)param_2 <= (int)local_1c);
      }
      if (local_c != 0) {
        param_2 = (int *)(uint)((int)local_1c < (int)param_2);
      }
      if (local_8 != 0) {
        param_2 = (int *)(uint)((int)param_2 < (int)local_1c);
      }
    }
  }
LAB_0050f381:
  *param_8 = iVar5;
  if (iVar5 == 0) {
    _ftol2_sse();
    *param_9 = extraout_EAX;
    return dVar9;
  }
  *param_9 = (int)param_2;
  return (double)(int)param_2;
}

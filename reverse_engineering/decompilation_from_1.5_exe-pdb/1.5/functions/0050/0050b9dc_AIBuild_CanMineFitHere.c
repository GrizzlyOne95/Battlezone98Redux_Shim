/*
 * Entry: 0050b9dc
 * Name: AIBuild_CanMineFitHere
 * Namespace: Global
 * Signature: int AIBuild_CanMineFitHere(int param_1, tagBUILDINGTYPE * param_2, int param_3, int param_4, int * param_5, int * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
AIBuild_CanMineFitHere
          (int param_1,tagBUILDINGTYPE *param_2,int param_3,int param_4,int *param_5,int *param_6)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int local_14;
  int local_10;
  int local_8;
  
  tlog_gdm("AIBuild_CanMineFitHere Begins\n");
  bVar2 = false;
  local_14 = 0;
  uVar5 = 1;
  local_10 = param_3;
  do {
    local_10 = local_10 + -1;
    local_8 = 0;
    if (0 < (int)uVar5) {
      do {
        if (bVar2) break;
        iVar1 = (param_4 - param_3) + local_10;
        iVar4 = (local_8 - (int)uVar5 / 2) + param_3;
        iVar3 = AIBuild_CanMineFitExactlyHere(param_1,param_2,iVar4,iVar1);
        if (iVar3 != 0) {
          bVar2 = true;
          local_14 = 1;
          *param_5 = iVar4;
          *param_6 = iVar1;
        }
        local_8 = local_8 + 1;
      } while (local_8 < (int)uVar5);
    }
    local_8 = 0;
    if (0 < (int)uVar5) {
      do {
        if (bVar2) break;
        iVar1 = (param_4 - param_3) + uVar5 + param_3;
        iVar4 = (local_8 - (int)uVar5 / 2) + param_3;
        iVar3 = AIBuild_CanMineFitExactlyHere(param_1,param_2,iVar4,iVar1);
        if (iVar3 != 0) {
          bVar2 = true;
          local_14 = 1;
          *param_5 = iVar4;
          *param_6 = iVar1;
        }
        local_8 = local_8 + 1;
      } while (local_8 < (int)uVar5);
    }
    local_8 = 0;
    if (0 < (int)uVar5) {
      do {
        if (bVar2) break;
        iVar1 = (local_8 - (int)uVar5 / 2) + param_4;
        iVar4 = AIBuild_CanMineFitExactlyHere(param_1,param_2,uVar5 + param_3,iVar1);
        if (iVar4 != 0) {
          bVar2 = true;
          local_14 = 1;
          *param_5 = uVar5 + param_3;
          *param_6 = iVar1;
        }
        local_8 = local_8 + 1;
      } while (local_8 < (int)uVar5);
    }
    local_8 = 0;
    if (0 < (int)uVar5) {
      do {
        if (bVar2) break;
        iVar1 = (local_8 - (int)uVar5 / 2) + param_4;
        iVar4 = AIBuild_CanMineFitExactlyHere(param_1,param_2,local_10,iVar1);
        if (iVar4 != 0) {
          bVar2 = true;
          local_14 = 1;
          *param_5 = local_10;
          *param_6 = iVar1;
        }
        local_8 = local_8 + 1;
      } while (local_8 < (int)uVar5);
    }
    uVar5 = uVar5 + 1;
    if (((*(uint *)&param_2->field_0x24 >> 0x13 & 7) < uVar5) ||
       ((*(uint *)&param_2->field_0x24 >> 0x17 & 7) < uVar5)) {
      bVar2 = true;
    }
    if (bVar2) {
      tlog_gdm("AIBuild_CanMineFitHere Ends\n");
      return local_14;
    }
  } while( true );
}

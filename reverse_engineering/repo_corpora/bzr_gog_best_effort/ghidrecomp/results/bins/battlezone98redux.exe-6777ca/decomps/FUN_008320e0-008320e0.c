
bool FUN_008320e0(int param_1,double *param_2,double *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_2 + 1);
  if (iVar3 != 0) {
    if ((iVar3 == 1) || (iVar3 == 2)) {
      iVar2 = *(int *)param_2;
LAB_0083216f:
      return iVar2 == *(int *)param_3;
    }
    if (iVar3 == 3) {
      if (*param_2 != *param_3) {
        return false;
      }
      return true;
    }
    if (iVar3 == 5) {
      iVar2 = *(int *)param_2;
    }
    else {
      iVar2 = *(int *)param_2;
      if (iVar3 != 7) goto LAB_0083216f;
    }
    if (iVar2 != *(int *)param_3) {
      iVar3 = FUN_00831dd4(param_1,*(undefined4 *)(iVar2 + 8),*(undefined4 *)(*(int *)param_3 + 8),4
                          );
      if (iVar3 == 0) {
        return false;
      }
      FUN_00831c7a(param_1,*(undefined4 *)(param_1 + 8),iVar3,param_2,param_3);
      piVar1 = *(int **)(param_1 + 8);
      if (piVar1[2] == 0) {
        return false;
      }
      if (piVar1[2] != 1) {
        return true;
      }
      if (*piVar1 == 0) {
        return false;
      }
      return true;
    }
  }
  return true;
}


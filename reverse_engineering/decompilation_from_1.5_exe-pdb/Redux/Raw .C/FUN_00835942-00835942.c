
void FUN_00835942(int param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0xc) + -1;
  if (-1 < iVar3) {
    piVar1 = (int *)(param_1 + 0x14 + iVar3 * 8);
    do {
      if (*piVar1 == -1) goto LAB_00835972;
      piVar1 = piVar1 + -2;
      iVar3 = iVar3 + -1;
    } while (-1 < iVar3);
  }
  iVar3 = FUN_0082bc39(*(undefined4 *)(param_1 + 8),"invalid pattern capture");
LAB_00835972:
  *(int *)(param_1 + 0x14 + iVar3 * 8) = param_2 - *(int *)(param_1 + 0x10 + iVar3 * 8);
  iVar2 = FUN_00835b72(param_1,param_2,param_3);
  if (iVar2 == 0) {
    *(undefined4 *)(param_1 + 0x14 + iVar3 * 8) = 0xffffffff;
  }
  return;
}


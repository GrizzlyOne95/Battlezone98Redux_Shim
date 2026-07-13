
void FUN_008361e7(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xc);
  if (0x1f < iVar1) {
    FUN_0082bc39(*(undefined4 *)(param_1 + 8),"too many captures");
  }
  *(undefined4 *)(param_1 + 0x14 + iVar1 * 8) = param_4;
  *(undefined4 *)(param_1 + 0x10 + iVar1 * 8) = param_2;
  *(int *)(param_1 + 0xc) = iVar1 + 1;
  iVar1 = FUN_00835b72(param_1,param_2,param_3);
  if (iVar1 == 0) {
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -1;
  }
  return;
}


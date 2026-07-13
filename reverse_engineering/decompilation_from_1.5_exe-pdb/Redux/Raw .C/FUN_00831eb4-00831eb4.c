
uint FUN_00831eb4(undefined4 param_1,double *param_2,double *param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_2 + 1);
  if (iVar1 == *(int *)(param_3 + 1)) {
    if (iVar1 == 3) {
      return (uint)(*param_2 <= *param_3);
    }
    if (iVar1 == 4) {
      iVar1 = FUN_00831e54(*(undefined4 *)param_2,*(undefined4 *)param_3);
      return (uint)(iVar1 < 1);
    }
    uVar2 = FUN_00831d67(param_1,param_2,param_3,0xe);
    if (uVar2 != 0xffffffff) {
      return uVar2;
    }
    iVar1 = FUN_00831d67(param_1,param_3,param_2,0xd);
    if (iVar1 != -1) {
      return (uint)(iVar1 == 0);
    }
  }
  uVar2 = FUN_0082df0d(param_1,param_2,param_3);
  return uVar2;
}


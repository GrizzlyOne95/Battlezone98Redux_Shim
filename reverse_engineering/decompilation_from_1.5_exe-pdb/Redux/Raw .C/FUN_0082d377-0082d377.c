
int FUN_0082d377(int param_1,undefined4 param_2,undefined4 *param_3)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)FUN_0082c4a6(param_1,param_2);
  if (piVar1[2] != 4) {
    iVar2 = FUN_00833372(param_1,piVar1);
    if (iVar2 == 0) {
      if (param_3 != (undefined4 *)0x0) {
        *param_3 = 0;
      }
      return 0;
    }
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      FUN_00830222(param_1);
    }
    piVar1 = (int *)FUN_0082c4a6(param_1,param_2);
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = *(undefined4 *)(*piVar1 + 0xc);
  }
  return *piVar1 + 0x10;
}


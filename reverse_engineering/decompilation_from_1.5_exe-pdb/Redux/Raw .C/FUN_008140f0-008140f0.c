
undefined4 __thiscall FUN_008140f0(undefined4 param_1,int *param_2,undefined1 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*param_2 < -0xccccccc) {
    uVar1 = 0;
  }
  else {
    *param_2 = *param_2 * 10;
    iVar2 = FUN_00814580(param_3,param_1);
    if (*param_2 < iVar2 + -0x80000000) {
      uVar1 = 0;
    }
    else {
      *param_2 = *param_2 - iVar2;
      uVar1 = 1;
    }
  }
  return uVar1;
}


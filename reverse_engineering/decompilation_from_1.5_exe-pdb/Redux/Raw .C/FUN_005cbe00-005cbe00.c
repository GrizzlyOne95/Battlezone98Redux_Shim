
void __thiscall FUN_005cbe00(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_00460fc0(param_2,param_1);
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 0x10) = param_3;
  }
  return;
}


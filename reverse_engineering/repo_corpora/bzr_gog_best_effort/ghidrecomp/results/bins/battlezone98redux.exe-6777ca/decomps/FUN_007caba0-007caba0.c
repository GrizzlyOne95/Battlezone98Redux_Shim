
void __thiscall FUN_007caba0(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  param_2 = param_2 - *(int *)(param_1 + 0x150);
  if (-1 < param_2) {
    iVar1 = size();
    if (param_2 < iVar1) {
      FUN_004200d0(param_2);
      FUN_007cca20(param_3);
    }
  }
  return;
}



undefined4 __thiscall FUN_0069ddd0(int param_1,int *param_2)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x14) == 0) {
    uVar1 = 0;
  }
  else if (*(int *)(*(int *)(param_1 + 0x14) + 0x34) < *(int *)(param_1 + 8)) {
    uVar1 = 0;
  }
  else {
    *param_2 = *(int *)(*(int *)(param_1 + 0x14) + 0x34) - *(int *)(param_1 + 0xc);
    uVar1 = 1;
  }
  return uVar1;
}


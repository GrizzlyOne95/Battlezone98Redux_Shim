
undefined4 __thiscall FUN_007c16f0(int param_1,int param_2,undefined2 param_3)

{
  undefined4 uVar1;
  
  if (*(int *)(param_1 + 0x148) == 0) {
    if (param_2 == 0x1b) {
      FUN_00788060();
      uVar1 = 1;
    }
    else {
      uVar1 = FUN_007d2490(param_2,param_3);
    }
  }
  else {
    FUN_007c12a0();
    uVar1 = 1;
  }
  return uVar1;
}


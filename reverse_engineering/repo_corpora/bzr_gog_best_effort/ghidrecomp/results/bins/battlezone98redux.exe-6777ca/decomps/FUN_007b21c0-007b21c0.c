
undefined4 __thiscall FUN_007b21c0(undefined4 param_1,int param_2,undefined2 param_3)

{
  undefined4 uVar1;
  
  if (param_2 == 0x1b) {
    if (DAT_009455b0 != 0 || DAT_009455b4 != 0) {
      FUN_007ae480(1,param_1);
    }
    FUN_007ae8f0();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_007d2490(param_2,param_3);
  }
  return uVar1;
}


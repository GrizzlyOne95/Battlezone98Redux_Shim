
undefined4 __thiscall FUN_005d7800(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0x19) {
    *(undefined4 *)(param_1 + 0x20) = 0x11;
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_005833a0(param_2);
  }
  return uVar1;
}


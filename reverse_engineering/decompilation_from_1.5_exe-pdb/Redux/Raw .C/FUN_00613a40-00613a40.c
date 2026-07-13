
undefined4 __thiscall FUN_00613a40(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else if (param_2 == 0x14) {
    *(undefined4 *)(param_1 + 0x20) = 0x10;
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x13,0);
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_005833a0(param_2);
  }
  return uVar1;
}


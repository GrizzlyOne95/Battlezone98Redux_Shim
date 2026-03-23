
undefined4 __thiscall FUN_005833a0(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else if (param_2 == 5) {
    *(undefined4 *)(param_1 + 0x6c) = 0x46742400;
    uVar1 = FUN_005fad00(5);
  }
  else if (param_2 == 6) {
    *(undefined4 *)(param_1 + 0x6c) = 0;
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0xc,0);
    *(undefined4 *)(param_1 + 0x20) = 8;
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_005fad00(param_2);
  }
  return uVar1;
}


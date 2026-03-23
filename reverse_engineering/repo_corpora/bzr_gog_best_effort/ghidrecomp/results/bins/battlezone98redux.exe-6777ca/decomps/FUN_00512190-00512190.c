
undefined4 __thiscall FUN_00512190(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else if (param_2 == 1) {
    if (*(int *)(param_1 + 0x1c) == 0x10) {
      FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),7,0);
      FUN_004dbb40();
      uVar1 = 0;
    }
    else {
      uVar1 = FUN_005fad00(1);
    }
  }
  else if (param_2 == 0x1a) {
    FUN_005f91e0(*(undefined4 *)(param_1 + 0x34),0x13,0);
    *(undefined4 *)(param_1 + 0x20) = 0x10;
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_005fad00(param_2);
  }
  return uVar1;
}


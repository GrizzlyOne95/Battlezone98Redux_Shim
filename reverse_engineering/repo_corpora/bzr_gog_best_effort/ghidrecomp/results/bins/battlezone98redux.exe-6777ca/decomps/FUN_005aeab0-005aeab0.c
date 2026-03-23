
undefined4 FUN_005aeab0(uint param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0xb) {
    FUN_004dbce0(0x10);
    uVar1 = 1;
  }
  else if (param_1 == 3) {
    FUN_004dbce0(7);
    uVar1 = 1;
  }
  else if (param_1 == 0x17) {
    FUN_004dbce0(2);
    uVar1 = 1;
  }
  else if (param_1 < 0x1b) {
    uVar1 = FUN_004a8560(param_1);
  }
  else {
    FUN_004dbf90(0x15,param_1,0);
    uVar1 = 1;
  }
  return uVar1;
}


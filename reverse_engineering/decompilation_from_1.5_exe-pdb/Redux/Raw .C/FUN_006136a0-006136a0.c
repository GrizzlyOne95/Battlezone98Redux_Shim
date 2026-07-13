
undefined4 FUN_006136a0(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0xd) {
    FUN_004dbce0(0x14);
    uVar1 = 1;
  }
  else if (param_1 == 0x10) {
    FUN_004dbd60(6,DAT_00917afc);
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a8560(param_1);
  }
  return uVar1;
}


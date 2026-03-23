
void __fastcall FUN_005972d0(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_00920ef4;
  DAT_00920ef4 = 0x3f800000;
  if ((*(uint *)(param_1 + 0x70) & 1) == 0) {
    if ((*(uint *)(param_1 + 0x70) & 0x10) == 0) {
      if ((*(uint *)(param_1 + 0x70) & 0x20) == 0) {
        if ((*(uint *)(param_1 + 0x70) & 0x40) == 0) {
          if ((*(uint *)(param_1 + 0x70) & 0x80) == 0) {
            if ((*(uint *)(param_1 + 0x70) & 0x100) != 0) {
              FUN_005970a0();
            }
          }
          else {
            FUN_00596f40();
          }
        }
        else {
          FUN_00596cf0();
        }
      }
      else {
        FUN_00596ba0();
      }
    }
    else {
      FUN_005969c0();
    }
  }
  else {
    FUN_00596240();
  }
  if ((*(uint *)(param_1 + 0x70) & 2) != 0) {
    FUN_005962a0();
  }
  if ((*(uint *)(param_1 + 0x70) & 4) != 0) {
    FUN_00596520();
  }
  if ((*(uint *)(param_1 + 0x70) & 8) != 0) {
    FUN_00596190(1);
  }
  DAT_00920ef4 = uVar1;
  return;
}



void FUN_00686470(undefined4 *param_1)

{
  undefined4 *puVar1;
  
  if ((DAT_00920ee0 != 0) && (param_1 == &DAT_008eaae0)) {
    FUN_006863b0(&DAT_008eaae0,DAT_00920ee0);
  }
  if (DAT_00920ee4 != 0) {
    puVar1 = (undefined4 *)FUN_005dddd0();
    if (param_1 == puVar1) {
      FUN_006863b0(param_1,DAT_00920ee4);
    }
  }
  if (DAT_00920ed8 != 0) {
    puVar1 = (undefined4 *)FUN_005d6510();
    if (param_1 == puVar1) {
      FUN_006863b0(param_1,DAT_00920ed8);
    }
  }
  return;
}


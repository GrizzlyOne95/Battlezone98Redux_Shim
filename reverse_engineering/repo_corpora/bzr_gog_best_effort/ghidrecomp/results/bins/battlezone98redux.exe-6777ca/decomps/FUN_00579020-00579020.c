
void __thiscall FUN_00579020(undefined4 param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = FUN_0050cd60(param_1);
  if (uVar1 < param_2) {
    uVar1 = FID_conflict_max_size();
    if (uVar1 < param_2) {
      FUN_00423e40();
    }
    FUN_005794f0(param_2);
  }
  return;
}


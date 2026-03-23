
void __thiscall FUN_006cf440(undefined4 param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = FUN_0048a810(param_1);
  if (uVar1 < param_2) {
    uVar1 = FID_conflict_max_size();
    if (uVar1 < param_2) {
      FUN_00423e40();
    }
    FUN_006d3170(param_2);
  }
  return;
}


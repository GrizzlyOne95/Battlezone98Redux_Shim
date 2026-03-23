
void FUN_00592670(uint param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_005927c0();
  if (uVar1 < param_1) {
    iVar2 = FID_conflict_max_size();
    iVar3 = FUN_0046b240();
    if ((uint)(iVar2 - iVar3) < param_1) {
      FUN_00423e40();
    }
    iVar2 = FUN_0046b240();
    uVar4 = FID_conflict__Grow_to(iVar2 + param_1);
    FUN_00592840(uVar4);
  }
  return;
}


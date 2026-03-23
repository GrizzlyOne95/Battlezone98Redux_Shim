
void FUN_00756470(uint param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_007564d0();
  if (uVar1 < param_1) {
    iVar2 = FID_conflict_max_size();
    iVar3 = FUN_007564f0();
    if ((uint)(iVar2 - iVar3) < param_1) {
      FUN_00423e40();
    }
    iVar2 = FUN_007564f0();
    uVar4 = FID_conflict__Grow_to(iVar2 + param_1);
    FUN_00756590(uVar4);
  }
  return;
}


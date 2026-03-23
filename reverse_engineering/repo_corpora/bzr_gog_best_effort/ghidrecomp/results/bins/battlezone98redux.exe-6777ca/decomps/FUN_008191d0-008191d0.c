
void FUN_008191d0(uint param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_006e6070();
  if (uVar1 < param_1) {
    iVar2 = FID_conflict_max_size();
    iVar3 = FUN_006e6090();
    if ((uint)(iVar2 - iVar3) < param_1) {
      FUN_00423e40();
    }
    iVar2 = FUN_006e6090();
    uVar4 = FID_conflict__Grow_to(iVar2 + param_1);
    FUN_00819400(uVar4);
  }
  return;
}


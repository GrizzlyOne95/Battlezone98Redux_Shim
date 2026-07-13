
void FUN_0066b700(uint param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_0066bfb0();
  if (uVar1 < param_1) {
    iVar2 = FUN_0066be00();
    iVar3 = FUN_00669fa0();
    if ((uint)(iVar2 - iVar3) < param_1) {
      FUN_00423e40();
    }
    iVar2 = FUN_00669fa0();
    uVar4 = FID_conflict__Grow_to(iVar2 + param_1);
    FUN_0066c030(uVar4);
  }
  return;
}


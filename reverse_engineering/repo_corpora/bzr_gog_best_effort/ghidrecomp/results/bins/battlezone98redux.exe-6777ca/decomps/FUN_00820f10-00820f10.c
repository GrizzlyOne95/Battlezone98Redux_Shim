
undefined4 FUN_00820f10(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int local_8;
  
  uVar3 = 1;
  uVar1 = FUN_00820ed0();
  FUN_00827910(&DAT_02cf3000,uVar3,uVar1);
  for (local_8 = 0; local_8 < DAT_00946730; local_8 = local_8 + 1) {
    FUN_00827910(&DAT_02c41b08 + local_8 * 0x100);
  }
  FUN_008282e0(uVar1);
  iVar2 = FUN_008283e0();
  if (iVar2 == 0) {
    FUN_00619ba0(
                "Sorry, unable to find required files to run. Please check your working directory or reinstall the game."
                );
    uVar3 = 0;
  }
  return uVar3;
}


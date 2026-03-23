
void FUN_00624110(void)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  if (DAT_009183b0 == 0) {
    if (DAT_008eaaa4 == 0) {
      if (DAT_0092015c != 0) {
        FUN_004351e0(0);
        DAT_0092015c = 0;
      }
    }
    else if (DAT_02a17484 == 0) {
      DAT_02a17484 = 0;
      FUN_004351e0(0);
      DAT_0092015c = 0;
      FUN_00623ac0(&DAT_02a17474,0);
      FUN_00623ac0(&DAT_02a17474,1);
      FUN_00623ac0(&DAT_02a17474,2);
      FUN_00623ac0(&DAT_02a17474,3);
      iVar1 = FUN_00435090(&local_c);
      if ((iVar1 == 1) && (*DAT_02cecefc != 0)) {
        FUN_00435030(&local_c);
        FUN_005d4950(local_c,local_8);
      }
      do {
        iVar1 = FUN_00435130(1);
      } while (iVar1 == 0);
    }
    else {
      FUN_00623eb0();
    }
  }
  return;
}


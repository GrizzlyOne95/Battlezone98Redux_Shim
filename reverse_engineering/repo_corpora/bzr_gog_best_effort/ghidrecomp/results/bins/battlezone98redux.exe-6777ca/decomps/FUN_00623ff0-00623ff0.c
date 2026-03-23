
void FUN_00623ff0(void)

{
  int iVar1;
  int local_c;
  int local_8;
  
  FUN_00623990(0);
  DAT_02a17484 = 0;
  if ((DAT_008eaaa4 != 0) && (DAT_009183b0 == 0)) {
    FUN_004351e0(0);
  }
  DAT_0092015c = 0;
  FUN_00623ac0(&DAT_02a17474,0);
  FUN_00623ac0(&DAT_02a17474,1);
  FUN_00623ac0(&DAT_02a17474,2);
  FUN_00623ac0(&DAT_02a17474,3);
  if (((DAT_008eaaa4 != 0) && (iVar1 = FUN_00435160(), iVar1 == 1)) && (DAT_009183b0 == 0)) {
    local_c = DAT_02cecf00 / 2;
    local_8 = DAT_02cecf04 / 2;
    FUN_005d4950(local_c,local_8);
    FUN_004350e0(&local_c);
  }
  iVar1 = DAT_009183b0;
  if (DAT_008eaaa4 != 0) {
    while (iVar1 == 0) {
      iVar1 = FUN_00435130(1);
    }
  }
  return;
}


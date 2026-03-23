
void FUN_00618130(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  DAT_009183e0 = 0;
  iVar1 = FUN_00451de0();
  if (iVar1 == 0) {
    FUN_00442e70();
  }
  if (param_1 == 0) {
    FUN_0061dba0();
  }
  iVar1 = FUN_00434160();
  if (iVar1 == 9) {
    FUN_006192b0(&DAT_02cecee0);
  }
  else {
    FUN_004d44f0();
    iVar1 = FUN_00572a70();
    if (iVar1 == 0) {
      FUN_00764a10();
    }
    else {
      iVar1 = FUN_00572640();
      if (iVar1 == 0) {
        iVar1 = FUN_00434160();
        if ((iVar1 == 2) || (iVar1 = FUN_00572a80(), iVar1 != 0)) {
          FUN_00434170(2);
        }
        else {
          FUN_0081e0c0("DoNextFrame: Quiting Game Due to Net Execute failure\n");
          uVar2 = FUN_0081cb40("multi_error","game_lost");
          FUN_0056fcb0(uVar2);
          FUN_00434170(2);
          FUN_005d48b0();
        }
      }
    }
    iVar1 = FUN_00451de0();
    if (iVar1 == 0) {
      FUN_0045bf90(&DAT_02cecee0);
    }
    FUN_00618060();
    FUN_00617fa0();
    iVar1 = FUN_00572a70();
    if (iVar1 != 0) {
      FUN_004df3b0();
    }
    FUN_0043a170(1);
    if ((param_2 != 0) && (DAT_008fe240 == 1)) {
      uVar2 = FUN_00439e60();
      FUN_006175c0(uVar2);
      FUN_00682540();
    }
    FUN_0062d5a0();
    FUN_006192b0(&DAT_02cecee0);
    if (DAT_009183e0 == 0) {
      FUN_00617b20();
    }
  }
  return;
}


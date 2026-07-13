
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __fastcall FUN_006185f0(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  FUN_0081e0c0("End of Game Menu Display\n",param_1);
  FUN_00681e40();
  DAT_00920ecc = 0;
  FUN_00618bc0();
  _chdir(&DAT_02cf0000);
  FUN_0081e0c0("Sim Startup: Starting Simulator\n");
  _DAT_02a13e80 = FUN_00822e60();
  FUN_00764a10();
  iVar1 = FUN_00822e60();
  FUN_0081e0c0("Sim Startup: Mission Preload after %ld ms initializing\n",iVar1 - _DAT_02a13e80);
  FUN_00616fc0();
  iVar1 = FUN_00822e60();
  FUN_0081e0c0("Sim Startup: Mission Load after %ld ms initializing\n",iVar1 - _DAT_02a13e80);
  iVar1 = FUN_006170a0();
  if (iVar1 == 0) {
    FUN_00434170(2);
    FUN_00618370();
    uVar2 = 1;
  }
  else {
    iVar1 = FUN_00822e60();
    FUN_0081e0c0("Sim Startup: Check Resave after %ld ms initializing\n",iVar1 - _DAT_02a13e80);
    FUN_004fbff0();
    iVar1 = FUN_00822e60();
    FUN_0081e0c0("Sim Startup: Post Load after %ld ms initializing\n",iVar1 - _DAT_02a13e80);
    iVar1 = FUN_00617110();
    if (iVar1 == 0) {
      FUN_00434170(2);
      FUN_00618370();
      uVar2 = 1;
    }
    else {
      iVar1 = FUN_00822e60();
      FUN_0081e0c0("Sim Startup: First Frame after %ld ms initializing\n",iVar1 - _DAT_02a13e80);
      FUN_005d50a0();
      iVar1 = FUN_00572a70();
      if ((iVar1 != 0) && (iVar1 = FUN_00434160(), iVar1 != 2)) {
        iVar1 = FUN_00822e60();
        FUN_0081e0c0("Sim Startup: Initializing Game Simulation Network Part 2 after %ld ms initializing\n"
                     ,iVar1 - _DAT_02a13e80);
        iVar3 = FUN_00572830();
        if (iVar3 == 0) {
          FUN_0081e0c0("Net: Exiting Game Due to Network Start Sync Failure\n",iVar1);
          uVar2 = FUN_0081cb40("multi_error","fail_join_game");
          FUN_0056fcb0(uVar2);
          FUN_00434170(2);
          FUN_005d48b0();
        }
      }
      FUN_005d50f0();
      DAT_02a13e34 = FUN_00822e60();
      if ((DAT_009183bc != 0) && (iVar1 = FUN_00434160(), iVar1 == 5)) {
        FUN_004fdc80(1,"Save After Load Test");
      }
      if ((DAT_009183e8 == 0) && (iVar1 = FUN_00434160(), iVar1 == 5)) {
        iVar1 = FUN_00572a70();
        if (iVar1 == 0) {
          FUN_0081e0c0("Game Simulation Initialized after %ld.%03ld seconds, Playing\n",
                       (DAT_02a13e34 - _DAT_02a13e80) / 1000,(DAT_02a13e34 - _DAT_02a13e80) % 1000);
        }
        else {
          FUN_0081e0c0("Game Simulation Initialized after %ld.%03ld seconds (%ld.%03ld after network startup), Playing\n"
                       ,(DAT_02a13e34 - _DAT_02a13e80) / 1000,(DAT_02a13e34 - _DAT_02a13e80) % 1000,
                       (DAT_02a13e34 - DAT_02a13e30) / 1000,(DAT_02a13e34 - DAT_02a13e30) % 1000);
        }
      }
      else {
        iVar1 = FUN_00572a70();
        if (iVar1 == 0) {
          FUN_0081e0c0("Game Simulation Initialized after %ld.%03ld seconds\n",
                       (DAT_02a13e34 - _DAT_02a13e80) / 1000,(DAT_02a13e34 - _DAT_02a13e80) % 1000);
        }
        else {
          FUN_0081e0c0("Game Simulation Initialized after %ld.%03ld seconds (%ld.%03ld after network startup)\n"
                       ,(DAT_02a13e34 - _DAT_02a13e80) / 1000,(DAT_02a13e34 - _DAT_02a13e80) % 1000,
                       (DAT_02a13e34 - DAT_02a13e30) / 1000,(DAT_02a13e34 - DAT_02a13e30) % 1000);
        }
        if (DAT_009183e8 != 0) {
          FUN_0081e0c0("Exiting game because exitAfterLoad was specified\n");
          FUN_00434170(9);
        }
      }
      FUN_00822ab0();
      DAT_009183dc = 1;
      FUN_00681df0();
      DAT_00920ecc = 1;
      uVar2 = 0;
    }
  }
  return uVar2;
}


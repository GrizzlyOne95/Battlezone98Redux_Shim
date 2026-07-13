
/* WARNING: Removing unreachable block (ram,0x006172f7) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00617110(void)

{
  int iVar1;
  undefined4 uVar2;
  longlong lVar3;
  longlong lVar4;
  
  DAT_009467b4 = 1;
  FUN_004b6ec0();
  FUN_0045bf10();
  FUN_0062baf0();
  FUN_0049b2d0();
  FUN_004dfa20();
  FUN_005c5870();
  if (DAT_009467b4 == 0) {
    FUN_0045bf30();
  }
  DAT_009467b4 = 0;
  FUN_00682390();
  lVar3 = FUN_0056f760(0);
  iVar1 = FUN_00572a70();
  if (iVar1 != 0) {
    DAT_02a13e30 = FUN_00822e60();
    FUN_0081e0c0("Sim Startup: Initializing Game Simulation Network Part 1 after %ld ms initializing\n"
                 ,DAT_02a13e30 - _DAT_02a13e80);
    FUN_005726d0(lVar3);
    iVar1 = FUN_00572380();
    if (iVar1 == 0) {
      FUN_0081e0c0("Game quit due to cheat detected\n");
      uVar2 = FUN_0081cb40("multi_error","version_mismatch");
      FUN_0056fcb0(uVar2);
      FUN_00434170(2);
      FUN_00437620(1);
      FUN_005d48b0();
      return 0;
    }
    FUN_004fd090();
    iVar1 = FUN_00572400();
    if (iVar1 == 0) {
      FUN_0081e0c0("Game quit due to network issues stage 1\n");
      uVar2 = FUN_0081cb40("multi_error","no_net_response");
      FUN_0056fcb0(uVar2);
      FUN_00434170(2);
      FUN_00437620(1);
      FUN_005d48b0();
      return 0;
    }
    FUN_007d6a70("Waiting for network system...\n");
    do {
      FUN_00822ae0();
      iVar1 = FUN_00572640();
      if (iVar1 == 0) {
        FUN_0081e0c0("Game quit due to network issues stage 2\n");
        uVar2 = FUN_0081cb40("multi_error","no_net_response");
        FUN_0056fcb0(uVar2);
        FUN_00434170(2);
        FUN_00437620(1);
        FUN_005d48b0();
        FUN_00572a30(1);
        FUN_00572640();
        return 0;
      }
      lVar4 = FUN_0056f760(0);
      if (0x5a < lVar4 - lVar3) {
        FUN_0081e0c0("Game quit due to excessive network connection time\n");
        uVar2 = FUN_0081cb40("multi_error","fail_join_game");
        FUN_0056fcb0(uVar2);
        FUN_00434170(2);
        FUN_00437620(1);
        FUN_005d48b0();
        FUN_00572a30(1);
        FUN_00572640();
        return 0;
      }
      FUN_006192b0(&DAT_02cecee0);
      FUN_005d50a0();
      FUN_00822ed0(0x14);
      iVar1 = FUN_00572420();
    } while (iVar1 != 0);
    FUN_00572450("Wait for running complete");
    FUN_007d6a70("Network ready\n");
    FUN_005d50a0();
    iVar1 = FUN_00572c20();
    if (iVar1 == 0) {
      FUN_0081e0c0("Game quit due to game already ending\n");
      uVar2 = FUN_0081cb40("multi_error","fail_join_game");
      FUN_0056fcb0(uVar2);
      FUN_00434170(2);
      FUN_00437620(1);
      FUN_005d48b0();
      FUN_00572a30(1);
      FUN_00572640();
      return 0;
    }
  }
  FUN_0081e0c0("Initializing Game Simulation Objects\n");
  FUN_004dfad0();
  FUN_005c5920();
  FUN_004dfbf0();
  FUN_004d4410();
  FUN_004b6ed0();
  FUN_005d50a0();
  if (DAT_009183d4 == 1) {
    FUN_0050f920(&DAT_00915540,_DAT_009183c4 & 0xffff,(int)_DAT_009183c4 >> 0x10 & 0xffff);
  }
  else if (DAT_009183d4 == 2) {
    FUN_0050fe80(&DAT_00915540,_DAT_009183c4);
  }
  iVar1 = FUN_00822e60();
  FUN_0081e0c0("Sim Startup: Waiting For VO at %ld ms initializing\n",iVar1 - _DAT_02a13e80);
  while (iVar1 = FUN_005d5270(), iVar1 != 0) {
    FUN_006192b0(&DAT_02cecee0);
    FUN_0043a170(0);
    FUN_00822ed0(0x10);
  }
  iVar1 = FUN_00822e60();
  FUN_0081e0c0("Sim Startup: VO complete at %ld ms initializing\n",iVar1 - _DAT_02a13e80);
  DAT_00915550 = 0;
  FUN_00437620(1);
  FUN_0067ca70(0,0,0);
  FUN_005d50a0();
  FUN_006151c0();
  FUN_006179c0();
  FUN_005d50a0();
  FUN_0062cba0();
  FUN_00437a70();
  FUN_00434f20();
  FUN_004378f0();
  FUN_00618bc0();
  FUN_0061a140(1);
  iVar1 = FUN_00572a70();
  if ((iVar1 == 0) && (DAT_008eaad0 != (code *)0x0)) {
    (*DAT_008eaad0)();
  }
  FUN_0067ca70(0,0,0);
  FUN_00623eb0();
  FUN_006179c0();
  return 1;
}


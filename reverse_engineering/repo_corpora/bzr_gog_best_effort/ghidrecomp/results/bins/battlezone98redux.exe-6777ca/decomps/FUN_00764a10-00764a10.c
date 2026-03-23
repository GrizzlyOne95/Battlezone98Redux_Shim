
void FUN_00764a10(void)

{
  char cVar1;
  int iVar2;
  
  if (DAT_00945463 != '\0') {
    SteamAPI_RunCallbacks();
  }
  if (DAT_00945490 != 0) {
    FUN_0073b690();
  }
  if (DAT_00945484 != 0) {
    FUN_006c69c0();
  }
  if (DAT_00945478 != 0) {
    FUN_0076ee40();
  }
  if (DAT_00945470 != 0) {
    FUN_00740be0();
  }
  if ((DAT_00945462 != '\0') && (DAT_0094547c != (int *)0x0)) {
    (**(code **)(*DAT_0094547c + 8))();
  }
  if (DAT_009183b0 == 0) {
    if ((((DAT_009183d0 != 0) && (DAT_009180d7 == '\0')) && (DAT_00917f4c == '\0')) &&
       ((cVar1 = FUN_00577d50(), cVar1 == '\0' && (iVar2 = FUN_00434160(), iVar2 != 2)))) {
      FUN_005d4670();
    }
  }
  else if ((DAT_009183d0 == 0) && (DAT_0091832c == 0)) {
    DAT_009183d0 = 1;
    FUN_005d48b0();
    DAT_009183d0 = 0;
    FUN_005d50f0();
  }
  return;
}


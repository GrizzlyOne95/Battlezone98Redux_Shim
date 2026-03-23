
void FUN_00764d80(void)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  undefined4 local_20;
  undefined4 local_18;
  undefined4 local_10;
  
  if (DAT_00945461 == '\0') {
    DAT_00945461 = '\x01';
    iVar2 = FUN_00764bc0();
    DAT_008f0470 = 4;
    if (DAT_0094546c != 0) {
      DAT_008f0470 = DAT_0094546c;
    }
    if ((iVar2 != 0) && (cVar1 = FUN_00764d50(DAT_008f0470), cVar1 == '\0')) {
      DAT_008f0470 = 4;
    }
    if (((DAT_008f0470 == 1) || (DAT_008f0470 == 3)) || (DAT_008f0470 == 4)) {
      DAT_00945463 = SteamAPI_Init();
    }
    if ((DAT_008f0470 == 2) || (DAT_008f0470 == 3)) {
      FUN_0073b130(DAT_00945463);
      pvVar3 = operator_new(0xc);
      if (pvVar3 == (void *)0x0) {
        local_10 = 0;
      }
      else {
        local_10 = FUN_0073ae30();
      }
      DAT_00945490 = local_10;
    }
    if (DAT_008f0470 == 4) {
      if (DAT_00945463 == '\0') {
        FUN_0073b130(0);
        pvVar3 = operator_new(0xc);
        if (pvVar3 == (void *)0x0) {
          local_18 = 0;
        }
        else {
          local_18 = FUN_0073ae30();
        }
        DAT_00945490 = local_18;
      }
      pvVar3 = operator_new(8);
      if (pvVar3 == (void *)0x0) {
        local_20 = 0;
      }
      else {
        local_20 = FUN_006c6830(DAT_00945463);
      }
      DAT_00945484 = local_20;
    }
  }
  return;
}


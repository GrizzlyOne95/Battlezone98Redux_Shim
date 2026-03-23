
void __fastcall FUN_00575bf0(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  undefined4 local_30;
  int local_2c;
  int local_28;
  undefined1 local_24 [4];
  int local_20;
  uint local_1c;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0084b926;
  local_10 = ExceptionList;
  uVar3 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  if ((DAT_00917f48 != 0) && (*(short *)(DAT_00917f48 + 4) == *(short *)(param_1 + 0x28))) {
    *(undefined2 *)(DAT_00917f48 + 4) = 0;
  }
  local_14 = param_1;
  uVar4 = FUN_0041f870(*(undefined2 *)(param_1 + 0x28),*(undefined1 *)(param_1 + 0x68),uVar3);
  uVar4 = FUN_0081e820("Removing Player %s (ID %lu, Team %d)\n",uVar4);
  FUN_0081e710(uVar4);
  if (DAT_00917a74 != 0) {
    local_28 = DAT_00917a74;
    FID_conflict_begin(local_24);
    while( true ) {
      uVar4 = FID_conflict_end(local_38);
      cVar1 = FID_conflict_operator__(uVar4);
      if (cVar1 == '\0') break;
      piVar5 = (int *)FUN_00421ec0();
      local_18 = *piVar5;
      sVar2 = FUN_004b9800();
      if (sVar2 == *(short *)(local_14 + 0x28)) {
        uVar4 = (**(code **)(*(int *)(local_18 + 0x18) + 4))();
        cVar1 = FUN_005cb2a0(uVar4);
        if (cVar1 == '\0') {
          *(undefined4 *)(local_18 + 0xec) = 0;
          local_20 = (**(code **)(*(int *)(local_18 + 0x18) + 0x30))();
          if ((local_20 != 0) && (*(short *)(local_20 + 0x10) != 1)) {
            uVar3 = FUN_004b9a90();
            if ((0xffff < uVar3) && (*(int *)(local_20 + 0x84) != 7)) {
              FUN_0062de40(local_20,0x280);
            }
            FUN_004b8460();
          }
        }
      }
      FUN_0046b260(local_34,0);
    }
  }
  if ((*(char *)(local_14 + 0x68) != '\0') && (*(byte *)(local_14 + 0x68) < 0x10)) {
    iVar6 = FUN_00434160();
    if ((iVar6 == 5) && (iVar6 = FUN_0046ce40(), iVar6 == 0)) {
      for (local_1c = 1; (int)local_1c < 0x10; local_1c = local_1c + 1) {
        if (*(byte *)(local_14 + 0x68) != local_1c) {
          uVar3 = local_1c;
          FUN_005e0bc0(*(undefined1 *)(local_14 + 0x68),local_1c);
          FUN_005e12e0(uVar3);
          uVar3 = (uint)*(byte *)(local_14 + 0x68);
          FUN_005e0bc0(local_1c,uVar3);
          FUN_005e12e0(uVar3);
        }
      }
    }
    FUN_00577900(0);
  }
  local_30 = FUN_00578950(local_14 + 0x30);
  DAT_00918128 = DAT_00918128 - (short)local_30;
  FUN_00578d70(local_14 + 0x28);
  FUN_00578b10(local_14 + 0x30);
  FUN_00578b10(local_14 + 0x30);
  if (*(int *)(local_14 + 0x24) != 0) {
    FUN_005d8ee0(local_14);
  }
  local_2c = FUN_007659f0();
  if (local_2c != 0) {
    FUN_00574aa0(*(undefined2 *)(local_14 + 0x28));
  }
  uVar4 = FUN_00416410();
  uVar4 = FUN_0041f870(*(undefined2 *)(local_14 + 0x28),*(undefined1 *)(local_14 + 0x68),uVar4);
  uVar4 = FUN_0081e820("Removed Player %s (ID %lu, Team %d)  %ld players remaining\n",uVar4);
  FUN_0081e710(uVar4);
  local_8 = local_8 & 0xffffff00;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00575bd0();
  ExceptionList = local_10;
  return;
}


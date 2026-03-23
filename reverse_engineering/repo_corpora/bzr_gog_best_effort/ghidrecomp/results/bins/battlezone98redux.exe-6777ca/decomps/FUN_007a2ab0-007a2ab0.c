
void FUN_007a2ab0(void)

{
  undefined4 uVar1;
  uint uStack_58;
  undefined1 local_40 [4];
  undefined1 local_3c [12];
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 *local_28;
  undefined4 local_24;
  undefined4 local_20 [2];
  char local_17;
  char local_16;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860150;
  local_10 = ExceptionList;
  uStack_58 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_58;
  ExceptionList = &local_10;
  FUN_0042d8c0(local_20);
  local_8 = 0;
  local_15 = FUN_00420f10(&stack0x00000008);
  if (local_15 != '\0') {
    uVar1 = FID_conflict_begin(local_3c);
    local_16 = FUN_00420f10(uVar1);
    if (local_16 != '\0') {
      local_24 = FUN_00422e80();
      FUN_007a2e30(local_20[0],local_24);
                    /* WARNING: Subroutine does not return */
      FUN_0042de70();
    }
  }
  local_17 = FUN_00420f10(&stack0x00000008);
  if (local_17 != '\0') {
    local_28 = (undefined4 *)FID_conflict_begin(local_40);
    local_30 = *local_28;
    local_2c = FUN_00422e80();
    FUN_00477aa0(local_30,local_2c);
                    /* WARNING: Subroutine does not return */
    FUN_0042de70();
  }
  FUN_007a2bc6();
  return;
}


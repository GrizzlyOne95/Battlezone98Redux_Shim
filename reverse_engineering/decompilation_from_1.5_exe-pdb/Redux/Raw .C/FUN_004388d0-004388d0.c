
undefined1 FUN_004388d0(undefined4 param_1)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  uint local_34;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  undefined4 local_20;
  char *local_1c;
  undefined1 local_18 [4];
  int local_14;
  char *local_10;
  uint local_c;
  char local_6;
  char local_5;
  
  local_5 = '\x01';
  local_c = FUN_00416410();
  if (10 < local_c) {
    local_c = 10;
  }
  if ((local_5 == '\0') || (cVar2 = FUN_004cd1b0(param_1,&local_c,4,&DAT_00874054), cVar2 == '\0'))
  {
    local_20 = 0;
  }
  else {
    local_20 = 1;
  }
  local_5 = (char)local_20;
  FUN_0042d8c0(local_18);
  while( true ) {
    uVar3 = FID_conflict_begin(local_3c);
    cVar2 = FUN_00420f10(uVar3);
    if (cVar2 == '\0') break;
    local_34 = local_c;
    uVar4 = local_c - 1;
    bVar1 = (int)local_c < 1;
    local_c = uVar4;
    if (bVar1) break;
    local_24 = (undefined4 *)FUN_0042de50();
    local_24 = (undefined4 *)*local_24;
    local_1c = (char *)*local_24;
    local_10 = &DAT_0260c258;
    do {
      local_6 = *local_1c;
      *local_10 = local_6;
      local_1c = local_1c + 1;
      local_10 = local_10 + 1;
    } while (local_6 != '\0');
    if ((local_5 == '\0') ||
       (cVar2 = FUN_004cd1b0(param_1,local_24 + 1,4,"seqNo",&DAT_0260c258), cVar2 == '\0')) {
      local_28 = 0;
    }
    else {
      local_28 = 1;
    }
    local_5 = (char)local_28;
    if (((char)local_28 == '\0') ||
       (cVar2 = FUN_004ccd80(param_1,&DAT_0260c258,0xe,&DAT_00874064), cVar2 == '\0')) {
      local_2c = 0;
    }
    else {
      local_2c = 1;
    }
    local_5 = (char)local_2c;
    FUN_00438c10(local_38,0);
  }
  if ((local_5 != '\0') &&
     (cVar2 = FUN_004ccd80(param_1,local_14 + 0x40,0x10,"lastMsg"), cVar2 != '\0')) {
    return 1;
  }
  return 0;
}



char FUN_0045d830(undefined4 param_1)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int *piVar4;
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined1 local_34 [4];
  char local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  char local_5;
  
  local_5 = FUN_004ccd10(param_1,"[AiMission]");
  if (DAT_009173b7 != '\0') {
    return local_5;
  }
  FUN_00430590();
  local_14 = 0;
  puVar2 = (undefined4 *)FUN_0042d8c0(local_34);
  local_c = *puVar2;
  while (local_5 != '\0') {
    uVar3 = FID_conflict_begin(local_3c);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_0042de50();
    if (*(char *)(*piVar4 + 4) == '\0') {
      local_14 = local_14 + 1;
    }
    FUN_00438c10(local_38,0);
  }
  if ((local_5 == '\0') || (cVar1 = FUN_004cd1b0(param_1,&local_14,4,&DAT_00874054), cVar1 == '\0'))
  {
    local_18 = 0;
  }
  else {
    local_18 = 1;
  }
  local_5 = (char)local_18;
  puVar2 = (undefined4 *)FUN_0042d8c0(local_40);
  local_c = *puVar2;
  while (local_5 != '\0') {
    uVar3 = FID_conflict_begin(local_48);
    cVar1 = FUN_00420f10(uVar3);
    if (cVar1 == '\0') break;
    piVar4 = (int *)FUN_0042de50();
    local_1c = *piVar4;
    if (*(char *)(local_1c + 4) == '\0') {
      if ((local_5 == '\0') || (cVar1 = FUN_005d7580(param_1,local_1c), cVar1 == '\0')) {
        local_20 = 0;
      }
      else {
        local_20 = 1;
      }
      local_5 = (char)local_20;
    }
    FUN_00438c10(local_44,0);
  }
  if ((local_5 == '\0') ||
     (cVar1 = FUN_004ccf20(param_1,local_10 + 0x10,1,&DAT_00875220), cVar1 == '\0')) {
    local_24 = 0;
  }
  else {
    local_24 = 1;
  }
  local_5 = (char)local_24;
  if (((char)local_24 == '\0') ||
     (cVar1 = FUN_004cd360(param_1,local_10 + 0x14,4,"shutdownTime"), cVar1 == '\0')) {
    local_28 = 0;
  }
  else {
    local_28 = 1;
  }
  local_5 = (char)local_28;
  if (((char)local_28 == '\0') ||
     (cVar1 = FUN_004ccf20(param_1,local_10 + 0x18,1,"failed"), cVar1 == '\0')) {
    local_2c = 0;
  }
  else {
    local_2c = 1;
  }
  local_5 = (undefined1)local_2c;
  if ((local_2c == 0) ||
     (cVar1 = FUN_004cce90(param_1,local_10 + 0x19,0xe,"resultName"), cVar1 == '\0')) {
    local_30 = '\0';
  }
  else {
    local_30 = '\x01';
  }
  return local_30;
}



char FUN_0045d570(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  char local_2c;
  char local_24;
  char local_20;
  int local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  char local_5;
  
  local_18 = 0;
  local_5 = FUN_004ce1c0(param_1,"[AiMission]");
  if (DAT_009173b7 == '\0') {
    if ((local_5 == '\0') || (cVar1 = FUN_004ce910(param_1,&local_18,4), cVar1 == '\0')) {
      local_14 = 0;
    }
    else {
      local_14 = 1;
    }
    local_5 = (char)local_14;
    for (local_10 = 0; (local_5 != '\0' && (local_10 < local_18)); local_10 = local_10 + 1) {
      iVar2 = FUN_005d7370(param_1);
      if (iVar2 == 0) {
        local_5 = '\0';
      }
      else {
        FUN_0045ccc0(iVar2);
      }
    }
    if ((local_5 == '\0') || (cVar1 = FUN_004ce5e0(param_1,local_c + 0x10,1), cVar1 == '\0')) {
      local_20 = '\0';
    }
    else {
      local_20 = '\x01';
    }
    local_5 = local_20;
    if ((local_20 == '\0') || (cVar1 = FUN_004ceb10(param_1,local_c + 0x14,4), cVar1 == '\0')) {
      local_24 = '\0';
    }
    else {
      local_24 = '\x01';
    }
    local_5 = local_24;
    if ((local_24 == '\0') || (cVar1 = FUN_004ce5e0(param_1,local_c + 0x18,1), cVar1 == '\0')) {
      local_5 = false;
    }
    else {
      local_5 = true;
    }
    if (((bool)local_5) && (cVar1 = FUN_004ce2f0(param_1,local_c + 0x19,0xe), cVar1 != '\0')) {
      local_2c = '\x01';
    }
    else {
      local_2c = '\0';
    }
    return local_2c;
  }
  return local_5;
}


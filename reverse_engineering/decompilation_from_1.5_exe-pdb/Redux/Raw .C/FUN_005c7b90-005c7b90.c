
undefined1 FUN_005c7b90(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined1 local_3c;
  char local_38;
  char local_34;
  char local_2c;
  char local_28;
  char local_24;
  char local_20;
  char local_1c;
  char local_18;
  int local_14;
  int local_10;
  int local_c;
  char local_5;
  
  if (DAT_009173b7 != '\0') {
    return 1;
  }
  FUN_00438ac0(param_1);
  local_5 = '\x01';
  fVar3 = (float10)FUN_005c74b0();
  DAT_02a13d88 = (float)fVar3;
  local_14 = 0;
  for (local_10 = 0; local_10 < 0x10; local_10 = local_10 + 1) {
    if (-1 < *(int *)(&DAT_02a13d20 + local_10 * 4)) {
      local_14 = local_14 + 1;
    }
  }
  if ((local_5 == '\0') ||
     (cVar1 = FUN_004cd1b0(param_1,&local_14,4,"aip_team_count"), cVar1 == '\0')) {
    local_18 = '\0';
  }
  else {
    local_18 = '\x01';
  }
  local_5 = local_18;
  for (local_c = 0; local_c < 0x10; local_c = local_c + 1) {
    if (-1 < *(int *)(&DAT_02a13d20 + local_c * 4)) {
      if ((local_5 == '\0') || (cVar1 = FUN_004cd1b0(param_1,&local_c,4,"aip_team"), cVar1 == '\0'))
      {
        local_1c = '\0';
      }
      else {
        local_1c = '\x01';
      }
      local_5 = local_1c;
      if (local_1c == '\0') {
LAB_005c7ce5:
        local_20 = '\0';
      }
      else {
        pcVar5 = "aip_name";
        uVar4 = 0xe;
        uVar2 = FUN_005ce740(*(undefined4 *)(&DAT_02a13d20 + local_c * 4));
        cVar1 = FUN_004cce90(param_1,uVar2,uVar4,pcVar5);
        if (cVar1 == '\0') goto LAB_005c7ce5;
        local_20 = '\x01';
      }
      local_5 = local_20;
    }
  }
  if ((local_5 == '\0') ||
     (cVar1 = FUN_004cd1b0(param_1,&DAT_025cfa1c,4,"difficultySetting"), cVar1 == '\0')) {
    local_24 = '\0';
  }
  else {
    local_24 = '\x01';
  }
  local_5 = local_24;
  if ((local_24 == '\0') ||
     (cVar1 = FUN_004ccf20(param_1,&DAT_02a13d64,1,"cameraReady"), cVar1 == '\0')) {
    local_28 = '\0';
  }
  else {
    local_28 = '\x01';
  }
  local_5 = local_28;
  if ((local_28 == '\0') ||
     (cVar1 = FUN_004cd1b0(param_1,&DAT_009182a4,4,"cameraCallCount"), cVar1 == '\0')) {
    local_2c = '\0';
  }
  else {
    local_2c = '\x01';
  }
  local_5 = local_2c;
  if ((local_2c == '\0') ||
     (cVar1 = FUN_004cd360(param_1,&DAT_02a13d88,4,"quakeMag"), cVar1 == '\0')) {
    local_5 = '\0';
  }
  else {
    local_5 = '\x01';
  }
  if ((local_5 == '\0') || (cVar1 = FUN_0049ad30(param_1), cVar1 == '\0')) {
    local_34 = '\0';
  }
  else {
    local_34 = '\x01';
  }
  local_5 = local_34;
  if (local_34 != '\0') {
    cVar1 = FUN_004f4670(param_1);
    if (cVar1 != '\0') {
      local_38 = '\x01';
      goto LAB_005c7e4b;
    }
  }
  local_38 = '\0';
LAB_005c7e4b:
  local_5 = local_38;
  if ((local_38 == '\0') || (cVar1 = FUN_004a7440(param_1), cVar1 == '\0')) {
    local_3c = 0;
  }
  else {
    local_3c = 1;
  }
  return local_3c;
}


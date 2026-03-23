
undefined1 __thiscall FUN_005f9490(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined8 local_70;
  undefined1 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  undefined4 local_10;
  int local_c;
  char local_6;
  char local_5;
  
  local_5 = 1;
  local_70 = 0;
  local_c = param_1;
  cVar1 = FUN_004ce910(param_2,param_1 + 0x18,4);
  local_5 = cVar1 != '\0';
  local_14 = (uint)(byte)local_5;
  if (((bool)local_5) && (cVar1 = FUN_004ce910(param_2,&local_10,4), cVar1 != '\0')) {
    local_18 = 1;
  }
  else {
    local_18 = 0;
  }
  local_5 = (char)local_18;
  if ((char)local_18 == '\0') {
LAB_005f9552:
    local_1c = 0;
  }
  else {
    *(undefined4 *)(local_c + 0x1c) = local_10;
    cVar1 = FUN_004ce910(param_2,&local_10,4);
    if (cVar1 == '\0') goto LAB_005f9552;
    local_1c = 1;
  }
  local_5 = (char)local_1c;
  if ((char)local_1c == '\0') {
LAB_005f959a:
    local_20 = 0;
  }
  else {
    *(undefined4 *)(local_c + 0x20) = local_10;
    cVar1 = FUN_004ce910(param_2,&local_10,4);
    if (cVar1 == '\0') goto LAB_005f959a;
    local_20 = 1;
  }
  local_5 = (char)local_20;
  if ((char)local_20 != '\0') {
    *(undefined4 *)(local_c + 0x24) = local_10;
    cVar1 = FUN_004cea20(param_2,local_c + 0x28,4);
    if (cVar1 != '\0') {
      local_24 = 1;
      goto LAB_005f95ec;
    }
  }
  local_24 = 0;
LAB_005f95ec:
  local_5 = (char)local_24;
  if ((0x7df < DAT_00917b20) && (*(int *)(local_c + 0x24) != 0)) {
    if (((char)local_24 == '\0') ||
       (cVar1 = FUN_004cf640(param_2,local_c + 0x2c,4,"UnitProcess::saveWhere",local_c),
       cVar1 == '\0')) {
      local_28 = 0;
    }
    else {
      local_28 = 1;
    }
    local_5 = (char)local_28;
  }
  if ((local_5 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_c + 0x30,4), cVar1 == '\0')) {
    local_2c = 0;
  }
  else {
    local_2c = 1;
  }
  local_5 = (char)local_2c;
  if (((char)local_2c == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_c + 0x34,4,"UnitProcess::me",local_c), cVar1 == '\0')) {
    local_30 = 0;
  }
  else {
    local_30 = 1;
  }
  local_5 = (char)local_30;
  if (((char)local_30 == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_c + 0x38,4,"UnitProcess::task",local_c), cVar1 == '\0')) {
    local_34 = 0;
  }
  else {
    local_34 = 1;
  }
  local_5 = (char)local_34;
  if (((char)local_34 == '\0') || (cVar1 = FUN_004cea20(param_2,local_c + 0x3c,4), cVar1 == '\0')) {
    local_38 = 0;
  }
  else {
    local_38 = 1;
  }
  local_5 = (char)local_38;
  if (((char)local_38 == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_c + 0x10,4,"UnitProcess::where",local_c), cVar1 == '\0')) {
    local_3c = 0;
  }
  else {
    local_3c = 1;
  }
  local_5 = (char)local_3c;
  if (((char)local_3c == '\0') || (cVar1 = FUN_004ce5e0(param_2,&local_6,1), cVar1 == '\0')) {
    local_40 = 0;
  }
  else {
    local_40 = 1;
  }
  if (((char)local_40 == '\0') || (local_6 != '\0')) {
    local_44 = 0;
  }
  else {
    local_44 = 1;
  }
  local_5 = (char)local_44;
  if (0x40b < DAT_00917b20) {
    if (((char)local_44 == '\0') || (cVar1 = FUN_004ce5e0(param_2,local_c + 0x40,1), cVar1 == '\0'))
    {
      local_48 = 0;
    }
    else {
      local_48 = 1;
    }
    local_5 = (char)local_48;
  }
  if ((local_5 == '\0') || (cVar1 = FUN_004cf210(param_2,&local_70,8), cVar1 == '\0')) {
    local_4c = 0;
  }
  else {
    local_4c = 1;
  }
  local_5 = (char)local_4c;
  if (((char)local_4c == '\0') || (cVar1 = FUN_004ce5e0(param_2,local_c + 0x48,1), cVar1 == '\0')) {
    local_50 = 0;
  }
  else {
    local_50 = 1;
  }
  local_5 = (char)local_50;
  if (((char)local_50 == '\0') || (cVar1 = FUN_004ce5e0(param_2,local_c + 0x49,1), cVar1 == '\0')) {
    local_54 = 0;
  }
  else {
    local_54 = 1;
  }
  local_5 = (char)local_54;
  if (((char)local_54 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_c + 0x4c,4), cVar1 == '\0')) {
    local_58 = 0;
  }
  else {
    local_58 = 1;
  }
  local_5 = (char)local_58;
  if (((char)local_58 == '\0') || (cVar1 = FUN_004ce5e0(param_2,local_c + 0x50,1), cVar1 == '\0')) {
    local_5c = 0;
  }
  else {
    local_5c = 1;
  }
  local_5 = (char)local_5c;
  if (((char)local_5c == '\0') || (cVar1 = FUN_004ceb10(param_2,local_c + 0x54,4), cVar1 == '\0')) {
    local_60 = 0;
  }
  else {
    local_60 = 1;
  }
  local_5 = (char)local_60;
  if (((char)local_60 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_c + 0x58,4), cVar1 == '\0')) {
    local_64 = 0;
  }
  else {
    local_64 = 1;
  }
  local_5 = (char)local_64;
  *(undefined1 *)(local_c + 0x40) = 0;
  if ((int)local_70 == 0 && local_70._4_4_ == 0) {
    *(undefined4 *)(local_c + 0x44) = 0;
  }
  else {
    uVar2 = FUN_004e0f70((int)local_70,local_70._4_4_);
    *(undefined4 *)(local_c + 0x44) = uVar2;
  }
  if ((local_5 == '\0') || (cVar1 = FUN_004616d0(param_2), cVar1 == '\0')) {
    local_68 = 0;
  }
  else {
    local_68 = 1;
  }
  return local_68;
}


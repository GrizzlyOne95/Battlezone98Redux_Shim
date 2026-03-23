
void __thiscall FUN_005fef80(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 local_b4 [4];
  undefined1 local_b0 [4];
  undefined4 local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  uint local_68;
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
  int local_1c;
  char local_15;
  undefined1 local_14 [12];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_15 = 1;
  local_1c = param_1;
  cVar1 = FUN_004ce910(param_2,param_1 + 8,4);
  local_15 = cVar1 != '\0';
  local_68 = (uint)(byte)local_15;
  if (((bool)local_15) && (cVar1 = FUN_004ce910(param_2,local_1c + 0xc,4), cVar1 != '\0')) {
    local_a8 = 1;
  }
  else {
    local_a8 = 0;
  }
  local_15 = (char)local_a8;
  if (((char)local_a8 == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_1c + 0x10,4,"UnitTask::me",local_1c), cVar1 == '\0')) {
    local_28 = 0;
  }
  else {
    local_28 = 1;
  }
  local_15 = (char)local_28;
  if (((char)local_28 == '\0') || (cVar1 = FUN_004ce910(param_2,local_1c + 0x14,4), cVar1 == '\0'))
  {
    local_70 = 0;
  }
  else {
    local_70 = 1;
  }
  local_15 = (char)local_70;
  if (((char)local_70 == '\0') || (cVar1 = FUN_004ce5e0(param_2,local_1c + 0x1c,1), cVar1 == '\0'))
  {
    local_30 = 0;
  }
  else {
    local_30 = 1;
  }
  local_15 = (char)local_30;
  if (((char)local_30 == '\0') || (cVar1 = FUN_004ce910(param_2,local_1c + 0x20,4), cVar1 == '\0'))
  {
    local_a4 = 0;
  }
  else {
    local_a4 = 1;
  }
  local_15 = (char)local_a4;
  if (((char)local_a4 == '\0') || (cVar1 = FUN_004ce910(param_2,local_1c + 0x24,4), cVar1 == '\0'))
  {
    local_38 = 0;
  }
  else {
    local_38 = 1;
  }
  local_15 = (char)local_38;
  if (((char)local_38 == '\0') || (cVar1 = FUN_004ced10(param_2,local_1c + 0x28,0xc), cVar1 == '\0')
     ) {
    local_78 = 0;
  }
  else {
    local_78 = 1;
  }
  local_15 = (char)local_78;
  if (((char)local_78 == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_1c + 0x40,4,"UnitTask::plan",local_1c), cVar1 == '\0')) {
    local_40 = 0;
  }
  else {
    local_40 = 1;
  }
  local_15 = (char)local_40;
  if (((char)local_40 == '\0') || (cVar1 = FUN_004ce910(param_2,local_1c + 0x44,4), cVar1 == '\0'))
  {
    local_98 = 0;
  }
  else {
    local_98 = 1;
  }
  local_15 = (char)local_98;
  if (((char)local_98 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 100,4), cVar1 == '\0')) {
    local_48 = 0;
  }
  else {
    local_48 = 1;
  }
  local_15 = (char)local_48;
  if (((char)local_48 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0x6c,4), cVar1 == '\0'))
  {
    local_80 = 0;
  }
  else {
    local_80 = 1;
  }
  local_15 = (char)local_80;
  if (((char)local_80 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0x68,4), cVar1 == '\0'))
  {
    local_50 = 0;
  }
  else {
    local_50 = 1;
  }
  local_15 = (char)local_50;
  if (((char)local_50 == '\0') || (cVar1 = FUN_004ce910(param_2,local_1c + 0x78,4), cVar1 == '\0'))
  {
    local_ac = 0;
  }
  else {
    local_ac = 1;
  }
  local_15 = (char)local_ac;
  if (0x40e < DAT_00917b20) {
    if (((char)local_ac == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0x84,4), cVar1 == '\0')
       ) {
      local_58 = 0;
    }
    else {
      local_58 = 1;
    }
    local_15 = (char)local_58;
  }
  if ((local_15 == '\0') || (cVar1 = FUN_004ced10(param_2,local_1c + 0x88,0xc), cVar1 == '\0')) {
    local_88 = 0;
  }
  else {
    local_88 = 1;
  }
  local_15 = (char)local_88;
  if (((char)local_88 == '\0') || (cVar1 = FUN_004ce910(param_2,local_1c + 0x94,4), cVar1 == '\0'))
  {
    local_60 = 0;
  }
  else {
    local_60 = 1;
  }
  local_15 = (char)local_60;
  if (((char)local_60 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0xb0,4), cVar1 == '\0'))
  {
    local_a0 = 0;
  }
  else {
    local_a0 = 1;
  }
  local_15 = (char)local_a0;
  if (((char)local_a0 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0xf0,4), cVar1 == '\0'))
  {
    local_20 = 0;
  }
  else {
    local_20 = 1;
  }
  local_15 = (char)local_20;
  if (((char)local_20 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0xf4,4), cVar1 == '\0'))
  {
    local_90 = 0;
  }
  else {
    local_90 = 1;
  }
  local_15 = (char)local_90;
  if (((char)local_90 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0xf8,4), cVar1 == '\0'))
  {
    local_24 = 0;
  }
  else {
    local_24 = 1;
  }
  local_15 = (char)local_24;
  if (((char)local_24 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0xfc,4), cVar1 == '\0'))
  {
    local_2c = 0;
  }
  else {
    local_2c = 1;
  }
  local_15 = (char)local_2c;
  if (((char)local_2c == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0x100,4), cVar1 == '\0'))
  {
    local_34 = 0;
  }
  else {
    local_34 = 1;
  }
  local_15 = (char)local_34;
  if (((char)local_34 == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_1c + 0x104,4,"UnitTask::attackTarget",local_1c),
     cVar1 == '\0')) {
    local_3c = 0;
  }
  else {
    local_3c = 1;
  }
  local_15 = (char)local_3c;
  if (((char)local_3c == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0x108,4), cVar1 == '\0'))
  {
    local_44 = 0;
  }
  else {
    local_44 = 1;
  }
  local_15 = (char)local_44;
  if (((char)local_44 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0x110,4), cVar1 == '\0'))
  {
    local_4c = 0;
  }
  else {
    local_4c = 1;
  }
  local_15 = (char)local_4c;
  if (((char)local_4c == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0x114,4), cVar1 == '\0'))
  {
    local_54 = 0;
  }
  else {
    local_54 = 1;
  }
  local_15 = (char)local_54;
  if (((char)local_54 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0x118,4), cVar1 == '\0'))
  {
    local_5c = 0;
  }
  else {
    local_5c = 1;
  }
  local_15 = (char)local_5c;
  if (((char)local_5c == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_1c + 0x11c,4,"UnitTask::followTarget",local_1c),
     cVar1 == '\0')) {
    local_64 = 0;
  }
  else {
    local_64 = 1;
  }
  local_15 = (char)local_64;
  if (((char)local_64 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_1c + 0x120,4), cVar1 == '\0'))
  {
    local_6c = 0;
  }
  else {
    local_6c = 1;
  }
  local_15 = (char)local_6c;
  if ((1999 < DAT_00917b20) && (DAT_00917b20 < 0x7d3)) {
    if (((char)local_6c == '\0') || (cVar1 = FUN_004ce910(param_2,local_b4,4), cVar1 == '\0')) {
      local_74 = 0;
    }
    else {
      local_74 = 1;
    }
    local_15 = (char)local_74;
    if (((char)local_74 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_b0,4), cVar1 == '\0')) {
      local_7c = 0;
    }
    else {
      local_7c = 1;
    }
    local_15 = (char)local_7c;
    if (((char)local_7c == '\0') || (cVar1 = FUN_004ceb10(param_2,local_b0,4), cVar1 == '\0')) {
      local_84 = 0;
    }
    else {
      local_84 = 1;
    }
    local_15 = (char)local_84;
    if (((char)local_84 == '\0') || (cVar1 = FUN_004ced10(param_2,local_14,0xc), cVar1 == '\0')) {
      local_8c = 0;
    }
    else {
      local_8c = 1;
    }
    local_15 = (char)local_8c;
    if (((char)local_8c == '\0') || (cVar1 = FUN_004ced10(param_2,local_14,0xc), cVar1 == '\0')) {
      local_94 = 0;
    }
    else {
      local_94 = 1;
    }
    local_15 = (char)local_94;
  }
  if ((local_15 == '\0') || (cVar1 = FUN_00461c90(param_2), cVar1 == '\0')) {
    local_9c = 0;
  }
  else {
    local_9c = 1;
  }
  local_15 = (undefined1)local_9c;
  FUN_0083e885();
  return;
}


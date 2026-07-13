
undefined1 __thiscall FUN_00473ae0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined8 local_48;
  undefined1 local_40;
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
  undefined4 local_14;
  uint local_10;
  int local_c;
  char local_6;
  char local_5;
  
  local_5 = 1;
  local_48 = 0;
  local_c = param_1;
  cVar1 = FUN_004ce910(param_2,param_1 + 0x18,4);
  local_5 = cVar1 != '\0';
  local_10 = (uint)(byte)local_5;
  if (((bool)local_5) && (cVar1 = FUN_004ce910(param_2,local_c + 0x1c,4), cVar1 != '\0')) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  local_5 = (char)local_14;
  if (((char)local_14 == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_c + 0x20,4,"ArmoryProcess::craft",local_c), cVar1 == '\0'))
  {
    local_18 = 0;
  }
  else {
    local_18 = 1;
  }
  local_5 = (char)local_18;
  if (((char)local_18 == '\0') || (cVar1 = FUN_004ce5e0(param_2,&local_6,1), cVar1 == '\0')) {
    local_1c = 0;
  }
  else {
    local_1c = 1;
  }
  if (((char)local_1c == '\0') || (local_6 != '\0')) {
    local_20 = 0;
  }
  else {
    local_20 = 1;
  }
  local_5 = (char)local_20;
  if (((char)local_20 == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_c + 0x10,4,"ArmoryProcess::where",local_c), cVar1 == '\0'))
  {
    local_24 = 0;
  }
  else {
    local_24 = 1;
  }
  local_5 = (char)local_24;
  if (((char)local_24 == '\0') || (cVar1 = FUN_004ce910(param_2,local_c + 0x24,4), cVar1 == '\0')) {
    local_28 = 0;
  }
  else {
    local_28 = 1;
  }
  local_5 = (char)local_28;
  if (((char)local_28 == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_c + 0x28,4,"ArmoryProcess::task",local_c), cVar1 == '\0'))
  {
    local_2c = 0;
  }
  else {
    local_2c = 1;
  }
  local_5 = (char)local_2c;
  if (((char)local_2c == '\0') || (cVar1 = FUN_004cf210(param_2,&local_48,8), cVar1 == '\0')) {
    local_30 = 0;
  }
  else {
    local_30 = 1;
  }
  local_5 = (char)local_30;
  if (((char)local_30 == '\0') || (cVar1 = FUN_004ced10(param_2,local_c + 0x34,0xc), cVar1 == '\0'))
  {
    local_34 = 0;
  }
  else {
    local_34 = 1;
  }
  local_5 = (char)local_34;
  if (((char)local_34 == '\0') || (cVar1 = FUN_004ce5e0(param_2,local_c + 0x40,1), cVar1 == '\0')) {
    local_38 = 0;
  }
  else {
    local_38 = 1;
  }
  local_5 = (char)local_38;
  if (((char)local_38 == '\0') || (cVar1 = FUN_004ce5e0(param_2,local_c + 0x41,1), cVar1 == '\0')) {
    local_3c = 0;
  }
  else {
    local_3c = 1;
  }
  local_5 = (char)local_3c;
  if ((int)local_48 == 0 && local_48._4_4_ == 0) {
    *(undefined4 *)(local_c + 0x2c) = 0;
  }
  else {
    uVar2 = FUN_004e0f70((int)local_48,local_48._4_4_);
    *(undefined4 *)(local_c + 0x2c) = uVar2;
  }
  *(undefined4 *)(local_c + 0x30) = 0;
  if ((local_5 == '\0') || (cVar1 = FUN_004616d0(param_2), cVar1 == '\0')) {
    local_40 = 0;
  }
  else {
    local_40 = 1;
  }
  return local_40;
}

